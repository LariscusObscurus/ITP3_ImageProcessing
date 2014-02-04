#ifndef COLORDISPLAYWIDGET_H
#define COLORDISPLAYWIDGET_H

#include <QWidget>

class ColorDisplayWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ColorDisplayWidget(QWidget *parent = 0);
	void setColor(QColor color);
	const QColor getColor();

protected:
	void mousePressEvent(QMouseEvent *);
signals:
	void colorChanged(QColor color);

private:
	void drawColor();
	QColor m_selectedColor;

};

#endif // COLORDISPLAYWIDGET_H
