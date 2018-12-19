#include <iostream>
#include <cstdlib>
#include <cmath>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
comparaison_vt(float tableau[], Mat image, Mat image_vt, int parImage)
{

    Mat image_gray;
    Mat image_gray_float;

    cvtColor(image, image_gray, CV_BGR2GRAY);
    image_gray.convertTo(image_gray_float, CV_32FC1);

    Mat image_vt_gray;
    Mat image_vt_gray_float;
    cvtColor(image_vt, image_vt_gray, CV_BGR2GRAY);
    image_vt_gray.convertTo(image_vt_gray_float, CV_32FC1);

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

    Mat image_fn;
    Mat image_fn_float;

    image_fn = image_vt_gray-image_gray;
    image_fn.convertTo(image_fn_float, CV_32FC1);


    for(int i=0;i<image_gray.size().height;i++)
    {
      for(int j=0;j<image_gray.size().width;j++)
      {

        if(image_vt_gray_float.at<float>(i,j) > 125)
        {
          nb_pixels_terrain_vt ++;
        }

        if(image_gray_float.at<float>(i,j)  > 125)
        {
          nb_pixels_terrain_trouve ++;
        }
        if(image_gray_float.at<float>(i,j)  > 125 && image_vt_gray_float.at<float>(i,j)  > 125)
        {
          nb_correct ++;
        }

        if(image_gray_float.at<float>(i,j)  > 125 && image_vt_gray_float.at<float>(i,j) <= 125)
        {
          nb_fp ++;
        }

        if(image_gray_float.at<float>(i,j) <= 125 && image_vt_gray_float.at<float>(i,j)  > 125)
        {
          nb_fn ++;
        }
      }
    }

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

    if (parImage)
    {
    cout<<"Données quantitatives de l'image " << tableau[8]<<" :" <<endl;
    cout<<"nb_pixels_tot : " << nb_pixels_tot<<endl;
    cout<<"nb_fp : " << nb_fp<<endl;
    cout<<"nb_fn : " << nb_fn<<endl;
    cout<<"nb_pixels_terrain_trouve : " << nb_pixels_terrain_trouve<<endl;
    cout<<"nb_pixels_terrain_vt : " << nb_pixels_terrain_vt<<endl;
    cout<<"nb_correct : " << nb_correct<<endl;
    cout<<"rappel : " << rappel<<endl;
    cout<<"precision : " << precision<<endl;
  }

}

void
process(char* choix)
{

  int parImage = atoi(choix);
  float tableau[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  Mat image;
  Mat image_vt;

  // Pour chaque image
  image = imread("./images_test_algo1/algo1_filled_region_1_001.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log1-vt/001-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_1_081.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log1-vt/081-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_1_212.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log1-vt/212-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_1_231.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log1-vt/231-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_1_271.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log1-vt/271-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_1_358.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log1-vt/358-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);

  image = imread("./images_test_algo1/algo1_filled_region_2_011.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log2-vt/011-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_2_089.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log2-vt/089-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_2_157.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log2-vt/157-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_2_185.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log2-vt/185-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_2_200.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log2-vt/200-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_2_231.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log2-vt/231-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);

  image = imread("./images_test_algo1/algo1_filled_region_3_001.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log3-vt/001-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_3_043.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log3-vt/043-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_3_078.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log3-vt/078-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_3_125.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log3-vt/125-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_3_216.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log3-vt/216-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_3_249.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log3-vt/249-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);

  image = imread("./images_test_algo1/algo1_filled_region_4_10.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log4-vt/10-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_4_20.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log4-vt/20-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_4_30.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log4-vt/30-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_4_40.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log4-vt/40-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_4_50.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log4-vt/50-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);
  image = imread("./images_test_algo1/algo1_filled_region_4_60.png", CV_LOAD_IMAGE_COLOR);
  image_vt = imread( "./images_vt/log4-vt/60-rgb-vt.png", CV_LOAD_IMAGE_COLOR);
  comparaison_vt(tableau, image , image_vt, parImage);

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
  std::cerr<<"Usage: "<<s<<" parImage\n"<<std::endl;
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
