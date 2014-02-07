// Grayscale.cpp

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

#include "Grayscale.hpp"
#include "../Exception.hpp"
#include "../Conversion.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QHash>
#include <QImage>
#include <QDebug>

QImage Grayscale::Draw(const QImage &image, const QHash<QString, QString>&)
{
	if (image.format() == QImage::Format_RGB888) {
		cv::Mat mat = QImageToMat(image);
		cv::cvtColor(mat, mat, CV_BGR2GRAY);
		cv::cvtColor(mat, mat, CV_GRAY2BGR);
		return MatToQImage(mat);
	} else if (image.format() == QImage::Format_ARGB32) {
		cv::Mat mat = QImageToMat(image.convertToFormat(QImage::Format_RGB888));
		cv::cvtColor(mat, mat, CV_BGR2GRAY);
		cv::cvtColor(mat, mat, CV_GRAY2BGR);
		return MatToQImage(mat);
	}

	return image;
}

QString Grayscale::GetName() const
{
	return "Grayscale";
}
