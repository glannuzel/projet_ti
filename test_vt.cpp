#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void
process(const char* ims, const char* env)
{
  Mat image;
  image = imread(ims);
  Mat envel = imread(env, CV_LOAD_IMAGE_GRAYSCALE);
  int rows = image.rows;
  int cols = image.cols;

  Mat img_test = Mat::zeros(rows,cols,CV_8UC3);
  Vec3b vecteur(255,0,255);

  for (int i =0; i<rows; i++)
  {
    for (int j=0; j<cols; j++)
    {
      if (envel.at<uchar>(i,j) == 0)
      {
        img_test.at<Vec3b>(i,j) = image.at<Vec3b>(i,j);
      }
      else
      {
        img_test.at<Vec3b>(i,j) = vecteur;
      }
    }
  }

  imshow("Test verite", img_test);

}


void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1],argv[2]);
  waitKey(0);
  return EXIT_SUCCESS;
}
