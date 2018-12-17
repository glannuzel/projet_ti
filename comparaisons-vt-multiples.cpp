#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
comparaison_vt(float tableau[], Mat image, Mat image_vt)
{

    Mat image_gray;
    Mat image_gray_float;

    cvtColor(image, image_gray, CV_BGR2GRAY);
    image_gray.convertTo(image_gray_float, CV_32FC1);
    imshow("image traite",image);

    Mat image_vt_gray;
    Mat image_vt_gray_float;
    cvtColor(image_vt, image_vt_gray, CV_BGR2GRAY);
    image_vt_gray.convertTo(image_vt_gray_float, CV_32FC1);
    imshow("vt",image_vt);

    int nb_pixels_tot(0);
    nb_pixels_tot = image.size().height*image.size().width;

    float rappel(0);
    float precision(0);
    float nb_correct(0);
    float nb_pixels_terrain_trouve(0);
    float nb_pixels_terrain_vt(0);
    float nb_fp(0);
    float nb_fn(0);


    Mat image_fp;
    Mat image_fp_float;

    image_fp = image_gray-image_vt_gray;
    image_fp.convertTo(image_fp_float, CV_32FC1);
    imshow("Faux positifs", image_fp);

    Mat image_fn;
    Mat image_fn_float;

    image_fn = image_vt_gray-image_gray;
    image_fn.convertTo(image_fn_float, CV_32FC1);

    imshow("Faux négatifs", image_fn);

    for(int i=0;i<image_gray.size().height;i++)
    {
      for(int j=0;j<image_gray.size().width;j++)
      {

        if(image_vt_gray_float.at<float>(i,j) == 255)
        {
          nb_pixels_terrain_vt ++;
        }

        if(image_gray_float.at<float>(i,j) == 255)
        {
          nb_pixels_terrain_trouve ++;
        }

        if(image_fp_float.at<float>(i,j) == 255)
        {
          nb_fp ++;
        }

        if(image_fn_float.at<float>(i,j) == 255)
        {
          nb_fn ++;
        }
      }
    }

    nb_correct = nb_pixels_terrain_trouve - nb_fp;

    rappel = nb_correct / nb_pixels_terrain_vt;

    precision = nb_correct / nb_pixels_terrain_trouve;

    tableau[0] += nb_pixels_tot;
    tableau[1] += nb_fp;
    tableau[2] += nb_fn;
    tableau[3] += nb_pixels_terrain_trouve;
    tableau[4] += nb_pixels_terrain_vt;
    tableau[5] += nb_correct;
    tableau[6] += rappel;
    tableau[7] += precision;
    tableau[8] ++;

    cout<<"Données quantitatives :" <<endl;
    cout<<"nb_pixels_tot : " << tableau[0]<<endl;
    cout<<"nb_fp : " << tableau[1]<<endl;
    cout<<"nb_fn : " << tableau[2]<<endl;
    cout<<"nb_pixels_terrain_trouve : " << tableau[3]<<endl;
    cout<<"nb_pixels_terrain_vt : " << tableau[4]<<endl;
    cout<<"nb_correct : " << tableau[5]<<endl;
    cout<<"rappel : " << tableau[6]<<endl;
    cout<<"precision : " << tableau[7]<<endl;

}

void
process(const char* dest)
{
  (void) dest;
  float tableau[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  Mat image;
  Mat image_vt;

  image = imread("./erosion.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log1-vt/001-rgb-vt.png", CV_LOAD_IMAGE_COLOR);


  if(!image.data||!image_vt.data)
    {
        cout <<  "Image not found" << std::endl ;
    }
  else
  {
    comparaison_vt(tableau, image , image_vt);
    comparaison_vt(tableau, image , image_vt);

  }

  float nb_pixels_tot_moy(0);
  float nb_fp_moy(0);
  float nb_fn_moy(0);
  float nb_pixels_terrain_trouve_moy(0);
  float nb_pixels_terrain_vt_moy(0);
  float nb_correct_moy(0);
  float rappel_moy(0);
  float precision_moy(0);

  nb_pixels_tot_moy = tableau[0] / tableau[8];
  nb_fp_moy  = tableau[1] / tableau[8];
  nb_fn_moy  = tableau[2] / tableau[8];
  nb_pixels_terrain_trouve_moy  = tableau[3] / tableau[8];
  nb_pixels_terrain_vt_moy  = tableau[4] / tableau[8];
  nb_correct_moy  = tableau[5] / tableau[8];
  rappel_moy  = tableau[6] / tableau[8];
  precision_moy  = tableau[7] / tableau[8];

  cout<<"Données quantitatives moyennes :" <<endl;
  cout<<"nb_pixels_tot : " << nb_pixels_tot_moy<<endl;
  cout<<"nb_fp : " << nb_fp_moy<<endl;
  cout<<"nb_fn : " << nb_fn_moy<<endl;
  cout<<"nb_pixels_terrain_trouve : " << nb_pixels_terrain_trouve_moy<<endl;
  cout<<"nb_pixels_terrain_vt : " << nb_pixels_terrain_vt_moy<<endl;
  cout<<"nb_correct : " << nb_correct_moy<<endl;
  cout<<"rappel : " << rappel_moy<<endl;
  cout<<"precision : " << precision_moy<<endl;
  cout<<"nb test : " << tableau[8]<<endl;

}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims vt\n"<<std::endl;
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
