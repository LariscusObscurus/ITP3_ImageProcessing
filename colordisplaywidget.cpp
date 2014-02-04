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
#include "colordisplaywidget.hpp"

ColorDisplayWidget::ColorDisplayWidget(QWidget *parent) :
	QWidget(parent),
	m_selectedColor(Qt::black)
{
	drawColor();
}

void ColorDisplayWidget::setColor(QColor color)
{
	m_selectedColor = color;
	drawColor();
}

const QColor ColorDisplayWidget::getColor()
{
	return m_selectedColor;
}

void ColorDisplayWidget::mousePressEvent(QMouseEvent *)
{
	QColorDialog colDia;
	QColor color =  colDia.getColor(Qt::white,this,tr("Farbe auswählen"),QColorDialog::ShowAlphaChannel);

	if(color.isValid()) {
		m_selectedColor = color;
		drawColor();
		emit colorChanged(m_selectedColor);
	}
}

void ColorDisplayWidget::drawColor()
{
	QPalette pal(palette());
	pal.setColor(QPalette::Background,m_selectedColor);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->show();
}
