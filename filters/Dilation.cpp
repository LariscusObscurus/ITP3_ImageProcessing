// Dilation.cpp

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

#include "Dilation.hpp"
#include "../Exception.hpp"
#include "../Conversion.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QHash>
#include <QImage>

QImage Dilation::Draw(const QImage &image, const QHash<QString, QString>& args)
{
	int shape = cv::MORPH_RECT;
	int ksize = 2;
	Arguments(args, shape, ksize);
	cv::Mat mat = QImageToMat(image);
	cv::Mat kernel = cv::getStructuringElement(shape, cv::Size(ksize, ksize));
	cv::dilate(mat.clone(), mat, kernel);
	return MatToQImage(mat);
}

void Dilation::Arguments(const QHash<QString, QString> &args, int& shape, int& ksize)
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
			throw FormatException("couldn't convert \"KernelSize\" argument for dilation effect");
		} else if (ksize < 0) {
			throw ArgumentException("\"KernelSize\" argument for dilation effect must be positive");
		}
		ksize = 2 * ksize + 1;
	}
}

QString Dilation::GetName() const
{
	return "Dilation";
}
