/* © 2013 Leonhardt Schwarz, David Wolf
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

#include <QPalette>
#include <QColorDialog>
#include <QStyleOption>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include "colordisplaywidget.hpp"

ColorDisplayWidget::ColorDisplayWidget(QWidget *parent) :
	QWidget(parent),
	m_selectedColor(Qt::black),
	m_active(false)
{
}

void ColorDisplayWidget::setColor(const QColor& color)
{
	m_selectedColor = color;
	emit colorChanged();
	update();
}

const QColor &ColorDisplayWidget::getColor()
{
	return m_selectedColor;
}

void ColorDisplayWidget::mousePressEvent(QMouseEvent *e)
{
	// Basis Event
	QWidget::mousePressEvent(e);

	// Eventlogik
	if (e->button() == Qt::LeftButton) {
		emit activated();
		m_active = true;
		QColor color =  QColorDialog::getColor(m_selectedColor, this, tr("Choose a color"), QColorDialog::ShowAlphaChannel);

		if(color.isValid()) {
			m_selectedColor = color;
			emit colorChanged();
		}
	}
}

void ColorDisplayWidget::paintEvent(QPaintEvent *e)
{
	// Basis Event
	QWidget::paintEvent(e);

	// Eventlogik
	if (m_active) {
		drawActive();
	} else {
		drawInactive();
	}
}

void ColorDisplayWidget::drawActive()
{
	QPainter painter(this);
	painter.setBrush(QBrush(m_selectedColor));
	// Zeichne ausgewählte Farbe
	painter.drawRect(0, 0, width(), height());
	// Zeichne Außenlinien
	drawLines(painter,
		QColor(32, 32, 32),
		QColor(16, 16, 16),
		QColor(128, 128, 128),
		QColor(96, 96, 96));
}

void ColorDisplayWidget::drawInactive()
{
	QPainter painter(this);
	painter.setBrush(QBrush(m_selectedColor));
	// Zeichne ausgewählte Farbe
	painter.drawRect(0, 0, width(), height());
	// Zeichne Außenlinien
	drawLines(painter,
		QColor(192, 192, 192), // Außen
		QColor(142, 142, 142), // Innen
		QColor(32, 32, 32), // Außen
		QColor(96, 96, 96)); // Innen
}

void ColorDisplayWidget::drawLines(QPainter &painter, QColor c1, QColor c2, QColor c3, QColor c4)
{
	int x = 0, y = 0;
	// Zeichne linke obere Ecke
	painter.setPen(c1);
	painter.drawLine(x, y, width(), 0); // obere Außenlinie
	painter.drawLine(x, y, 0, height()); // linke Außenlinie
	painter.setPen(c2);
	painter.drawLine(x+1, y+1, width(), 1); // obere Innenlinie
	painter.drawLine(x+1, y+1, 1, height()); // linke Innenlinie
	// Setze neue Werte
	x = width() - 1;
	y = height() - 1;
	// Zeichne rechte untere Ecke
	painter.setPen(c3);
	painter.drawLine(x, y, x, 0); // rechte Außenlinie
	painter.drawLine(x, y, 0, y); // untere Außenlinie
	painter.setPen(c4);
	painter.drawLine(x-1, y-1, x-1, 1); // rechte Innenlinie
	painter.drawLine(x-1, y-1, 1, y-1); // untere Innenlinie
}

void ColorDisplayWidget::background()
{
	m_active = false;
}

void ColorDisplayWidget::foreground()
{
	m_active = true;
}
