// Canny.cpp

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

#include "Canny.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include "Blur.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QHash>
#include <QImage>

QImage Canny::Draw(const QImage &image, const QHash<QString, QString>& args)
{
	Blur f;
	int ksize = 3;
	int threshold = 100;
	f.Draw(image, args);
	cv::Mat mat = QImageToMat(image);
	Arguments(args, ksize, threshold);
	cv::Canny(mat.clone(), mat, threshold, threshold * 3, ksize);
	return MatToQImage(mat);
}

void Canny::Arguments(const QHash<QString, QString>& args, int& ksize, int& threshold)
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

QString Canny::GetName() const
{
	return "Canny";
}
