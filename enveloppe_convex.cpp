//https://docs.opencv.org/2.4/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html?highlight=convexhull#convexhull

#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void
process(const char* ims, const char* imd)
{
  //Time calculation init
  clock_t start;
  double duration;
  start = clock();


  Mat image;
  image = imread(ims, CV_LOAD_IMAGE_GRAYSCALE);

  blur( image, image, Size(3,3) );

  Mat threshold_output;
  threshold(image, threshold_output, 50, 255, THRESH_BINARY);

  vector< vector<Point> > contours; // list of contour points
  vector<Vec4i> hierarchy;
  // find contours
  findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Contours finding time : " << duration << endl;


  start = clock();
  // create hull array for convex hull points
  vector< vector<Point> > hull(contours.size());
  for(int i = 0; (unsigned)i < contours.size(); i++)
  {
    convexHull(Mat(contours[i]), hull[i]);
  }
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Convex hulls calculation time : " << duration << endl;

  start = clock();
  vector < vector<Point> > hull_add(1);
  for (int i = 0; (unsigned)i < hull.size(); i++)
  {
    for (int j = 0; (unsigned)j < hull[i].size(); j++)
    {
      hull_add[0].push_back(hull[i][j]);
    }
  }


  vector < vector <Point> > myconvex(1);
  convexHull(Mat(hull_add[0]), myconvex[0]);

  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Union of convex hulls time : " << duration << endl;


  Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
  Scalar color = Scalar(255, 0, 255); // red - color for convex hull
  drawContours(drawing, myconvex, -1, color);

/*
  // create a blank image (black image)
  Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);

  for(int i = 0; (unsigned)i < contours.size(); i++)
  {
      Scalar color_contours = Scalar(0, 255, 0); // green - color for contourscontours
      //Scalar color = Scalar(0, 0, 255); // red - color for convex hull
      // draw with contour
      drawContours(drawing, contours, 0, color_contours, 1, 8, vector<Vec4i>(), 0, Point());
      // draw wth convex hull
      //drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
  }
*/

    imshow("convex",drawing);
    imwrite(imd,drawing);
}


void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2]);
  waitKey(0);
  return EXIT_SUCCESS;
}
