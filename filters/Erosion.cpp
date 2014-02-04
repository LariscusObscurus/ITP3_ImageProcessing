// Erosion.cpp

#include "Erosion.hpp"
#include "../Exception.hpp"
#include "../Conversion.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMap>
#include <QImage>

void Erosion::Draw(QImage &image, const QMap<QString, QString> &args)
{
	int shape = cv::MORPH_RECT;
	int ksize = 2;
	Arguments(args, shape, ksize);
	cv::Mat mat = QimageToMat(image);
	cv::Mat kernel = cv::getStructuringElement(shape, cv::Size(ksize, ksize));
	cv::erode(mat.clone(), mat, kernel);
	image = MatToQimage(mat);
}

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

QString Erosion::GetName() const
{
	return "Erosion";
}
