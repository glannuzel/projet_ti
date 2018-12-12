#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void
process(const char* ims, const char* masque, const char* imd_1,  const char* imd_2)
{
  Mat image;
  Mat mask;

  image = imread(ims, CV_LOAD_IMAGE_COLOR);
  mask = imread(masque, CV_LOAD_IMAGE_COLOR);


  if(!image.data||!mask.data)
    {
        cout <<  "Image not found" << std::endl ;
    }
  else
  {

    Mat image_gray;
    cvtColor(image, image_gray, CV_BGR2GRAY);
    imshow(ims,image);


    Mat mask_gray;
    cvtColor(mask, mask_gray, CV_BGR2GRAY);
    Mat mask_gray_float;
    mask_gray.convertTo(mask_gray_float, CV_32FC1);


    Mat image_dest_1 = image.clone();
    Mat image_dest_2 = image.clone();
    Vec3b vecteur(0,0,0);

    for(int i=0;i<image_gray.size().height;i++)
    {
      for(int j=0;j<image_gray.size().width;j++)
      {

        if (mask_gray_float.at<float>(i,j) == 0)
        {
          image_dest_1.at<Vec3b>(i,j) = vecteur;
        }
        else{
          image_dest_2.at<Vec3b>(i,j) = vecteur;
        }
      }
    }

    imshow(imd_1, image_dest_1);
    imshow(imd_2, image_dest_2);
  }
}


void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 4
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2], argv[3], argv[4]);
  waitKey(0);
  return EXIT_SUCCESS;
}
