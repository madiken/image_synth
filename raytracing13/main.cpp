#include <QCoreApplication>
#include <QtCore\QtCore>
#include <QtGui\QtGui>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <iostream>

#include "settings.h"
#include "scene.h"
#include "tratata.h"


using namespace std;


/*
 *-size - размер картинки (она квадратная)
-depth - глубина рекурсии
-hdr сохранять ли в hdr

-raysperpixel количество лучей, испускаемых из пикселя
 **/
bool getUserCommand(int argc, char *argv[], string *errMessage, Settings & s){
    vector<string> para;
    for (int i = 1 ; i < argc; i++){

        string p(argv[i]);

        para.push_back(p);
    }
    for (int i = 0; i < para.size(); i++)
        cout << i << " :"<< para[i] << endl;

    //DAFEULT VALUES----------------------
    int size = 100; //by default
    bool hdr = false;
    int depth = 10;
    int perPixel = 100;



    for (int i = 0; i < para.size(); i++){
        cout << "para " << i << " :"<< para[i] << endl;
        if (para[i].compare("-size") == 0){
            cout << "I see size" << endl;
            if ( i + 1 >= para.size() ) {
                (*errMessage) = "-size";

                return false;
            }
            size = atoi(para[i+1].c_str());


        }

        if (para[i].compare("-depth") == 0){
            cout << "I see depth" << endl;
            if ( i + 1 >= para.size() ) {
                (*errMessage) = "-depth";

                return false;
            }
            depth = atoi(para[i+1].c_str());

        }

        if (para[i].compare("-raysperpixel") == 0){
            cout << "I see raysperpixel" << endl;
            if ( i + 1 >= para.size() ) {
                (*errMessage) = "-raysperpixel";

                return false;
            }
            perPixel = atoi(para[i+1].c_str());

        }


        else if (para[i].compare("-hdr") == 0){
             hdr = true;
        }
   }
   s.setHeight(size);
   s.setWidth(size);
   s.setSize(size);
   s.setSavehdr(hdr);
   s.setRaysPerPixel(perPixel);
   s.setRecursionDepth(depth);



    return true;


}

int main(int argc, char *argv[])
{
    cout << "Hello!" << endl;
    Settings settings;
    string err;

    if (!getUserCommand(argc, argv, &err, settings))
    {
        cout << "Invalid params: " << err << endl;
        return -1;

    }



    tratata w;
    cout << "params ----------------" << endl;
    cout << "height :" << settings.getHeight() << endl;
   cout <<  "width :"<<settings.getWidth()<< endl;
   cout <<  "size :" << settings.getSize()<< endl;
   cout <<  "savehdr :" << settings.getSavehdr()<< endl;
   cout <<  "rays per pixel :" << settings.getRaysPerPixel()<< endl;
   cout <<  "depth : "<< settings.getRecursionDepth()<< endl;
   cout <<"-----------------------------" << endl;

    scene *myScene = new scene();

    //add some primitives to scene
    myScene->generateDefaultScene();


    cout << "rendering :" << endl;
    int start=GetTickCount();
    w.render(settings, myScene);
    int end=GetTickCount();


    cout<< "rendering finished in : " <<(end-start)/1000/60<<" mins " <<(end-start)/1000%60<<" secs" << endl;




    cout << "  delete myscene :" << endl;

    delete myScene;
    return 0;

}
