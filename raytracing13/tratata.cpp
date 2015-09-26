#include "tratata.h"

#include "camera.h"
#include "traceengine.h"
#include "rgbe.h"
#include "projectionpane.h"

void tratata::render(Settings settings, scene *myScene)
{

    camera cacamera;//params are set inside constructor
    traceEngine tracer;

    ProjectionPane pane(settings.getWidth(), settings.getHeight());
    //tracer.generateScene("texture.bmp");
    tracer.setScene(myScene);

    cout << "render.." << endl;
     tracer.testTrace(pane, cacamera, settings);

     cout << "processing.." << endl;

    image = new QImage(pane.getWidth(), pane.getHeight(), QImage::Format_RGB16);

    //write hdr
    FILE* fResult ;
    int finalSaveResult;

    if (settings.getSavehdr()){
        fResult = fopen("pathtracing.hdr", "wb");
        finalSaveResult = RGBE_WriteHeader(fResult, pane.getWidth(), pane.getHeight(), 0);//FILE* fp, int width, int height, rgbe_header_info* info
    }

    for (int x = 0; x < image->width(); x++)
        for (int y = 0; y < image->height(); y++){
            Rgb color = pane.getPixel(y, x);
            //hdr------------
            if (settings.getSavehdr()){
                float *rgbeColor = new float[3];
                rgbeColor[0] = color.red();
                rgbeColor[1] = color.green();
                rgbeColor[2] = color.blue();

                finalSaveResult =  RGBE_WritePixels(fResult, rgbeColor , 0, 1);
                delete [] rgbeColor;
            }
            //----------------

            color.setRed(pow(color.red(), 1/2.2f));
            color.setGreen(pow(color.green(), 1/2.2f));
            color.setBlue(pow(color.blue(), 1/2.2f));


            color = color * 255;
            QRgb qcolor = qRgb((int)color.red(), (int)color.green(), (int)color.blue());
            image->setPixel(y,x,qcolor);
        }



    //save the image;
    string name = "pathtracing.bmp";
    QString str(name.c_str());
    image->save(str, "bmp");
}

tratata::~tratata()
{
    delete image;

}


