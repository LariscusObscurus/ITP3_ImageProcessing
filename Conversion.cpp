// Conversion.cpp

#include "Conversion.h"
#include <opencv2/core/core.hpp>
#include <QImage>

QImage MatToQimage(cv::Mat& mat, QImage::Format format)
{
	return QImage(mat.data, mat.cols, mat.rows, mat.step, format).copy();
}

cv::Mat QimageToMat(QImage& img, int format)
{
	return cv::Mat(img.height(), img.width(), format, img.bits(), img.bytesPerLine()).clone();
}

