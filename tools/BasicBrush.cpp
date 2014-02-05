// BasicBrush.cpp

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

#include "BasicBrush.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QColor>
#include <QPoint>
#include <QHash>

void BasicBrush::Arguments(const QHash<QString, QString> &args, cv::Point& pt1, cv::Point& pt2, cv::Scalar& color, int& size)
{
	bool ok = false;
	int r, g, b;
	QHash<QString, QString>::const_iterator it;

	// x1
	if ((it = args.find("X1")) != args.end()) {
		pt1.x = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"X1\" argument for pencil tool");
		}
	}
	// y1
	if ((it = args.find("Y1")) != args.end()) {
		pt1.y = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Y1\" argument for pencil tool");
		}
	}
	// x2
	if ((it = args.find("X2")) != args.end()) {
		pt2.x = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"X2\" argument for pencil tool");
		}
	}
	// y2
	if ((it = args.find("Y2")) != args.end()) {
		pt2.y = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Y2\" argument for pencil tool");
		}
	}
	// size
	if ((it = args.find("Size")) != args.end()) {
		size = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Size\" argument for pencil tool");
		}
	}
	// red
	if ((it = args.find("Red")) != args.end()) {
		r = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Red\" argument for pencil tool");
		}
	}
	// green
	if ((it = args.find("Green")) != args.end()) {
		g = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Green\" argument for pencil tool");
		}
	}
	// blue
	if ((it = args.find("Blue")) != args.end()) {
		b = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Blue\" argument for pencil tool");
		}
	}
	color = CV_RGB(r, g, b);
}
