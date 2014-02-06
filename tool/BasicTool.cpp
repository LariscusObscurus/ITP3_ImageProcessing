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

#include "BasicTool.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QColor>
#include <QPoint>
#include <QHash>
#include <QDebug>

void BasicTool::Arguments(const QHash<QString, QString> &args, cv::Point& pt, cv::Scalar& color, int& size)
{
	bool ok = false;
	int r, g, b, a;
	QHash<QString, QString>::const_iterator it;

	// x
	if ((it = args.find("X")) != args.end()) {
		pt.x = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"X\" argument for tool");
		}
	}
	// y
	if ((it = args.find("Y")) != args.end()) {
		pt.y = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Y\" argument for tool");
		}
	}
	// size
	if ((it = args.find("Size")) != args.end()) {
		size = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Size\" argument for tool");
		}
	}
	// red
	if ((it = args.find("Red")) != args.end()) {
		r = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Red\" argument for tool");
		}
	}
	// green
	if ((it = args.find("Green")) != args.end()) {
		g = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Green\" argument for tool");
		}
	}
	// blue
	if ((it = args.find("Blue")) != args.end()) {
		b = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Blue\" argument for tool");
		}
	}
	// alpha
	if ((it = args.find("Alpha")) != args.end()) {
		a = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Blue\" argument for tool");
		}
	}

	color = cv::Scalar(b, g, r, a);
}
