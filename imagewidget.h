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
	bool saveImage(const QString& fileName, const char *fileFormat);
	void setPenColor(const QColor &newColor);
	void clearImage();

signals:

public slots:

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
	QColor m_penColor;

	bool m_drawing;
	QPoint m_lastPoint;
};

#endif // IMAGEWIDGET_H
