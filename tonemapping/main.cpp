#include <QCoreApplication>


#include <QCoreApplication>
#include <QtCore\QtCore>
#include <QtGui\QtGui>
#include <QtGui/QImage>
#include <QtGui/QColor>

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <stdlib.h>

#include "rgbe.h"


double round(double d)
{
  return floor(d + 0.5);
}
using namespace std;
int main(int argc, char *argv[])
{

     cout << "Hello!" << endl;
     string hdrfile; //= "test.hdr";
     if (argc == 2){
         hdrfile = argv[1];
     }
     else {
         cout << "please give me a file name";
         return -1;
     }
     string sss;

 /*    string y, x;
     fstream fstr(hdrfile, ifstream::in);
     cout << fstr.is_open() << endl;


     while(!fstr.eof()){
         getline(fstr, sss);
         int pos = sss.find("-Y");
         int pos2 = sss.find("+X");


          if ((pos!= string::npos) & ( pos2 != string::npos)){
            y =  sss.substr(pos, pos2 - pos);
            x =   sss.substr(pos2);
            break;
          }

     }
     fstr.close();
     cout << "fin" << endl;
     int posSpace = y.find(" ");
     y = sss.substr(2);
     cout << y << endl;

     posSpace = x.find(" ");
     x = sss.substr(2);
     cout << x << endl;

     int h = atoi(y.c_str());
     int w = atoi(x.c_str());

     cout << "h" << h <<endl;
     cout << "w" << w <<endl;*/


    FILE* file = fopen(hdrfile.c_str(), "rb");

    if (file == NULL){
        cout << "Error opening file";
        return -1;
    }



    int w, h;

  //  float ***lMatrix = new float **[h];
    rgbe_header_info info;

    RGBE_ReadHeader(file, &w, &h, &info);

    cout << "size "<< w << " " << h << endl;

    fstream fout("debug.txt", fstream::out);

   float *data = new float[3 * w * h];
   RGBE_ReadPixels_RLE(file,data,3,w,h);

   /*  for (int i = 0; i < h; i++){
        lMatrix[i] = new float*[w];
         for (int j = 0; j < w; j++){
             lMatrix[i][j] = new float[3];
             RGBE_ReadPixels(file, lMatrix[i][j], 0, 1);

             fout << lMatrix[i][j][0] << " " << lMatrix[i][j][1] << " " << lMatrix[i][j][2] << endl;

         }

     }*/




   // for (int i = 0; i < w*h*3; i++)
    //    cout << data[i] << endl;

    QImage img(QSize(w, h), QImage::Format_RGB666);
cout << img.width();
cout << img.height();


    for (int i = 0; i < h; i++){

         for (int j = 0; j < w; j++){
             float r = round(pow(data[i*3*w+j*3+0], 1)*255) ;
             float g = round(pow(data[i*3*w+j*3+1], 1)*255)  ;
             float b = round(pow(data[i*3*w+j*3+2],1)*255)  ;
             fout << r << " " << g << " " << b << endl;


             QColor  rgb(r, g, b);
             fout << i << "," << j << " ";

             img.setPixel(j, i, rgb.rgb());

         }
         fout << endl;

     }
      string name = hdrfile.substr(0, hdrfile.find("."));
      name = name + ".bmp";
      QString str(name.c_str());
     img.save(str, "bmp");




 /*  for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
           delete [] lMatrix[i][j];
       }
       delete [] lMatrix[i];
      }



      delete [] lMatrix;
*/


     delete [] data;
     return 0;
}
