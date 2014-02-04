// Blur.cpp

#include "Blur.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMap>
#include <QImage>

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

QString Blur::GetName() const
{
	return "Blur";
}
