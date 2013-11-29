// Conversion.h

#ifndef CONVERSION_H
#define CONVERSION_H

#include <QImage>
#include <opencv2/core/core.hpp>

QImage MatToQimage(cv::Mat&, int format = CV_8UC3);
cv::Mat QimageToMat(QImage&, QImage::Format format = QImage::Format_RGB888);

#endif // CONVERSION_H

