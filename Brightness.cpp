// Brightness.cpp

#include "Brightness.h"
#include "Conversion.h"
#include "Exception.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>




void Brightness::Initialize() { }

void Brightness::Draw(QImage &image, const QMap<QString, QString> &args)
{

        
   cv::Mat mat = QimageToMat(image);
  
   mat = Scalar(75, 75, 75); //increase the brightness by 75 units
     //img.convertTo(imgH, -1, 1, 75);

  // Mat imgL = img + Scalar(-75, -75, -75); //decrease the brightness by 75 units
  //img.convertTo(imgL, -1, 1, -75);
        
   image = MatToQimage(mat);
        


}

void Brightness::Finalize() { }
