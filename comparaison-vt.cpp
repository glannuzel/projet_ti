#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace cv;
using namespace std;


/*void
process(const char* ims, const char* vt)
{*/

void
comparaison_vt(float tableau[8][2], int test, char* ims, char* vt)
{

  Mat image;
  Mat image_vt;

  image = imread(static_cast<const char*>(ims), CV_LOAD_IMAGE_COLOR);
  image_vt = imread(static_cast<const char*>(vt), CV_LOAD_IMAGE_COLOR);


  if(!image.data||!image_vt.data)
    {
        cout <<  "Image not found" << std::endl ;
    }
  else
  {

    Mat image_gray;
    Mat image_gray_float;

    cvtColor(image, image_gray, CV_BGR2GRAY);
    image_gray.convertTo(image_gray_float, CV_32FC1);
    imshow(ims,image);

    Mat image_vt_gray;
    Mat image_vt_gray_float;
    cvtColor(image_vt, image_vt_gray, CV_BGR2GRAY);
    image_vt_gray.convertTo(image_vt_gray_float, CV_32FC1);
    imshow(vt,image_vt);

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

    tableau[0][test] = nb_pixels_tot;
    tableau[1][test] = nb_fp;
    tableau[2][test] = nb_fn;
    tableau[3][test] = nb_pixels_terrain_trouve;
    tableau[4][test] = nb_pixels_terrain_vt;
    tableau[5][test] = nb_correct;
    tableau[6][test] = rappel;
    tableau[7][test] = precision;

    cout<<"Données quantitatives :" <<endl;
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


/*void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims vt\n"<<std::endl;
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
}*/
