// EdgeDetection.cpp

#include "EdgeDetection.h"
#include "Conversion.h"
#include "Exception.h"
//#include "GaussianBlur.h"
#include "Grayscale.h"
#include "Blur.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void EdgeDetection::Initialize() { }

void EdgeDetection::Draw(QImage &image, const QMap<QString, QString> &args)
{
	int ksize = 3;
	int ddepth = CV_16U;
	cv::Mat srcGray, grad, result;
	cv::Mat gradX, gradY;
	cv::Mat absGradX, absGradY;
	SetupOperation(image, args);
	srcGray = QimageToMat(image);
	//cv::Scharr(srcGray, gradX, ddepth, 1, 0);
	cv::Sobel(srcGray, gradX, ddepth, 1, 0, ksize);
	cv::convertScaleAbs( gradX, absGradX );
	//cv::Scharr(srcGray, gradY, ddepth, 0, 1);
	cv::Sobel(srcGray, gradY, ddepth, 0, 1, ksize);
	cv::convertScaleAbs(gradY, absGradY);
	cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, grad);
	grad.convertTo(result, CV_8U);
	image = MatToQimage(result);
	/*
	cv::Mat mat = QimageToMat(image);
	SetupOperation(image, args);
	cv::Canny(mat.clone(), mat, 45, 90);
	image = MatToQimage(mat);
	*/
}

void EdgeDetection::Finalize() { }

void EdgeDetection::SetupOperation(QImage& image, QMap<QString, QString> args)
{
	//GaussianBlur gauss;
	Blur blur;
	Grayscale gray;

	if (args.find("KernelSize") == args.end()) {
		args["KernelSize"] = QString().setNum(0);
	}

	//gauss.Draw(image, args);
	blur.Draw(image, args);
	gray.Draw(image, args);
}
