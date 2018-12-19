#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void
process(const char* ims, const char* imd, const char* stru1, const char* stru2)
{
  //Time calculation init
  clock_t start;
  double duration;
  start = clock();


  Mat image;
  Mat stru_elmt1; Mat stru_elmt2;

  image = imread(ims, CV_LOAD_IMAGE_COLOR);
  stru_elmt1 = imread(stru1, CV_LOAD_IMAGE_GRAYSCALE);
  stru_elmt2 = imread(stru2, CV_LOAD_IMAGE_GRAYSCALE);

  if(!image.data || !stru_elmt1.data || !stru_elmt2.data)
    {
        cout <<  "Image not found" << std::endl ;
    }
  else
  {

    Mat image_gray;
    cvtColor(image, image_gray, CV_BGR2GRAY);

    //Load
    Mat image_init = image_gray.clone();
    Mat image_dest = image_gray.clone();
    Mat image_dest2 = image_gray.clone();


    int nb_erosions1 = 3;
    int nb_erosions2 = 2;

    //Erosion
    erode(image_gray, image_dest, stru_elmt1, Point(-1,-1), nb_erosions1);
    erode(image_dest, image_dest2, stru_elmt2, Point(-1,-1), nb_erosions2);

    //Dilation
    dilate(image_dest2, image_dest, stru_elmt1, Point(-1,-1), nb_erosions1);
    dilate(image_dest, image_dest2, stru_elmt2, Point(-1,-1), nb_erosions2);

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "Erosion and dilation time : " << duration << endl;

    imshow(imd,image_dest2);
    imwrite(imd, image_dest2);

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
