// MedianBlur.cpp

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
