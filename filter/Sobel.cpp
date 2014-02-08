// Sobel.cpp

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

#include "Sobel.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QHash>
#include <QImage>
#include <QDebug>

QImage Sobel::Draw(const QImage &image, const QHash<QString, QString>& args)
{
	int ksize = 3;

	cv::Mat src, grad, result;
	cv::Mat gradX, gradY;
	cv::Mat absGradX, absGradY;

	Arguments(args, ksize);

	src = QImageToMat(image);
	cv::cvtColor(src, src, CV_BGR2GRAY);
	cv::Sobel(src, gradX, -1, 1, 0, ksize);
	cv::convertScaleAbs(gradX, absGradX);
	cv::Sobel(src, gradY, -1, 0, 1, ksize);
	cv::convertScaleAbs(gradY, absGradY);
	cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, grad);
	grad.convertTo(result, CV_8U);
	return MatToQImage(result);
}

void Sobel::Arguments(const QHash<QString, QString> &args, int& ksize)
{
	bool ok = false;
	QHash<QString,QString>::const_iterator it;

	if ((it = args.find("Value")) != args.end()) {
		ksize = it.value().toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"Value\" argument for sobel");
		} else if (ksize < 0) {
			throw ArgumentException("\"Value\" argument for sobel must be positive");
		}
		ksize = (2 * (ksize-1) + 1);
		ksize = ksize > 31 ? 31 : ksize;
	}
}

QString Sobel::GetName() const
{
	return "Sobel";
}
