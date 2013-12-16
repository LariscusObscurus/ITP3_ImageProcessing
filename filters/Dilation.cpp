// Dilation.cpp

#include "Dilation.h"
#include "Exception.h"
#include "Conversion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void Dilation::Initialize() { }

void Dilation::Draw(QImage &image, const QMap<QString, QString> &args)
{
	int shape = cv::MORPH_RECT;
	int ksize = 2;
	Arguments(args, shape, ksize);
	cv::Mat mat = QimageToMat(image);
	cv::Mat kernel = cv::getStructuringElement(shape, cv::Size(ksize, ksize));
	cv::dilate(mat.clone(), mat, kernel);
	image = MatToQimage(mat);
}

void Dilation::Finalize() { }

void Dilation::Arguments(const QMap<QString, QString> &args, int& shape, int& ksize)
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
			throw FormatException("couldn't convert \"KernelSize\" argument for dilation effect");
		} else if (ksize < 0) {
			throw ArgumentException("\"KernelSize\" argument for dilation effect must be positive");
		}
		ksize = 2 * ksize + 1;
	}
}
