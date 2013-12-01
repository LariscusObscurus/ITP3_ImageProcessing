#include <QPainter>
#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
	QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
}

bool ImageWidget::openImage(const QString &fileName)
{
	QImage loadedImage;
	if(!loadedImage.load(fileName)) {
		return false;
	}
	//QSize imageSize = loadedImage.size();
	loadedImage.convertToFormat(QImage::Format_RGB32);
	m_image = loadedImage;
	drawImage();
	update();
	return true;
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
