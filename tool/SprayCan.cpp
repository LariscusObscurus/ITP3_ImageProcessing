// SprayCan.cpp

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

#include "SprayCan.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QPoint>
#include <QDebug>

QImage SprayCan::Draw(const QImage &img, const QHash<QString, QString>& args)
{
	QPainter painter(const_cast<QImage*>(&img));
	QColor color;
	QPoint pt, ppt;
	int size;

	// Lade argumente
	Arguments(args, ppt, pt, color, size);

	int numSteps = 2 + (pt - ppt).manhattanLength() / 2;

	// Setze allgemeine Werte
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);

	// Zeichne Kreis
	for (int i = 0; i < numSteps; ++i) {
		QRectF rect;
		int x = ppt.x() + i * (pt.x() - ppt.x()) / (numSteps - 1);
		int y = ppt.y() + i * (pt.y() - ppt.y()) / (numSteps - 1);

		// Äußerer Kreis
		rect = QRectF(x - (size / 2.f), y - (size / 2.f), size, size);
		painter.setBrush(QBrush(color, Qt::Dense7Pattern));
		painter.drawEllipse(rect);

		// Mittlerer Kreis
		rect = QRectF(x - (size / 3.f), y - (size / 3.f), size * 2.f / 3.f, size * 2.f / 3.f);
		painter.setBrush(QBrush(color, Qt::Dense6Pattern));
		painter.drawEllipse(rect);

		// Innerer Kreis
		rect = QRectF(x - (size / 4.f), y - (size / 4.f), size / 2.f, size / 2.f);
		painter.setBrush(QBrush(color, Qt::Dense5Pattern));
		painter.drawEllipse(rect);
	}

	return img;
}

QString SprayCan::GetName() const
{
	return "AirBrush";
}
