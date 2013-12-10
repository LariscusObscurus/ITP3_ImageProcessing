// Conversion.cpp

#include "Conversion.h"

int ConvertQformat(QImage::Format format)
{
	switch (format) {
	case QImage::Format_RGB888:
		return CV_8UC3;
	case QImage::Format_ARGB32:
		return CV_8UC4;
	case QImage::Format_Mono:
		return CV_8UC1;
	default:
		return CV_8UC3;
	}
}

QImage::Format ConvertCvFormat(int format)
{
	switch (format) {
	case CV_8UC3:
		return QImage::Format_RGB888;
	case CV_8UC4:
		return QImage::Format_ARGB32;
	case CV_8UC1:
		return QImage::Format_Mono;
	default:
		return QImage::Format_RGB888;
	}
}

QImage MatToQimage(cv::Mat& mat)
{
	return QImage(mat.data, mat.cols, mat.rows, mat.step, ConvertCvFormat(mat.type())).copy();
}

cv::Mat QimageToMat(QImage& img)
{
	return cv::Mat(img.height(), img.width(), ConvertQformat(img.format()), img.bits(), img.bytesPerLine()).clone();
}
