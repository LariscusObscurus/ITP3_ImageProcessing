// ConvexHull.cpp

#include "ConvexHull.h"
#include "Conversion.h"
#include "Exception.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>




void ConvexHull::Initialize() { }

void ConvexHull::Draw(QImage &image, const QMap<QString, QString> &args)
{
   int thresh = 100;
   int max_thresh = 255;
   RNG rng(12345);
        
   cv::Mat mat = QimageToMat(image);
  
   /*
    Convert to Grey
    */
   
   vector<vector<Point> > contours;
   vector<Vec4i> hierarchy;

   /// Detect edges using Threshold
   threshold( src_gray, mat, thresh, 255, THRESH_BINARY );

   /// Find contours
   findContours( mat, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

   /// Find the convex hull object for each contour
   vector<vector<Point> >hull( contours.size() );
   for( int i = 0; i < contours.size(); i++ )
      {  convexHull( Mat(contours[i]), hull[i], false ); }

   /// Draw contours + hull results
   Mat drawing = Mat::zeros( mat.size(), CV_8UC3 );
   for( int i = 0; i< contours.size(); i++ )
      {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
      }
        
	image = MatToQimage(mat);
        


}

void ConvexHull::Finalize() { }
