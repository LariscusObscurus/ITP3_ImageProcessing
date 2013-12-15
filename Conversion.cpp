// Conversion.cpp

#include "Conversion.h"
#include "Exception.h"

QImage::Format ConvertCvFormat(int format)
{
	switch (format) {
	case CV_8UC4:
		return QImage::Format_ARGB32;
	case CV_8UC3:
		return QImage::Format_RGB888;
	case CV_8UC1:
		return QImage::Format_Mono;
	default:
		return QImage::Format_Invalid;
	}
}

QImage ConvertQ4(cv::Mat& bgr)
{
	cv::Mat argb = cv::Mat(bgr.rows, bgr.cols, CV_8UC4);
	int fromTo[] = { 0,3, 1,2, 2,1 };
	cv::mixChannels(&bgr, 1, &argb, 1, fromTo, 3);
	return QImage(argb.data, argb.cols, argb.rows, argb.step, QImage::Format_Mono).copy();
}

QImage ConvertQ3(cv::Mat& bgr)
{
	cv::Mat rgb = cv::Mat(bgr.rows, bgr.cols, CV_8UC3);
	int fromTo[] = { 0,2, 1,1, 2,0 };
	cv::mixChannels(&bgr, 1, &rgb, 1, fromTo, 3);
	return QImage(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_Mono).copy();
}

QImage MatToQimage(cv::Mat& mat)
{
	QImage::Format format = ConvertCvFormat(mat.type());

	if (format == QImage::Format_ARGB32) {
		return ConvertQ4(mat);
	} else if (format == QImage::Format_RGB32) {
		return ConvertQ3(mat);
	} else if (format == QImage::Format_Mono) {
		return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Mono).copy();
	} else {
		throw FormatException("can't convert this pixel format");
	}
}

int ConvertQformat(QImage::Format format)
{
	switch (format) {
	case QImage::Format_ARGB32:
		return CV_8UC4;
	case QImage::Format_RGB888:
		return CV_8UC3;
	case QImage::Format_Mono:
		return CV_8UC1;
	default:
		return 0;
	}
}

cv::Mat ConvertMat4(QImage& img)
{
	cv::Mat argb = cv::Mat(img.height(), img.width(), CV_8UC4, img.bits(), img.bytesPerLine());
	cv::Mat bgr(argb.rows, argb.cols, CV_8UC3);
	int fromTo[] = { 3,0, 2,1, 1,2 };
	cv::mixChannels(&argb, 1, &bgr, 1, fromTo, 3);
	return bgr.clone();
}

cv::Mat ConvertMat3(QImage& img)
{
	cv::Mat rgb = cv::Mat(img.height(), img.width(), CV_8UC3, img.bits(), img.bytesPerLine());
	cv::Mat bgr(rgb.rows, rgb.cols, CV_8UC3);
	int fromTo[] = { 2,0, 1,1, 0,2 };
	cv::mixChannels(&rgb, 1, &bgr, 1, fromTo, 3);
	return bgr.clone();
}

cv::Mat QimageToMat(QImage& img)
{
	int format = ConvertQformat(img.format());

	if (format == CV_8UC4) {
		return ConvertMat4(img);
	} else if (format == CV_8UC3) {
		return ConvertMat3(img);
	} else if (format == CV_8UC1) {
		return cv::Mat(img.height(), img.width(), CV_8UC1, img.bits(), img.bytesPerLine()).clone();
	} else {
		throw FormatException("can't convert this pixel format");
	}
}
