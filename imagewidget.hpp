#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QImage>
#include <QString>
#include "ringbuffer.hpp"

class IOperation;

class ImageWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ImageWidget(QWidget *parent = 0);
	bool openImage(const QString& fileName);
	bool saveImage();
	bool saveImage(const QString& fileName, const char *fileFormat);
	void applyFilter(IOperation* filter);
	bool undo();
	bool redo();
	void undoHistory();
	void resetImage();
	void clearImage();
	QString getFileName() const;

	QColor getPenColor() const;

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
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void resizeEvent(QResizeEvent *event);
	virtual void paintEvent(QPaintEvent *);

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
	RingBuffer<QImage> m_redoBuffer;
	QPen m_pen;
	PenStyle m_penStyle;

	QString m_fileName;
	QString m_imageChanged;
	QString m_fileNameNoPath;
};

#endif // IMAGEWIDGET_H
