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

  //Read image
  Mat image;
  image = imread(ims, CV_LOAD_IMAGE_GRAYSCALE);

  //Blur image
  blur( image, image, Size(3,3) );
  // Binarize image
  Mat threshold_output;
  threshold(image, threshold_output, 50, 255, THRESH_BINARY);

  /// CONTOURS

  vector< vector<Point> > contours; // list of contour points
  vector<Vec4i> hierarchy;
  // find contours
  findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

  //Processing time to find contours
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Contours finding time : " << duration << endl;


  /// CONVEX HULL

  //initialize time measurement for convex hulls' calculation
  start = clock();
  // create hull array for convex hull points
  vector< vector<Point> > hull(contours.size());
  for(int i = 0; (unsigned)i < contours.size(); i++)
  {
    convexHull(Mat(contours[i]), hull[i]);
  }
  //processing time for convexHull calculation
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Convex hulls calculation time : " << duration << endl;

  //initialize time measurement for union of convex hulls' calculation
  start = clock();
  vector < vector<Point> > hull_add(1); //all the points in one vector
  for (int i = 0; (unsigned)i < hull.size(); i++)
  {
    for (int j = 0; (unsigned)j < hull[i].size(); j++)
    {
      hull_add[0].push_back(hull[i][j]);
    }
  }
  //Calulate the union of all the convex hulls
  vector < vector <Point> > myconvex(1);
  convexHull(Mat(hull_add[0]), myconvex[0]);
  //Calculate and display
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Union of convex hulls time : " << duration << endl;


  // DRAW CONVEX HULL

  Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
  Scalar color = Scalar(255, 0, 255); // magenta - color for convex hull
  drawContours(drawing, myconvex, -1, color);


  imshow("convex",drawing);
  imwrite(imd,drawing);
}


void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims imd\n"<<std::endl;
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
