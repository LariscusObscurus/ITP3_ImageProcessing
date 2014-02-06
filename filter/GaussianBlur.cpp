// GaussianBlur.cpp

/* © 2013 David Wolf
 *
 * This file is part of ImageProcessing.
 *
 * ImageProcessing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ImageProcessing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ImageProcessing.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "GaussianBlur.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QHash>
#include <QImage>

QImage GaussianBlur::Draw(const QImage &image, const QHash<QString, QString>& args)
{
	double sigma = 0;
	int ksize = 3;
	Arguments(args, ksize, sigma);
	cv::Mat mat = QImageToMat(image);
	cv::GaussianBlur(mat.clone(), mat, cv::Size(ksize, ksize), sigma);
	return MatToQImage(mat);
}

void GaussianBlur::Arguments(const QHash<QString, QString> &args, int &ksize, double &sigma)
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
