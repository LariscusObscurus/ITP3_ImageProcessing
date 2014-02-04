// MedianBlur.cpp

#include "MedianBlur.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMap>
#include <QImage>

void MedianBlur::Draw(QImage &image, const QMap<QString, QString> &args)
{
	int ksize = 7;
	auto it = args.find("KernelSize");

	if (it != args.end() && it.key() == "KernelSize") {
		bool ok = false;
		ksize = it.value().toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"KernelSize\" argument for median blur");
		} else if (ksize < 1) {
			throw ArgumentException("\"KernelSize\" argument for median blur must be odd and greater than 1");
		}
		ksize = 2 * ksize + 1;
	}

	cv::Mat mat = QimageToMat(image);
	cv::medianBlur(mat.clone(), mat, ksize);
	image = MatToQimage(mat);
}

QString MedianBlur::GetName() const
{
	return "Median Blur";
}
