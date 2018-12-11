#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imboundary, const char* imsname, const char* imdname)
{
  Mat img_bound = imread(imboundary,CV_LOAD_IMAGE_GRAYSCALE);
  Mat ims = imread(imsname);

  Mat img_out = ims.clone();

  int rows = ims.rows;
  int cols = ims.cols;

  for (int i=0; i <rows;i++)
  {
    for(int j =0; j<cols; j++)
    {
      if(img_bound.at<uchar>(i,j) == 255)
      {
        img_out.at<Vec3b>(i,j)[2]= 255;
        img_out.at<Vec3b>(i,j)[0] = 0;
        img_out.at<Vec3b>(i,j)[1] = 0;
      }
    }
  }

  imwrite(imdname,img_out);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname imsname2 imdname "<<endl;
  exit(EXIT_FAILURE);
}

#define param 1
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  return EXIT_SUCCESS;
}
