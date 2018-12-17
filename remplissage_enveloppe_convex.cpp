#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void
process(const char* ims, const char* imd)
{
  Mat image;
  image = imread(ims, CV_LOAD_IMAGE_COLOR);


  if(!image.data)
    {
        cout <<  "Image not found" << std::endl ;
    }
  else
  {
    Mat edgesIn;
    Mat filledEdgesOut;
    Mat edgesNeg =image.clone();
    cv::floodFill(edgesNeg, cv::Point(0,0), CV_RGB(255,255,255));
    cv::bitwise_not(edgesNeg, edgesNeg);
    filledEdgesOut = (edgesNeg | image);
    imshow(imd, filledEdgesOut);
    imwrite(imd, filledEdgesOut);
  }
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
  process(argv[1], argv[2]);
  waitKey(0);
  return EXIT_SUCCESS;
}
