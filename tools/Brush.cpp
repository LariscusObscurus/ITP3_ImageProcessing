// FloodFill.cpp

/* © 2014 David Wolf
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

#include "Brush.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QColor>
#include <QPoint>

QImage Brush::Draw(const QImage &img, const QHash<QString, QString>& args)
{
	/*
	cv::Mat mat = QImageToMat(img);
	cv::Point seedPoint;
	cv::Scalar color(c.blue(), c.green(), c.red());

	seedPoint.x = end.x();
	seedPoint.y = end.y();

	cv::floodFill(mat, seedPoint, color);
	img = MatToQImage(mat);
	*/
	return img;
}

QString Brush::GetName() const
{
	return "Brush";
}
