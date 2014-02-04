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
#include "colordisplaywidget.hpp"

ColorDisplayWidget::ColorDisplayWidget(QWidget *parent) :
	QWidget(parent),
	m_selectedColor(Qt::black)
{
}

void ColorDisplayWidget::setColor(QColor color)
{
	m_selectedColor = color;
}

const QColor ColorDisplayWidget::getColor()
{
	return m_selectedColor;
}

void ColorDisplayWidget::mousePressEvent(QMouseEvent *e)
{
	// Basis Event
	QWidget::mousePressEvent(e);

	// Eventlogik
	QColorDialog colDia;
	QColor color =  colDia.getColor(Qt::white, this, tr("Choose Color"), QColorDialog::ShowAlphaChannel);

	if(color.isValid()) {
		m_selectedColor = color;
		emit colorChanged(m_selectedColor);
	} else {
		emit colorChanged(m_selectedColor);
	}
}

void ColorDisplayWidget::paintEvent(QPaintEvent *e)
{
	// Basis Event
	QWidget::paintEvent(e);

	// Eventlogik
	QPainter painter(this);

	painter.setPen(QColor(
			       255 - m_selectedColor.red(),
			       255 - m_selectedColor.green(),
			       255 - m_selectedColor.blue()));
	painter.setBrush(QBrush(m_selectedColor));
	painter.drawRect(0, 0, width()-1, height()-1);
}
