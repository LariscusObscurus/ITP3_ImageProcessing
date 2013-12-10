#include <QPainter>
#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
	QWidget(parent),
	m_penColor(Qt::blue),
	m_drawing(false),
	m_undoBuffer(20)
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
	loadedImage.convertToFormat(QImage::Format_RGB32);
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
	m_undoBuffer.push(m_image);
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
	m_undoBuffer.push(m_image);
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
	painter.setPen(QPen(m_penColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawLine(m_lastPoint, endPoint);

	int rad = (0) + 2;
	update(QRect(m_lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
	m_lastPoint = endPoint;
}
