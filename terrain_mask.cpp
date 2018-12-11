#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define H 0
#define S 1
#define V 2

void process (const char * ims){
  Mat image=imread(ims);
  if (!image.data){
    cout << "Error loading image" << endl;
    exit(EXIT_FAILURE);
  }
  if (image.type() != CV_8UC3)
    image.convertTo(image, CV_8UC3);   
  
  Mat samples(image.rows * image.cols, 3, CV_32F);
  for( int y = 0; y < image.rows; y++ )
    for( int x = 0; x < image.cols; x++ )
      for( int z = 0; z < 3; z++)
        samples.at<float>(y + x*image.rows, z) = image.at<Vec3b>(y,x)[z];


  int clusterCount = 10;
  Mat labels;
  int attempts = 1;
  Mat centers;
  kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 100, 0.0001), attempts, KMEANS_PP_CENTERS, centers );


  Mat new_image( image.size(), image.type() );
  for( int y = 0; y < image.rows; y++ )
    for( int x = 0; x < image.cols; x++ )
      { 
	int cluster_idx = labels.at<int>(y + x*image.rows,0);
	new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
	new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
	new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
      }
  imshow( "clustered image", new_image );
  waitKey( 0 ); 


  Mat hsv;
  cvtColor(new_image, hsv, COLOR_BGR2HSV);
  int sensibility = 30;
  Scalar lower_green = Scalar(60-sensibility,0,0);
  Scalar  upper_green =Scalar(60+sensibility,255,255);
  Mat mask;
  inRange(hsv, lower_green, upper_green, mask);
  imshow("f", mask);
  waitKey(0);
  /*Mat imageG = Mat(image.rows, image.cols, CV_8UC1);
    cvtColor(image, imageG, COLOR_BGR2GRAY);
    std::vector<std::vector<cv::Point> > contours;
  findContours(imageG, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
  imshow("dfs", imageG);  
  waitKey(0);
  cv::Mat contourImage(image.size(), CV_8UC3, cv::Scalar(0,0,0));
  cv::Scalar colors[3];
  colors[0] = cv::Scalar(255, 0, 0);
  colors[1] = cv::Scalar(0, 255, 0);
  colors[2] = cv::Scalar(0, 0, 255);
  for (size_t idx = 0; idx < contours.size(); idx++) {
    cv::drawContours(imageG, contours, idx, colors[idx % 3]);
  }
  imshow("dffdss", contourImage);  
  waitKey(0);*/
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

