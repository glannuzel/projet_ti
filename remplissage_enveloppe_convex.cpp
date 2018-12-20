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
  Mat element_struct = imread("1.png",CV_LOAD_IMAGE_GRAYSCALE);

  if(!image.data)
    {
        cout <<  "Image not found" << std::endl ;
    }
  else
  {
    Mat edgesIn;
    Mat filledEdgesOut;
    Mat mask;
    Mat edgesNeg =image.clone();

    //Time calculation init
    clock_t start;
    double duration;
    start = clock();

    //Fill in the convex hull
    cv::floodFill(edgesNeg, cv::Point(0,0), CV_RGB(255,255,255));
    cv::bitwise_not(edgesNeg, edgesNeg);
    filledEdgesOut = (edgesNeg | image);

    //Dilate to retrieve the pixel left on each side of the convex hull
    dilate(filledEdgesOut,mask,element_struct,Point(-1,-1),1);

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "Fill in convex hull and last dilation : " << duration << endl;

    imshow(imd, mask);
    imwrite(imd, mask);

  }
}


void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims imd\n"<<std::endl;
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
