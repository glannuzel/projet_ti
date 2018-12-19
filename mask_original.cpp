#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void
process(const char* ims_mask, const char* ims_originale, const char* imd)
{
  Mat mask;
  ims_mask = imread(ims_mask, CV_LOAD_IMAGE_COLOR);
  Mat image_originale;
  image_originale = imread(ims_originale, CV_LOAD_IMAGE_COLOR);
  Mat mask_original = image_originale.clone();

  if(!image.data)
    {
        cout <<  "Image not found" << std::endl ;
    }
  else
  {
    for(int i=0;i<image_originale.size().height;i++)
    {
      for(int j=0;j<image_originale.size().width;j++)
      {
        if(ims_mask.at<Vec3b>(i,j)[0] != 255)
        {
        mask_originale.at<Vec3b>(i,j)[0] = 0;
        mask_originale.at<Vec3b>(i,j)[1] = 0;
        mask_originale.at<Vec3b>(i,j)[2] = 0;
      }
      }
    }

    imshow(imd, mask_originale);
    imwrite(imd, mask_originale);
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
