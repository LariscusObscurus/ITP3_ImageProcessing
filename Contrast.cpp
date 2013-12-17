// Contrast.cpp

#include "Contrast.h"
#include "Conversion.h"
#include "Exception.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>




void Contrast::Initialize() { }

void Contrast::Draw(QImage &image, const QMap<QString, QString> &args)
{

        
   cv::Mat mat = QimageToMat(image);
  
   Mat imgH;
   mat.convertTo(imgH, -1, 2, 0); //increase the contrast (double)

    //Mat imgL;
    //img.convertTo(imgL, -1, 0.5, 0); //decrease the contrast (halve)
        
   image = MatToQimage(mat);
        


}

void Contrast::Finalize() { }
