// Canny.cpp

#include "Canny.h"
#include "Conversion.h"
#include "Exception.h"
#include "Blur.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void Canny::Initialize() { }

void Canny::Draw(QImage &image, const QMap<QString, QString> &args)
{
	Blur f;
	int ksize = 3;
	int threshold = 100;
	f.Draw(image, args);
	cv::Mat mat = QimageToMat(image);
	Arguments(args, ksize, threshold);
	cv::Canny(mat.clone(), mat, threshold, threshold * 3, ksize);
	image = MatToQimage(mat);
}

void Canny::Finalize() { }

void Canny::Arguments(const QMap<QString, QString>& args, int& ksize, int& threshold)
{
	bool ok = false;
	auto it = args.find("KernelSize");

	if (it != args.end() && it.key() == "KernelSize") {
		ksize = args["KernelSize"].toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"KernelSize\" argument for gaussian blur");
		} else if (ksize < 0) {
			throw ArgumentException("\"KernelSize\" argument for gaussian blur must be positive");
		}
		ksize = 2 * ksize + 1;
	}
	it = args.find("Threshold");

	if (it != args.end() && it.key() == "Threshold") {
		threshold = args["Threshold"].toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"Threshold\" argument for gaussian blur");
		} else if (ksize < 0) {
			throw ArgumentException("\"Threshold\" argument for gaussian blur must be positive");
		}
	}
}
