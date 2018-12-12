//https://docs.opencv.org/2.4/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html?highlight=convexhull#convexhull

#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void
process(const char* ims)
{
  Mat image;
  image = imread(ims, CV_LOAD_IMAGE_GRAYSCALE);

  Mat threshold_output;
  threshold(image, threshold_output, 50, 255, THRESH_BINARY);

  vector< vector<Point> > contours; // list of contour points
  vector<Vec4i> hierarchy;
  // find contours
  findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

  cout << contours.size() << endl;

  // create hull array for convex hull points
  vector< vector<Point> > hull(contours.size());
  for(int i = 0; (unsigned)i < contours.size(); i++)
  {
    convexHull(Mat(contours[i]), hull[i]);
  }

  // create a blank image (black image)
  Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);

  for(int i = 0; (unsigned)i < contours.size(); i++)
  {
      //Scalar color_contours = Scalar(0, 255, 0); // green - color for contours
      Scalar color = Scalar(0, 0, 255); // red - color for convex hull
      // draw with contour
      //drawContours(drawing, contours, i, color_contours, 1, 8, vector<Vec4i>(), 0, Point());
      // draw wth convex hull
      drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
  }

    imshow("convex",drawing);

}


void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 1
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  waitKey(0);
  return EXIT_SUCCESS;
}
