#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QImage>
#include "ringbuffer.h"

class IOperation;

class ImageWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ImageWidget(QWidget *parent = 0);
	bool openImage(const QString& fileName);
	bool saveImage(const QString& fileName, const char *fileFormat);
	void applyFilter(IOperation& filter);
	bool undo();
	bool redo();
	void resetImage();
	void clearImage();

signals:

public slots:
	void setPenColor(const QColor &newColor);

protected:
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *);

private:
	void drawImage();
	void drawLineTo(const QPoint &endPoint);

	QImage m_image;
	QImage m_original;
	QColor m_penColor;

	bool m_drawing;
	QPoint m_lastPoint;
	RingBuffer<QImage> m_undoBuffer;
};

#endif // IMAGEWIDGET_H
