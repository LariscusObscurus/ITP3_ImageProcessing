#include <QPainter>
#include "imagewidget.h"
#include"IOperation.h"

ImageWidget::ImageWidget(QWidget *parent) :
	QWidget(parent),
	m_penColor(Qt::black),
	m_drawing(false),
	m_undoBuffer(20),
	m_pen(m_penColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
	m_penWidth(2)
{
	setAttribute(Qt::WA_StaticContents);

}

bool ImageWidget::openImage(const QString &fileName)
{
	QImage loadedImage;
	if(!loadedImage.load(fileName)) {
		return false;
	}
	QSize imageSize = loadedImage.size();
	this->resize(imageSize);
	loadedImage.convertToFormat(QImage::Format_ARGB32);
	m_image = m_original = loadedImage;
	drawImage();
	update();
	return true;
}

bool ImageWidget::saveImage(const QString &fileName, const char *fileFormat)
{
	if(m_image.save(fileName, fileFormat)) {
		return true;
	}
	return false;
}

void ImageWidget::setPenColor(const QColor &newColor)
{
	m_penColor = newColor;
	m_pen.setColor(m_penColor);
}

void ImageWidget::setPenWidth(int width)
{
	m_penWidth = width;
	m_pen.setWidth(m_penWidth);
}

void ImageWidget::applyFilter(IOperation& filter)
{
	m_undoBuffer.push(m_image.copy());
	QMap<QString, QString> arg;
	filter.Draw(m_image, arg);
	update();

}

bool ImageWidget::undo()
{
	QImage old = m_undoBuffer.pop();
	if(old.isNull()) {
		return false;
	}
	m_image = old;
	update();
	return true;
}

bool ImageWidget::redo()
{
	return false;
}

void ImageWidget::resetImage()
{
	m_undoBuffer.push(m_image.copy());
	m_image = m_original;
	update();
}

void ImageWidget::clearImage()
{
	m_image.fill(Qt::white);
	update();
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
	m_undoBuffer.push(m_image.copy());
	if (event->button() == Qt::LeftButton) {
		m_lastPoint = event->pos();
		m_drawing = true;
	}
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton) && m_drawing) {
		drawLineTo(event->pos());
	}
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && m_drawing) {
		drawLineTo(event->pos());
		m_drawing = false;
	}
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, m_image, dirtyRect);
}

void ImageWidget::drawImage()
{
	QPainter painter(&m_image);
	painter.drawImage(QPoint(0,0), m_image);
}

void ImageWidget::drawLineTo(const QPoint &endPoint)
{
	QPainter painter(&m_image);
	painter.setPen(m_pen);
	painter.drawLine(m_lastPoint, endPoint);

	int rad = (0) + 2;
	update(QRect(m_lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
	m_lastPoint = endPoint;
}
