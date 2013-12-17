// Remapping.cpp

#include "Remapping.h"
#include "Exception.h"
#include "Conversion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

 Mat src, dst;
 Mat map_x, map_y;
 int ind = 0;

void Remapping::Initialize() { }

void Remapping::Draw(QImage &image, const QMap<QString, QString> &args)
{
	int shape = cv::MORPH_RECT;
	int ksize = 1;
	//Arguments(args);
	cv::Mat mat = QimageToMat(image);
        
        mat.create( mat.size(), mat.type() );
        map_x.create( mat.size(), CV_32FC1 );
        map_y.create( mat.size(), CV_32FC1 );
        
        remap( mat, dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

	image = MatToQimage(mat);
}

void Remapping::Finalize() { }

void Remapping::Arguments(const QMap<QString, QString> &args)
{
	/*auto it = args.find(0);

         switch( it )
         {
           case 0:
             if( i > src.cols*0.25 && i < src.cols*0.75 && j > src.rows*0.25 && j < src.rows*0.75 )
               {
                 map_x.at<float>(j,i) = 2*( i - src.cols*0.25 ) + 0.5 ;
                 map_y.at<float>(j,i) = 2*( j - src.rows*0.25 ) + 0.5 ;
                }
             else
               { map_x.at<float>(j,i) = 0 ;
                 map_y.at<float>(j,i) = 0 ;
               }
                 break;
           case 1:
                 map_x.at<float>(j,i) = i ;
                 map_y.at<float>(j,i) = src.rows - j ;
                 break;
           case 2:
                 map_x.at<float>(j,i) = src.cols - i ;
                 map_y.at<float>(j,i) = j ;
                 break;
           case 3:
                 map_x.at<float>(j,i) = src.cols - i ;
                 map_y.at<float>(j,i) = src.rows - j ;
                 break;
         } // end of switch*/
}
