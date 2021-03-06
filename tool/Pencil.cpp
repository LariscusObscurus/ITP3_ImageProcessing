// Pencil.cpp

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

#include "Pencil.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QPoint>
#include <QPen>
#include <QHash>
#include <QDebug>

QImage Pencil::Draw(const QImage &img, const QHash<QString, QString> &args)
{
	QPainter painter(const_cast<QImage*>(&img));
	QColor color;
	QPoint pt, ppt;
	QPen pen;
	int size;

	// Lade argumente
	Arguments(args, ppt, pt, color, size);

	// Setze alle Werte
	pen.setWidth(size);
	pen.setColor(color);
	painter.setPen(pen);
	painter.setBrush(QBrush(color, Qt::SolidPattern));
	painter.setRenderHint(QPainter::Antialiasing);

	// Zeichne Linie
	painter.drawLine(ppt, pt);
	return img;
}

QString Pencil::GetName() const
{
	return "Pencil";
}
