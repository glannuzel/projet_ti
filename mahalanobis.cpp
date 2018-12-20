#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imsname, int seuil)
{
  //Time calculation init
  clock_t start;
  double duration;
  start = clock();

  //Read picture and initialize dimensions
  Mat ims = imread(imsname);
  int rows = ims.rows;
  int cols = ims.cols;

  // Covariance and inverse of covariance matrixes initialization
  Mat cov_mat = Mat::zeros(3,3,CV_32F);
  Mat invCov_mat = Mat::zeros(3,3,CV_32F);

  /// READ MODEL FILE
  ifstream fichier("model.txt", ios::in);

  if(fichier)
  {
      float cov00, cov11, cov22, cov01, cov02, cov12, cov10, cov21, cov20;
      float meanB, meanG, meanR;
      fichier >> cov00 >> cov01 >> cov02 >> cov10 >> cov11 >> cov12 >> cov20 >> cov21 >> cov22;
      fichier >> meanB >> meanG >> meanR ;

      fichier.close();

      cov_mat.at<float>(0,0)=cov00;
      cov_mat.at<float>(1,1)=cov11;
      cov_mat.at<float>(2,2)=cov22;

      cov_mat.at<float>(0,1)=cov01;
      cov_mat.at<float>(1,0)=cov10;
      cov_mat.at<float>(0,2)=cov02;
      cov_mat.at<float>(2,0)=cov20;
      cov_mat.at<float>(1,2)=cov12;
      cov_mat.at<float>(2,1)=cov21;

      //Invert covariance matrix
      invert(cov_mat, invCov_mat, DECOMP_SVD);

      /// MAHALANOBIS DISTANCE CALCULATION FOR EACH PIXEL

      //Calculation on the channels and change of matrix format
      Mat mcouleur = Mat::zeros(rows*cols,3,CV_32F);
      for (int j=0; j<cols;j++)
      {
        for (int i=0; i< rows; i++)
        {
          mcouleur.at<float>(i+j*rows,0)=ims.at<Vec3b>(i,j)[0] - meanB;
          mcouleur.at<float>(i+j*rows,1)=ims.at<Vec3b>(i,j)[1] - meanG;
          mcouleur.at<float>(i+j*rows,2)=ims.at<Vec3b>(i,j)[2] - meanR;
        }
      }
      //Distance calculation
      Mat inter = Mat::zeros(rows*cols,3,CV_32F);
      inter = mcouleur * invCov_mat;
      Mat inter_transp;
      transpose(inter,inter_transp); //transpose inter
      Mat mcouleur_transp;
      transpose(mcouleur,mcouleur_transp); //transpose mcouleur
      Mat fusion;
      multiply(inter_transp,mcouleur_transp,fusion); //multiply inter_transp and m_transp

      // Mahalanobis image
      Mat mahalanobis_mat = Mat::zeros(rows,cols,CV_32F);
      for (int j=0; j<cols; j++)
      {
        for (int i=0; i<rows; i++)
        {
          mahalanobis_mat.at<float>(i,j)=fusion.at<float>(0,i+j*rows)+fusion.at<float>(1,i+j*rows)+fusion.at<float>(2,i+j*rows);
        }
      }

      // Processing time
      duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
      cout << "Mahalanobis calculation time : " << duration << endl;



      ///IMAGE BINARIZATION

      //initialize clock for processing time measurement
      start = clock();
      Mat binary_image = Mat::zeros(rows,cols,CV_8UC1);
      //A good threshold = 750;
      for (int i=0; i<rows; i++)
      {
        for (int j=0; j<cols; j++)
        {
          if(mahalanobis_mat.at<float>(i,j) <=seuil)
          {
            binary_image.at<uchar>(i,j) = 255;
          }
          else{
            binary_image.at<uchar>(i,j) = 0;
          }
        }
      }

      //Processing time measurement
      duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
      cout << "Thresholding and binarization : " << duration << endl;

      imshow("Binarisation Mahalanobis", binary_image);
      waitKey(0);


      //FILL IN HOLES (lines, balloon)

      //initialize clock for processing time measurement
      start = clock();
      Mat mahal_neg = binary_image.clone();
      floodFill(mahal_neg, cv::Point(0,0), Scalar(255));
      Mat mahal_neg_inv;
      bitwise_not(mahal_neg, mahal_neg_inv);
      binary_image = (binary_image | mahal_neg_inv);

      duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
      cout << "Fill in time : " << duration << endl;

/*
      int dilation_type = MORPH_RECT;
      int dilation_size = 4;
      Mat element = getStructuringElement(dilation_type, Size(2*dilation_size + 1, 2*dilation_size+1), Point(dilation_size, dilation_size ) );
      morphologyEx(binary_image, binary_image, MORPH_OPEN, element);
*/
      imwrite("mahalanobis.png",binary_image);

  }
  else
          cerr << "Impossible d'ouvrir le fichier !" << endl;

}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname threshold "<<endl;
  exit(EXIT_FAILURE);
}

#define param 2
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], atoi(argv[2]));
  return EXIT_SUCCESS;
}
