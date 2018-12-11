#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void
process(const char* ims)
{
  Mat image;
  image = imread(ims, CV_LOAD_IMAGE_COLOR);
  if(!image.data)
    {
        cout <<  "Image not found" << std::endl ;
    }
  else
  {

    Mat image_gray;
    cvtColor(image, image_gray, CV_BGR2GRAY);
    imshow("otsu",image_gray);

    // Methode opencv
    Mat otsu_th_ocv;
    float a,seuil_otsu = threshold(image_gray, otsu_th_ocv,0,255, THRESH_BINARY|THRESH_OTSU);
    imshow("otsu-th-ocv",otsu_th_ocv);
    imwrite("otsu-th-ocv.png",otsu_th_ocv);
    (void)a;

    cout<<"ocv otsu threshold t = "<<seuil_otsu<<endl;

  }
}


void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 1
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  waitKey(0);
  return EXIT_SUCCESS;
}
