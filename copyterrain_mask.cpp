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
//#include <chrono>

#define PROCESSED 1
#define NOT_PROCESSED 0

using namespace cv;
using namespace std;
using namespace std::chrono;

milliseconds avg;
int nb_samples = 0;

void filter(Mat & mask){
  int dilation_type = MORPH_RECT;
  int dilation_size = 25;
  Mat element = getStructuringElement( dilation_type, Size( 2*dilation_size + 1, 2*dilation_size+1), Point( dilation_size, dilation_size ) );
  // Note that one label is the background
  morphologyEx(mask, mask, MORPH_OPEN, element);
  dilate(mask, mask, element);
}

void enveloppe_convexe(Mat mask, Mat & originale){
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
  // create a blank image (black image)
  Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
  vector < vector <Point> > myconvex(1);
  convexHull(Mat(hull_add[0]), myconvex[0]);
  Scalar color = Scalar(255, 255, 255); // red - color for convex hull
  drawContours(drawing, myconvex, -1, color, CV_FILLED, 8, vector<Vec4i>(), 0, Point());
  for(int i = 0; (unsigned)i < contours.size(); i++){
    //Scalar color_contours = Scalar(0, 255, 0); // green - color for contours
    Scalar color = Scalar(255, 255, 255); // red - color for convex hull
    // draw with contour
    drawContours(drawing, hull, i, color, CV_FILLED, 8, vector<Vec4i>(), 0, Point());
  }
  cvtColor(drawing, drawing, COLOR_BGR2GRAY);
  imshow("filter+convex",drawing);
  imwrite("filterconvex.png",drawing);
  for (int i = 0; i < originale.rows; i++){
    for (int j = 0; j < originale.cols; j++){
      Vec3b & p = originale.at<Vec3b>(i,j);
      unsigned char pp = drawing.at<unsigned char>(i,j);
      if (pp < 100){
	p = 0;
      }
    }
  }
}

int process_ims (const char * ims, const char * imd){
  milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
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
  int sensibility = 35;
  Scalar lower_green = Scalar(60-sensibility,0,0);
  Scalar  upper_green = Scalar(60+sensibility, 255, 255);
  Mat mask;
  inRange(hsv, lower_green, upper_green, mask);
  imshow("before filter", mask);
  filter(mask);
  enveloppe_convexe(mask, originale);
  imshow("final", originale);
  imwrite(imd, originale);
  milliseconds ms2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
  milliseconds c = ms2-ms;
  if (!nb_samples) avg = c;
  else avg = (avg * nb_samples + c)/(nb_samples+1);-rgb.png
  nb_samples++;
  waitKey(0);
  return PROCESSED;
}

/*void process(const char * folder, const char * imd){
  (void) imd;
  for (int i = 1; i <= 1000; i++){
    char ims[999];
    if (i < 10)
      sprintf(ims, "%s/00%d-rgb.png", folder, i);
    else if (i < 100)
      sprintf(ims, "%s/0%d-rgb.png", folder, i);
    else
      sprintf(ims, "%s/%d-rgb.png", folder, i);
    if (!process_ims(ims))
      break;
  }
  cout << avg.count() << endl;
}*/

void usage (const char *s){
  std::cerr<<"Usage: "<<s<<" folder_path \n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int main (int argc, char * argv[]){
  if (argc != (param+1)){
    usage(argv[0]);
  }
  process_ims(argv[1], argv[2]);
  return EXIT_SUCCESS;
}
