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

  Mat ims = imread(imsname);
  int rows = ims.rows;
  int cols = ims.cols;

  Mat cov_mat = Mat::zeros(3,3,CV_32F);
  Mat invCov_mat = Mat::zeros(3,3,CV_32F);

  ifstream fichier("test.txt", ios::in);

  if(fichier)
  {
      float cov00, cov11, cov22, cov01, cov02, cov12, cov10, cov21, cov20;
      float meanB, meanG, meanR;
      fichier >> cov00 >> cov01 >> cov02 >> cov10 >> cov11 >> cov12 >> cov20 >> cov21 >> cov22;
      fichier >> meanB >> meanG >> meanR ;
      /*on lit jusqu'à l'espace et on stocke ce qui est lu dans la variable indiquée */

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

      invert(cov_mat, invCov_mat, DECOMP_SVD);

      //Affichage des canaux R, G et B
      Mat canalR = Mat::zeros(rows,cols,CV_8UC1);
      Mat canalG = Mat::zeros(rows,cols,CV_8UC1);
      Mat canalB = Mat::zeros(rows,cols,CV_8UC1);

      for (int i=0; i<rows;i++)
      {
        for(int j=0; j<cols;j++)
        {
          canalB.at<uchar>(i,j)=ims.at<Vec3b>(i,j)[0];
          canalG.at<uchar>(i,j)=ims.at<Vec3b>(i,j)[1];
          canalR.at<uchar>(i,j)=ims.at<Vec3b>(i,j)[2];
        }
      }

      Mat icouleur = Mat::zeros(rows*cols*3,1,CV_8UC1);

      for (int j=0; j<cols;j++)
      {
        for (int i=0; i< rows; i++)
        {
          icouleur.at<uchar>(i+j*rows,0)=canalB.at<uchar>(i,j);
          icouleur.at<uchar>(cols*rows+(i+j*rows),0)=canalG.at<uchar>(i,j);
          icouleur.at<uchar>(cols*rows*2+i+j*rows,0)=canalR.at<uchar>(i,j);
        }
      }

      Mat mcouleur = Mat::zeros(rows*cols,3,CV_32F);

      for (int j=0; j<cols;j++)
      {
        for (int i=0; i< rows; i++)
        {
          mcouleur.at<float>(i+j*rows,0)=icouleur.at<uchar>(i+j*rows,0);
          mcouleur.at<float>(i+j*rows,1)=icouleur.at<uchar>(cols*rows+(i+j*rows),0);
          mcouleur.at<float>(i+j*rows,2)=icouleur.at<uchar>(cols*rows*2+i+j*rows,0);
        }
      }

      for (int i = 0; i<rows*cols; i++)
      {
          mcouleur.at<float>(i,0) = mcouleur.at<float>(i,0) - meanB;
          mcouleur.at<float>(i,1) = mcouleur.at<float>(i,1) - meanG;
          mcouleur.at<float>(i,2) = mcouleur.at<float>(i,2) - meanR;
      }


      Mat inter = Mat::zeros(rows*cols,3,CV_32F);
      inter = mcouleur * invCov_mat;
      //transpose inter
      Mat inter_transp;
      transpose(inter,inter_transp);


      //transpose mcouleur
      Mat mcouleur_transp;
      transpose(mcouleur,mcouleur_transp);
      Mat fusion;
      multiply(inter_transp,mcouleur_transp,fusion);

      Mat mahal_inter = Mat::zeros(1,rows*cols,CV_32F);
      for (int i=0; i<rows*cols; i++)
      {
        mahal_inter.at<float>(0,i)=fusion.at<float>(0,i)+fusion.at<float>(1,i)+fusion.at<float>(2,i);
      }

      // mahalanobis image
      Mat mahalanobis_mat = Mat::zeros(rows,cols,CV_32F);
      for (int j=0; j<cols; j++)
      {
        for (int i=0; i<rows; i++)
        {
          mahalanobis_mat.at<float>(i,j)=mahal_inter.at<float>(0,i+j*rows);
        }
      }

      duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
      cout << "Mahalanobis calculation time : " << duration << endl;

/*
      Mat canalB_modif = Mat::zeros(rows,cols,CV_32F);
      Mat canalG_modif = Mat::zeros(rows,cols,CV_32F);
      Mat canalR_modif = Mat::zeros(rows,cols,CV_32F);


      subtract(canalB,meanB,canalB_modif);
      subtract(canalG,meanG,canalG_modif);
      subtract(canalR,meanR,canalR_modif);
      canalR_modif.at<float>(0,0) = canalR.at<uchar>(0,0) - meanR;
*/

      start = clock();

      int seuil = 800;
      for (int i=0; i<rows; i++)
      {
        for (int j=0; j<cols; j++)
        {
          if(mahalanobis_mat.at<float>(i,j) <=seuil)
          {
            mahalanobis_mat.at<float>(i,j) = 255;
          }
          else{
            mahalanobis_mat.at<float>(i,j) = 0;
          }
        }
      }

      duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
      cout << "Thresholding and binarization : " << duration << endl;

/*
      blur(mahalanobis_mat, mahalanobis_mat, Size(40,40));
      for (int i=0; i<rows; i++)
      {
        for (int j=0; j<cols; j++)
        {
          if(mahalanobis_mat.at<float>(i,j) > 225)
          {
            mahalanobis_mat.at<float>(i,j) = 255;
          }
          else{
            mahalanobis_mat.at<float>(i,j) = 0;
          }
        }
      }
      int dilation_type = MORPH_ELLIPSE;
      int dilation_size = 15;
      Mat element = getStructuringElement( dilation_type, Size( 2*dilation_size + 1, 2*dilation_size+1), Point( dilation_size, dilation_size ) );
      dilate(mahalanobis_mat, mahalanobis_mat, element);
*/

      imshow("Binarisation Mahalanobis", mahalanobis_mat);
      waitKey(0);

      imwrite("mahalanobis.png",mahalanobis_mat);

  }
  else
          cerr << "Impossible d'ouvrir le fichier !" << endl;



}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname imsname2 imdname "<<endl;
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
