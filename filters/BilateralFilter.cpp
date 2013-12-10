// BilateralFilter.cpp

#include "BilateralFilter.h"
#include "Conversion.h"
#include "Exception.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void BilateralFilter::Initialize() { }

void BilateralFilter::Draw(QImage &image, const QMap<QString, QString> &args)
{
	int d = 5;
	double sigmaColor = 75;
	double sigmaSpace = 75;
	Arguments(args, d, sigmaColor, sigmaSpace);
	cv::Mat mat = QimageToMat(image);
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
