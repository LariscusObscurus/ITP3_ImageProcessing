// Contour.cpp

#include "Contour.h"
#include "Conversion.h"
#include "Exception.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>




void Contour::Initialize() { }

void Contour::Draw(QImage &image, const QMap<QString, QString> &args)
{
        int thresh = 100;
        int max_thresh = 255;
        RNG rng(12345);

	cv::Mat mat = QimageToMat(image);
	// Name des Argumentes steht noch nicht fest
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        /// Detect edges using canny
        Canny( src_gray, mat, thresh, thresh*2, 3 );
        /// Find contours
        findContours( mat, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

        /// Draw contours
        Mat drawing = Mat::zeros( mat.size(), CV_8UC3 );
        for( int i = 0; i< contours.size(); i++ )
           {
             Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
             drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
           }
        
	image = MatToQimage(mat);
        


}

void Contour::Finalize() { }
