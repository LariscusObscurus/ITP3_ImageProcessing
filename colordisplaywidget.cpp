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
