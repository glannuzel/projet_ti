#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imsname)
{
  //Time calculation init
  clock_t start;
  double duration;
  start = clock();

  // Read source image and initialize dimensions
  Mat ims = imread(imsname);
  int rows = ims.rows;
  int cols = ims.cols;

  Mat cov_mat = Mat::zeros(3,3,CV_32F); // covariance matrix init

  // Crop area to make the model
  Rect areaToCrop(515,189,9,4);
  Mat cropped_image_ocv=ims(areaToCrop);
  rows = cropped_image_ocv.rows;
  cols = cropped_image_ocv.cols;

  // Means
  //Separate color channels
  Mat canalR = Mat::zeros(rows,cols,CV_8UC1);
  Mat canalG = Mat::zeros(rows,cols,CV_8UC1);
  Mat canalB = Mat::zeros(rows,cols,CV_8UC1);
  for (int i=0; i<rows;i++)
  {
    for(int j=0; j<cols;j++)
    {
      canalB.at<uchar>(i,j)=cropped_image_ocv.at<Vec3b>(i,j)[0];
      canalG.at<uchar>(i,j)=cropped_image_ocv.at<Vec3b>(i,j)[1];
      canalR.at<uchar>(i,j)=cropped_image_ocv.at<Vec3b>(i,j)[2];
    }
  }
  //Means calculation
  Scalar meanR = mean(canalR);
  Scalar meanG = mean(canalG);
  Scalar meanB = mean(canalB);

  //Covariance Calculation
  //Set channels' values in columns
  Mat canalB_col = Mat::zeros(cols*rows,1,CV_8UC1);
  Mat canalR_col = Mat::zeros(cols*rows,1,CV_8UC1);
  Mat canalG_col = Mat::zeros(cols*rows,1,CV_8UC1);

  for (int j =0; j<cols; j++)
  {
    for (int i=0; i<rows; i++)
    {
      canalB_col.at<uchar>(i+j*rows,0) = canalB.at<uchar>(i,j);
      canalG_col.at<uchar>(i+j*rows,0) = canalG.at<uchar>(i,j);
      canalR_col.at<uchar>(i+j*rows,0) = canalR.at<uchar>(i,j);
    }
  }

  Mat pow2R, pow2G, pow2B;

  Mat diffR = Mat::zeros(cols*rows,1,CV_32F);
  Mat diffB = Mat::zeros(cols*rows,1,CV_32F);
  Mat diffG = Mat::zeros(cols*rows,1,CV_32F);

  //substract means to colors
  for(int i =0; i< rows*cols; i++)
  {
      diffR.at<float>(i,0) = canalR_col.at<uchar>(i,0) - meanR[0];
      diffB.at<float>(i,0) = canalB_col.at<uchar>(i,0) - meanB[0];
      diffG.at<float>(i,0) = canalG_col.at<uchar>(i,0) - meanG[0];
  }
  //square the values
  pow(diffB,2,pow2B);
  pow(diffG,2,pow2G);
  pow(diffR,2,pow2R);
  //Save values in the covariance matrix's diagonal
  cov_mat.at<float>(0,0)=mean(pow2B)[0];
  cov_mat.at<float>(1,1)=mean(pow2G)[0];
  cov_mat.at<float>(2,2)=mean(pow2R)[0];

  //Calculate other terms of the covariance matrix
  Mat bg, br, gr;
  multiply(diffB,diffG,bg);
  multiply(diffB,diffR,br);
  multiply(diffG,diffR,gr);

  cov_mat.at<float>(0,1)=mean(bg)[0];
  cov_mat.at<float>(1,0)=cov_mat.at<float>(0,1); //symetric matrix
  cov_mat.at<float>(0,2)=mean(br)[0];
  cov_mat.at<float>(2,0)=cov_mat.at<float>(0,2); //symetric matrix
  cov_mat.at<float>(1,2)=mean(gr)[0];
  cov_mat.at<float>(2,1)=cov_mat.at<float>(1,2); //symetric matrix


  //Save model
  fstream fichier("model.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

    if(fichier)
    {
            //Save covariance matrix
            fichier << cov_mat.at<float>(0,0) << endl;
            fichier << cov_mat.at<float>(0,1) << endl;
            fichier << cov_mat.at<float>(0,2) << endl;

            fichier << cov_mat.at<float>(1,0) << endl;
            fichier << cov_mat.at<float>(1,1) << endl;
            fichier << cov_mat.at<float>(1,2) << endl;

            fichier << cov_mat.at<float>(2,0) << endl;
            fichier << cov_mat.at<float>(2,1) << endl;
            fichier << cov_mat.at<float>(2,2) << endl;

            //Save mean for each channel
            fichier << meanB[0] << endl;
            fichier << meanG[0] << endl;
            fichier << meanR[0] << endl;

            fichier.close();
    }
    else
    {
            cerr << "Impossible d'ouvrir le fichier !" << endl;
    }

    //Calculate and display processing time
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "Initialisation time : " << duration << endl;
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname "<<endl;
  exit(EXIT_FAILURE);
}

#define param 1
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  return EXIT_SUCCESS;
}
