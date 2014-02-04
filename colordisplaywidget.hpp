/* © 2013 Leonhardt Schwarz, David Wolf
 *
 * This file is part of ImageProcessing.
 *
 * ImageProcessing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ImageProcessing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ImageProcessing.  If not, see <http://www.gnu.org/licenses/>.
 */

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
	virtual void mousePressEvent(QMouseEvent *);
	virtual void paintEvent(QPaintEvent *);
signals:
	void colorChanged(QColor color);

private:
	void drawColor();
	QColor m_selectedColor;

};

#endif // COLORDISPLAYWIDGET_H
