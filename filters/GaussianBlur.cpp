// GaussianBlur.cpp

#include "GaussianBlur.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMap>
#include <QImage>

void GaussianBlur::Draw(QImage &image, const QMap<QString, QString> &args)
{
	double sigma = 0;
	int ksize = 3;
	Arguments(args, ksize, sigma);
	cv::Mat mat = QimageToMat(image);
	cv::GaussianBlur(mat.clone(), mat, cv::Size(ksize, ksize), sigma);
	image = MatToQimage(mat);
}

void GaussianBlur::Arguments(const QMap<QString, QString> &args, int &ksize, double &sigma)
{
	// Name der Argumente steht noch nicht fest
	bool ok = false;
	auto ks = args.find("KernelSize");
	auto sg = args.find("Sigma");

	if (ks != args.end() && ks.key() == "KernelSize") {
		ksize = ks.value().toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"KernelSize\" argument for gaussian blur");
		} else if (ksize < 0) {
			throw ArgumentException("\"KernelSize\" argument for gaussian blur must be positive");
		}
		ksize = 2 * ksize + 1;
	}
	if (sg != args.end() && sg.key() == "Sigma") {
		sigma = sg.value().toDouble(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"Sigma\" argument for gaussian blur");
		} else if (sigma < 0) {
			throw ArgumentException("\"Sigma\" argument for gaussian blur must be positive");
		}
	}
}

QString GaussianBlur::GetName() const
{
	return "Gaussian Blur";
}
