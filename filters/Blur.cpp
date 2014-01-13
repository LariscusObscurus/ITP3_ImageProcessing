// Blur.cpp

#include "Blur.h"
#include "../Conversion.h"
#include "../Exception.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void Blur::Initialize() { }

void Blur::Draw(QImage &image, const QMap<QString, QString> &args)
{
	int ksize = 3;
	cv::Mat mat = QimageToMat(image);
	// Name des Argumentes steht noch nicht fest
	auto it = args.find("KernelSize");

	if (it != args.end() && it.key() == "KernelSize") {
		bool ok = false;
		ksize = it.value().toInt(&ok);

		if (!ok) {
			throw FormatException("Couldn't convert \"KernelSize\" argument for blur");
		}
		ksize = 2 * ksize + 1;
	}
	cv::blur(mat.clone(), mat, cv::Size(ksize, ksize));
	image = MatToQimage(mat);
}

void Blur::Finalize() { }
