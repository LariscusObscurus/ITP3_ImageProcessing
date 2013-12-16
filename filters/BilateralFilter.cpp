// BilateralFilter.cpp

#include "BilateralFilter.h"
#include "Conversion.h"
#include "Exception.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void BilateralFilter::Initialize() { }

void BilateralFilter::Draw(QImage &image, const QMap<QString, QString> &args)
{
	cv::Mat mat;
	int d = 9;
	double sigmaColor = 150;
	double sigmaSpace = 150;

	// convert image if necessary
	if (image.format() == QImage::Format_RGB32 || image.format() == QImage::Format_ARGB32) {
		mat = QimageRgb32ToMat24(image);
	} else if (image.format() == QImage::Format_RGB888 || image.format() == QImage::Format_Indexed8) {
		mat = QimageToMat(image);
	} else {
		throw ArgumentException("for bilateral filter only 1-channel or 3-channel images are valid");
	}

	Arguments(args, d, sigmaColor, sigmaSpace);
	cv::bilateralFilter(mat.clone(), mat, d, sigmaColor, sigmaSpace);
	image = MatToQimage(mat);
}

void BilateralFilter::Finalize() { }

void BilateralFilter::Arguments(const QMap<QString, QString> &args, int &d, double &sigmaColor, double &sigmaSpace)
{
	bool ok = false;
	auto it = args.find("Diameter");

	if (it != args.end() && it.key() == "Diameter") {
		d = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Diameter\" argument for bilateral filter");
		}
	}
	it = args.find("SigmaColor");

	if (it != args.end() && it.key() == "SigmaColor") {
		sigmaColor = it.value().toDouble(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"SigmaColor\" argument for bilateral filter");
		}
	}
	it = args.find("SigmaSpace");

	if (it != args.end() && it.key() == "SigmaSpace") {
		sigmaSpace = it.value().toDouble(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"SigmaSpace\" argument for bilateral filter");
		}
	}
}

cv::Mat BilateralFilter::QimageRgb32ToMat24(QImage &img)
{
	return QimageToMat(img.convertToFormat(QImage::Format_RGB888));
}
