#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

enum {SQUARE, DIAMOND, DISK, LINE_V, DIAG_R, LINE_H, DIAG_L, CROSS, PLUS};

void
process(const int shape, const int halfsize, const char* imdname)
{
  Mat elmt_struct(2*halfsize+1, 2*halfsize+1,  CV_8UC1, Scalar(0));

  if( shape == SQUARE ){
    for(int i =0; i < 2*halfsize+1; i++)
    {
      for(int j =0; j < 2*halfsize+1; j++)
      {
        if(((abs(i-halfsize) > abs(j-halfsize))&& (abs(i-halfsize)<= halfsize))||((abs(i-halfsize) <= abs(j-halfsize))&& (abs(j-halfsize)<= halfsize))) elmt_struct.at<uchar>(i,j) = 255;
      }
    }
  }
  else if(shape == DIAMOND)
  {
    for(int i =0; i < 2*halfsize+1; i++)
    {
      for(int j =0; j < 2*halfsize+1; j++)
      {
        if(abs(i-halfsize)+abs(j-halfsize) <= halfsize) elmt_struct.at<uchar>(i,j) = 255;
      }
    }
  }
  else if(shape == DISK)
  {
    for(int i =0; i < 2*halfsize+1; i++)
    {
      for(int j =0; j < 2*halfsize+1; j++)
      {
        if(sqrt(pow(abs(i-halfsize),2)+pow(abs(j-halfsize),2)) <= halfsize) elmt_struct.at<uchar>(i,j) = 255;
      }
    }
  }
  else if(shape == LINE_V)
  {
    for(int i =0; i < 2*halfsize+1; i++)
    {
      for(int j =0; j < 2*halfsize+1; j++)
      {
        if(j==halfsize) elmt_struct.at<uchar>(i,j) = 255;
      }
    }
  }
  else if(shape == LINE_H)
  {
    for(int i =0; i < 2*halfsize+1; i++)
    {
      for(int j =0; j < 2*halfsize+1; j++)
      {
        if(i==halfsize) elmt_struct.at<uchar>(i,j) = 255;
      }
    }
  }
  else if(shape == PLUS)
  {
    for(int i =0; i < 2*halfsize+1; i++)
    {
      for(int j =0; j < 2*halfsize+1; j++)
      {
        if((i==halfsize)||(j==halfsize)) elmt_struct.at<uchar>(i,j) = 255;
      }
    }
  }
  else
  {
    if(shape == DIAG_L || shape == CROSS)
    {
      for(int i =0; i < 2*halfsize+1; i++)
      {
        for(int j =0; j < 2*halfsize+1; j++)
        {
          if((i==j)) elmt_struct.at<uchar>(i,j) = 255;
        }
      }
    }
    if(shape == DIAG_R || shape == CROSS)
    {
      for(int i =0; i < 2*halfsize+1; i++)
      {
        for(int j =0; j < 2*halfsize+1; j++)
        {
          if((2*halfsize-i==j)) elmt_struct.at<uchar>(i,j) = 255;
        }
      }
    }
  }
  imwrite(imdname, elmt_struct);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" shape halfsize se-name"<<endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), argv[3]);
  waitKey(0);
  return EXIT_SUCCESS;
}
