#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imsname)
{
  Mat ims = imread(imsname);

  Mat img_out = ims.clone();

  int rows = ims.rows;
  int cols = ims.cols;

  // Crop area to make the model
  Rect areaToCrop(cols/2,rows/2,cols/2-20,rows/2-20);
  Mat cropped_image_ocv=image(areaToCrop);

  imshow("crop-ocv.png",cropped_image_ocv);

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
