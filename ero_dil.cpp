#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void
process(const char* ims, const char* imd, const char* stru)
{
  //Time calculation init
  clock_t start;
  double duration;
  start = clock();


  Mat image;
  Mat stru_elmt;

  image = imread(ims, CV_LOAD_IMAGE_COLOR);
  stru_elmt = imread(stru, CV_LOAD_IMAGE_COLOR);
  if(!image.data || !stru_elmt.data)
    {
        cout <<  "Image not found" << std::endl ;
    }
  else
  {

    Mat image_gray;
    cvtColor(image, image_gray, CV_BGR2GRAY);
    //imshow("Image grise",image_gray);

    Mat stru_elmt_gray;
    cvtColor(stru_elmt, stru_elmt_gray, CV_BGR2GRAY);


    Mat image_dest = image_gray.clone();

    int nb_erosions = 4;
    erode(image_gray, image_dest, stru_elmt_gray, Point(-1,-1), nb_erosions);
    //imshow("Image erodee",image_dest);

    Mat image_dest2 = image_gray.clone();

    dilate(image_dest, image_dest2, stru_elmt_gray, Point(-1,-1), nb_erosions);


    //imshow("Image erodee puis dilatee",image_dest2);

    int nb_dilatation = 4;
    dilate(image_dest2, image_dest, stru_elmt_gray, Point(-1,-1), nb_dilatation);
    //imshow("Image re dilatee",image_dest);

    erode(image_dest, image_dest2, stru_elmt_gray, Point(-1,-1), nb_dilatation);

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

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2], argv[3]);
  waitKey(0);
  return EXIT_SUCCESS;
}
