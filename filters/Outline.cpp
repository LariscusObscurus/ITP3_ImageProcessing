// Outline.cpp

#include "Outline.h"
#include "Exception.h"
#include "Conversion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void Outline::Initialize() { }

void Outline::Draw(QImage &image, const QMap<QString, QString> &args)
{
	const int op = cv::MORPH_GRADIENT;
	int shape = cv::MORPH_RECT;
	int ksize = 2;
	Arguments(args, shape, ksize);
	cv::Mat mat = QimageToMat(image);
	cv::Mat kernel = cv::getStructuringElement(shape, cv::Size(ksize, ksize));
	cv::morphologyEx(mat.clone(), mat, op, kernel);
	image = MatToQimage(mat);
}

void Outline::Finalize() { }

void Outline::Arguments(const QMap<QString, QString> &args, int &shape, int &ksize)
{
	auto it = args.find("Shape");

	if (it != args.end() && it.key() == "Shape") {
		if (it.value() == "Rect") {
			shape = cv::MORPH_RECT;
		} else if (it.value() == "Cross") {
			shape = cv::MORPH_CROSS;
		} else if (it.value() == "Ellipse") {
			shape = cv::MORPH_ELLIPSE;
		} else {
			throw ArgumentException("\"Shape\" doesn't name an existing type");
		}
	}
	it = args.find("MorphSize");

	if (it != args.end() && it.key() == "MorphSize") {
		bool ok = false;
		ksize = it.value().toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"MorphSize\" argument for erosion effect");
		} else if (ksize < 0) {
			throw ArgumentException("\"MorphSize\" argument for erosion effect must be positive");
		}
		ksize = 2 * ksize + 1;
	}
}
