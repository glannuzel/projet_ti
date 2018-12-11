#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define RED 2
#define GREEN 1
#define BLUE 0

Mat to_gray(Mat image){
  int col_size = image.cols;
  int row_size = image.rows;  
  Mat out = Mat(row_size, col_size, CV_8UC1);
  for (int i = 0; i < row_size; i++){
    for (int j = 0; j < col_size; j++){
      Vec3b p = image.at<Vec3b>(i,j);
      double ratio = 1.0;
      if (p.val[RED]+p.val[BLUE] != 0)
	ratio = p.val[GREEN]/((p.val[RED]+p.val[BLUE])/2.);
      else if (p.val[GREEN] == 0)
	ratio = 0.0;
      unsigned char & p_out = out.at<unsigned char>(i,j);
      p_out = ratio * 255;
    }
  }
  return out;
}


void process (const char * ims){
  Mat image=imread(ims);
  if (!image.data){
    cout << "Error loading image" << endl;
    exit(EXIT_FAILURE);
  }
  if (image.type() != CV_8UC3)
    image.convertTo(image, CV_8UC3);   
  
  Mat out = to_gray(image);
  equalizeHist(out,out);
  // adaptiveThreshold(out, out, 100, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 7, -20);
  imshow("fds", out);
  waitKey(0);
  Mat hsv;
  cvtColor(image, hsv, COLOR_BGR2HSV);
  int sensibility = 60;
  Scalar lower_green = Scalar(60-sensibility,100,100);
  Scalar  upper_green =Scalar(60+sensibility,255,255);
  Mat mask;
  inRange(hsv, lower_green, upper_green, mask);
  imshow("f", mask);
  waitKey(0);
}

void usage (const char *s){
  std::cerr<<"Usage: "<<s<<" imsname \n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 1
int main (int argc, char * argv[]){
  if (argc != (param+1)){
    usage(argv[0]);
  }
  process(argv[1]);
  return EXIT_SUCCESS;
}

