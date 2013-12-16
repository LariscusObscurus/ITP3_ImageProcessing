// Erosion.cpp

#include "Erosion.h"
#include "Exception.h"
#include "Conversion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void Erosion::Initialize() { }

void Erosion::Draw(QImage &image, const QMap<QString, QString> &args)
{
	int shape = cv::MORPH_RECT;
	int ksize = 5;
	Arguments(args, shape, ksize);
	cv::Mat mat = QimageToMat(image);
	cv::Mat kernel = cv::getStructuringElement(shape, cv::Size(ksize, ksize));
	cv::erode(mat.clone(), mat, kernel);
	image = MatToQimage(mat);
}

void Erosion::Finalize() { }

void Erosion::Arguments(const QMap<QString, QString> &args, int& shape, int& ksize)
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
	it = args.find("KernelSize");

	if (it != args.end() && it.key() == "KernelSize") {
		bool ok = false;
		ksize = it.value().toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"KernelSize\" argument for erosion effect");
		} else if (ksize < 0) {
			throw ArgumentException("\"KernelSize\" argument for erosion effect must be positive");
		}
		ksize = 2 * ksize + 1;
	}
}
