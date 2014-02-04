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
	setStyleSheet("");
	QColorDialog colDia;
	QColor color =  colDia.getColor(Qt::white,this,tr("Choose Color"),QColorDialog::ShowAlphaChannel);

	if(color.isValid()) {
		m_selectedColor = color;
		drawColor();
		emit colorChanged(m_selectedColor);
	} else {
		drawColor();
		emit colorChanged(m_selectedColor);
	}
}

void ColorDisplayWidget::paintEvent(QPaintEvent *)
{
	QStyleOption option;
	QPainter painter(this);
	option.init(this);
	style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void ColorDisplayWidget::drawColor()
{
	setStyleSheet(QString("border: 1px solid rgb(%1, %2, %3); background-color: rgb(%4, %5, %6);").arg(
			      QString::number(255 - m_selectedColor.red()),
			      QString::number(255 - m_selectedColor.green()),
			      QString::number(255 - m_selectedColor.blue()),
			      QString::number(m_selectedColor.red()),
			      QString::number(m_selectedColor.green()),
			      QString::number(m_selectedColor.blue())));
}
