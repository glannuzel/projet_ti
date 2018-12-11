#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define H 0
#define S 1
#define V 2

/*
Change a channel value
 */
void adjust_channel(Mat &image, const int shift, const int channel){
  int col_size = image.cols;
  int row_size = image.rows;
  for (int i = 0; i < row_size; i++){
    for (int j = 0; j < col_size; j++){
      Vec3b &pixel = image.at<Vec3b>(i,j);
      if (pixel[channel] + shift <= 255)
	pixel[channel] += shift;
      else
	pixel[channel] = 255;
    }
  }
}

void process (const char * ims, const char * imd){
  Mat image=imread(ims);
  if (!image.data){
    cout << "Error loading image" << endl;
    exit(EXIT_FAILURE);
  }
  if (image.type() != CV_8UC3)
    image.convertTo(image, CV_8UC3);

  Mat hsv;
  cvtColor(image, hsv, COLOR_BGR2HSV);
  int sensibility = 25;
  Scalar lower_green = Scalar(60-sensibility,0,0);
  Scalar  upper_green =Scalar(60+sensibility,255,255);
  Mat mask;
  inRange(hsv, lower_green, upper_green, mask);
  imshow("f", mask);
  imwrite(imd, mask);

  waitKey(0);
}

void usage (const char *s){
  std::cerr<<"Usage: "<<s<<" imsname \n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int main (int argc, char * argv[]){
  if (argc != (param+1)){
    usage(argv[0]);
  }
  process(argv[1], argv[2]);
  return EXIT_SUCCESS;
}
