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

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

// headers
#include <QWidget>
#include <QtGui>
#include <QImage>
#include <QString>
#include <QHash>
#include <new>
#include "ringbuffer.hpp"
#include "OperationType.hpp"

// classes
class IOperation;

class ImageWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ImageWidget(QWidget *parent = 0);
	virtual ~ImageWidget() throw();

	bool OpenImage(const QString& fileName);
	bool SaveImage();
	bool SaveImage(const QString& fileName, const char *fileFormat);
	bool Undo();
	bool Redo();
	void UndoHistory();
	void ResetImage();
	bool IsChanged() const;
	QString GetFileName() const;

signals:

public slots:
	void Operation(IOperation*, const QHash<QString,QString>&, OperationType type = OperationType::Auto);
	void Arguments(const QHash<QString,QString>&);

protected:
	virtual void mousePressEvent(QMouseEvent*);
	virtual void mouseReleaseEvent(QMouseEvent*);
	virtual void mouseMoveEvent(QMouseEvent*);
	virtual void wheelEvent(QWheelEvent*);
	virtual void resizeEvent(QResizeEvent *event);
	virtual void paintEvent(QPaintEvent *);

private:
	void Draw();
	void Draw(IOperation*, const QHash<QString,QString>&);

	QImage mImage;
	QImage mOriginal;
	QImage mLiveImage;

	bool mChanged;
	RingBuffer<QImage> mUndoBuffer;
	RingBuffer<QImage> mRedoBuffer;

	QString mFileName;
	IOperation* mOperation;
	QHash<QString, QString> mArgs;
	bool mDraw;
	bool mLive;
};

#endif // IMAGEWIDGET_H
