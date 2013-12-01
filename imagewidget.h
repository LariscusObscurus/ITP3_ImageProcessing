#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QImage>

class ImageWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ImageWidget(QWidget *parent = 0);
	bool openImage(const QString& fileName);
	bool saveImage(const QString& fileName);

signals:

public slots:

protected:
	//void resizeEvent(QResizeEvent *event);

private:
	void resizeImage(QImage *image, const QSize &newSize);

	QImage image;

};

#endif // IMAGEWIDGET_H
