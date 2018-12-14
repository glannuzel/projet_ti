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

using namespace cv;
using namespace std;

#define H 0
#define S 1
#define V 2

Mat detect(Mat image, int attempts, int clusterCount){
  Mat samples(image.rows * image.cols, 3, CV_32F);
  for( int y = 0; y < image.rows; y++ )
    for( int x = 0; x < image.cols; x++ )
      for( int z = 0; z < 3; z++)
        samples.at<float>(y + x*image.rows, z) = image.at<Vec3b>(y,x)[z];
  Mat labels;
  Mat centers;
  kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 25, 0.00001), attempts, KMEANS_PP_CENTERS, centers);
  Mat new_image( image.size(), image.type() );
  for( int y = 0; y < image.rows; y++ )
    for( int x = 0; x < image.cols; x++ )
      {
	int cluster_idx = labels.at<int>(y + x*image.rows,0);
	new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
	new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
	new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
      }
  return new_image;
}

bool has_white_contour(Mat image, float threshold){
  long count = 0;
  for (int i = 0; i < image.rows; i++){
    for (int j = 0; j < image.cols; j++){
      if (image.at<unsigned char>(i, j) >= 200) count++;
    }
  }
  if (count / (float)(image.cols*image.rows) > threshold)
    return true;
  return false;
}

void remove_glitch(Mat & image, int size, int step, float threshold){
  for (int i = 0; i < image.rows; i+=step){
    for (int j = 0; j < image.cols; j+=step){
      if (j+size < image.cols && i+size < image.rows){
	Mat subImage = Mat(image, Rect(j, i, size, size));
	bool b = has_white_contour(subImage, threshold);
	if (b){
	  for (int ii = i; ii < i+size; ii++){
	    for (int jj = j; jj < j+size; jj++){
	      image.at<unsigned char>(ii, jj) = 255;
	    }
	  }
	}	
      }      
    }
  }
}

void colorFilter(Mat & mask, Mat & originale){  
  blur(mask, mask, Size(40,40));
  for (int ii = 0; ii < 1; ii++){
    for (int i = 0; i < originale.rows; i++){
      for (int j = 0; j < originale.cols; j++){
	unsigned char & pp = mask.at<unsigned char>(i,j);
	if (pp < 225)
	  pp = 0;
	else
	  pp = 255;
      }
    }
  }
  int dilation_type = MORPH_ELLIPSE;
  int dilation_size = 10;
  Mat element = getStructuringElement( dilation_type, Size( 2*dilation_size + 1, 2*dilation_size+1), Point( dilation_size, dilation_size ) );
  dilate(mask, mask, element);
  remove_glitch(mask, 5, 1, 0.9);  
}

void process_ims (const char * ims){
  Mat image=imread(ims);
  if (!image.data){
    cout << "Error loading image" << endl;
    exit(EXIT_FAILURE);
  }
  if (image.type() != CV_8UC3)
    image.convertTo(image, CV_8UC3);
  Mat originale = image.clone();
  Mat image_blur;
  //GaussianBlur(image, image_blur, Point(0, 0), 3);
  //addWeighted(image, 1.5, image_blur, -1, 0, image);
  // Mat new_image = detect(image, 1, 10);
  
  Mat hsv;
  cvtColor(image, hsv, COLOR_BGR2HSV);
  int sensibility = 35;
  Scalar lower_green = Scalar(60-sensibility,0,0);
  Scalar  upper_green = Scalar(60+sensibility, 255, 255);
  Mat mask;
  inRange(hsv, lower_green, upper_green, mask);
  colorFilter(mask, originale);



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
  // create a blank image (black image)
  Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
  for(int i = 0; (unsigned)i < contours.size(); i++){
      //Scalar color_contours = Scalar(0, 255, 0); // green - color for contours
      Scalar color = Scalar(255, 255, 255); // red - color for convex hull
      // draw with contour
      // draw wth convex hull
      drawContours(drawing, hull, i, color, CV_FILLED, 8, vector<Vec4i>(), 0, Point());
    }
  cvtColor(drawing, drawing, COLOR_BGR2GRAY);
  imshow("convex",drawing);
  // drawing = mask;
  for (int i = 0; i < originale.rows; i++){
    for (int j = 0; j < originale.cols; j++){
      Vec3b & p = originale.at<Vec3b>(i,j);
      unsigned char pp = drawing.at<unsigned char>(i,j);
      if (pp < 100){
	p.val[0] = 0;
	p.val[1] = 0;
	p.val[2] = 0;
      }
    }
  }
  imshow("ims", originale);
  waitKey(0);
}

void process(void){
  for (int i = 262; i <= 374; i++){
    char ims[999];
    if (i < 10)
      sprintf(ims, "log1/00%d-rgb.png", i);
    else if (i < 100)
      sprintf(ims, "log1/0%d-rgb.png", i);
    else
      sprintf(ims, "log1/%d-rgb.png", i);
    process_ims(ims);
  }
}

void usage (const char *s){
  std::cerr<<"Usage: "<<s<<" \n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 0
int main (int argc, char * argv[]){
  if (argc != (param+1)){
    usage(argv[0]);
  }
  process();
  return EXIT_SUCCESS;
}
