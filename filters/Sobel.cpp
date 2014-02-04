// Sobel.cpp

#include "Sobel.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include "Grayscale.hpp"
#include "GaussianBlur.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMap>
#include <QImage>

void Sobel::Draw(QImage &image, const QMap<QString, QString> &args)
{
	int ddepth = CV_16U;
	int ksize = 3;
	cv::Mat srcGray, grad, result;
	cv::Mat gradX, gradY;
	cv::Mat absGradX, absGradY;
	SetupOperation(image, args, 1);
	srcGray = QimageToMat(image);
	cv::Sobel(srcGray, gradX, ddepth, 1, 0, ksize);
	cv::convertScaleAbs( gradX, absGradX );
	cv::Sobel(srcGray, gradY, ddepth, 0, 1, ksize);
	cv::convertScaleAbs(gradY, absGradY);
	cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, grad);
	grad.convertTo(result, CV_8U);
	image = MatToQimage(result);
}

void Sobel::SetupOperation(QImage& image, QMap<QString, QString> args, int ksize)
{
	bool ok = false;
	GaussianBlur gauss;
	//Grayscale gray;

	if (args.find("KernelSize") == args.end()) {
		args["KernelSize"] = QString().setNum(ksize);
	} else {
		ksize = args["KernelSize"].toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"KernelSize\" argument for gaussian blur");
		} else if (ksize < 0) {
			throw ArgumentException("\"KernelSize\" argument for gaussian blur must be positive");
		}
	}
	gauss.Draw(image, args);
	//gray.Draw(image, args);
}

QString Sobel::GetName() const
{
	return "Sobel";
}
