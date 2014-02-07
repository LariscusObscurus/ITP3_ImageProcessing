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
	int ksize = 3;
	int threshold = 100;
	cv::Mat mat = QImageToMat(image);

	Arguments(args, ksize, threshold);

	cv::blur(mat, mat, cv::Size(ksize, ksize));
	cv::Canny(mat, mat, threshold, threshold * 3);
	return MatToQImage(mat);
}

void Canny::Arguments(const QHash<QString, QString>& args, int& ksize, int& threshold)
{
	bool ok = false;
	QHash<QString, QString>::const_iterator it;

	if ((it = args.find("Value")) != args.end()) {
		threshold = it.value().toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"Value\" argument for canny");
		} else if (ksize < 0) {
			throw ArgumentException("\"Value\" argument for canny must be positive");
		}
	}

	if ((it = args.find("KernelSize")) != args.end()) {
		ksize = it.value().toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"KernelSize\" argument for canny");
		} else if (ksize < 0) {
			throw ArgumentException("\"KernelSize\" argument for canny must be positive");
		}
		ksize = 2 * ksize + 1;
	}

	if ((it = args.find("Threshold")) != args.end()) {
		threshold = it.value().toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"Threshold\" argument for canny");
		} else if (ksize < 0) {
			throw ArgumentException("\"Threshold\" argument for canny must be positive");
		}
	}
}

QString Canny::GetName() const
{
	return "Canny";
}
