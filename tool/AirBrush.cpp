// AirBrush.cpp

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

#include "AirBrush.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QPoint>
#include <QDebug>

QImage AirBrush::Draw(const QImage &img, const QHash<QString, QString>& args)
{
	QPainter painter(const_cast<QImage*>(&img));
	QColor color;
	QPoint pt, ppt;
	int size;

	// Lade argumente
	Arguments(args, ppt, pt, color, size);

	// Setze alle Werte
	int numSteps = 2 + (pt - ppt).manhattanLength() / 2;
	painter.setBrush(QBrush(color, Qt::Dense6Pattern));
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);

	// Zeichne Kreis
	for (int i = 0; i < numSteps; ++i) {
		int x = ppt.x() + i * (pt.x() - ppt.x()) / (numSteps - 1);
		int y = ppt.y() + i * (pt.y() - ppt.y()) / (numSteps - 1);

		painter.drawEllipse(x - (size / 2), y - (size / 2), size, size);
	}

	return img;
}

QString AirBrush::GetName() const
{
	return "AirBrush";
}
