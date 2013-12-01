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
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *);

private:
	void drawImage();

	QImage m_image;

};

#endif // IMAGEWIDGET_H
