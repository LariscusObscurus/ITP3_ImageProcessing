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

	enum PenStyle {
		solid,
		dots
	};

signals:

public slots:
	void setPenColor(const QColor& newColor);
	void setPenWidth(int width);
	void setPenStyle(PenStyle style);

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
	int m_penWidth;

	bool m_drawing;
	QPoint m_lastPoint;
	RingBuffer<QImage> m_undoBuffer;
	QPen m_pen;
	PenStyle m_penStyle;
};

#endif // IMAGEWIDGET_H
