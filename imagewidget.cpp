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
	QSize imageSize = loadedImage.size();
	image = loadedImage;
	update();
	return true;
}
