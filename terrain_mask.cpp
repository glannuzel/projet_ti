#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <math.h>
#include <stdio.h>

#define PROCESSED 1
#define NOT_PROCESSED 0

using namespace cv;
using namespace std;

/*
  \brief Filter the undesirable objects from the mask
  \parameter in/out mask the mask
  \parameter in oversize the size for a structuring element used to dilate the mask (optional). That enables to detect a bit more than the field (to improve recall but lower the precision)
 */
void filter(Mat & mask, int oversize = 0){    
  int dilation_type = MORPH_RECT;
  int dilation_size = 25;
  Mat element = getStructuringElement(dilation_type, Size(2*dilation_size + 1, 2*dilation_size+1), Point(dilation_size, dilation_size ) );
  morphologyEx(mask, mask, MORPH_OPEN, element);
  if (oversize){
    dilation_size = oversize;
    element = getStructuringElement(dilation_type, Size( 2*dilation_size + 1, 2*dilation_size+1), Point( dilation_size, dilation_size ) );
    dilate(mask, mask, element);
  }
}

/**
   \brief compute a convex hull from the mask. That enables to include some not green objects on the field such as the ball, the players or the lines
   \parameter in/out mask the mask to compute the convex hull
 */
void convex_hull(Mat & mask){
  Mat threshold_output = mask.clone();
  vector< vector<Point> > contours; // list of contour points
  vector<Vec4i> hierarchy;
  // find contours
  findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_TC89_L1, Point(0, 0));
  // create hull array for convex hull points
  vector< vector<Point> > hull(contours.size());
  for(int i = 0; (unsigned)i < contours.size(); i++){
    convexHull(Mat(contours[i]), hull[i]);
  }
  vector < vector<Point> > hull_add(1);
  for (int i = 0; (unsigned)i < hull.size(); i++){
      for (int j = 0; (unsigned)j < hull[i].size(); j++){
	  hull_add[0].push_back(hull[i][j]);
      }
  }
  Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
  vector < vector <Point> > myconvex(1);
  convexHull(Mat(hull_add[0]), myconvex[0]);
  Scalar color = Scalar(255, 255, 255); // red - color for convex hull
  drawContours(drawing, myconvex, -1, color, CV_FILLED, 8, vector<Vec4i>(), 0, Point());
  cvtColor(drawing, drawing, COLOR_BGR2GRAY);
  mask = drawing;
}

/**
   \brief process an image to obtain a mask of the field
   \parameter ims the input image
   \parameter imd the destination path for the mask
   \parameter oversize optionnal to increase the size of the mask
   \return PROCESSED if ok, NOT_PROCESSED if not
 */
int process_ims (const char * ims, const char * imd, int oversize = 0){
  Mat image=imread(ims);
  if (!image.data){
    return NOT_PROCESSED;
  }
  if (image.type() != CV_8UC3)
    image.convertTo(image, CV_8UC3);
  Mat originale = image.clone();
  Mat image_blur;  
  Mat hsv;
  cvtColor(image, hsv, COLOR_BGR2HSV);
  int sensibility = 40;
  Scalar lower_green = Scalar(60-sensibility,0,0);
  Scalar  upper_green = Scalar(60+sensibility, 255, 255);
  Mat mask;
  inRange(hsv, lower_green, upper_green, mask);
  filter(mask, oversize);  
  convex_hull(mask);  
  imwrite(imd, mask);
  return PROCESSED;
}

void usage (const char *s){
  std::cerr<<"Usage: "<<s<<" <image path> <mask dest> <mask oversize> \n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int main (int argc, char * argv[]){
  if (argc != (param+1)){
    usage(argv[0]);
  }
  if (process_ims(argv[1], argv[2], atoi(argv[3])))
    return EXIT_SUCCESS;
  return EXIT_FAILURE;
}
