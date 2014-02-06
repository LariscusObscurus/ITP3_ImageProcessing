// Flood.cpp

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

#include "Flood.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QColor>
#include <QPoint>
#include <QHash>

QImage Flood::Draw(const QImage &img, const QHash<QString, QString>& args)
{
	cv::Mat mat;
	cv::Point seedPoint;
	cv::Scalar color;
	int size;

	// Konvertiere Bild in ein valides Format
	mat = QImageRgb32ToMat24(img);

	Arguments(args, seedPoint, color, size);

	cv::floodFill(mat, seedPoint, color);
	return MatToQImage(mat);
}

QString Flood::GetName() const
{
	return "FloodFill";
}
