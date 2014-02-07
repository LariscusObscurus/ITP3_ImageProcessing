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

#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include "imagewidget.hpp"
#include "IOperation.hpp"
#include "Utility.hpp"
#include "Exception.hpp"

ImageWidget::ImageWidget(QWidget *parent) :
	QWidget(parent),
	mChanged(false),
	mUndoBuffer(20),
	mRedoBuffer(20),
	mFileName(""),
	mOperation(nullptr),
	mDraw(false),
	mLive(false)
{
	setAttribute(Qt::WA_StaticContents);
}

ImageWidget::~ImageWidget() throw()
{
}

bool ImageWidget::OpenImage(const QString &fileName)
{
	QImage loadedImage;

	if(!loadedImage.load(fileName)) {
		return false;
	}

	QSize imageSize = loadedImage.size();
	resize(imageSize);
	mImage = loadedImage.convertToFormat(QImage::Format_ARGB32);
	mOriginal = mImage.copy();
	mFileName = fileName;
	update();

	return true;
}

bool ImageWidget::SaveImage()
{
	QStringList splitedFile = mFileName.split(".");
	QString ext;

	if (!splitedFile.isEmpty()) {
		ext = splitedFile.last();
	}

	if (mImage.save(mFileName, ext.toLatin1())) {
		mChanged = false;
		return true;
	}

	return false;
}

bool ImageWidget::SaveImage(const QString &fileName, const char *fileFormat)
{
	if (mImage.save(fileName, fileFormat)) {
		mFileName = fileName;
		mChanged = false;
		return true;
	}

	return false;
}

bool ImageWidget::Undo()
{
	QImage old = mUndoBuffer.pop();

	if (!old.isNull()) {
		mRedoBuffer.push(mImage.copy());
	} else {
		return false;
	}

	mImage = old;
	update();
	return true;
}

bool ImageWidget::Redo()
{
	QImage redo = mRedoBuffer.pop();

	if (redo.isNull()) {
		return false;
	}

	mUndoBuffer.push(mImage.copy());
	mImage = redo;
	update();
	return true;
}

void ImageWidget::UndoHistory()
{
	mRedoBuffer.push(mImage.copy());

	while (true) {
		QImage current = mUndoBuffer.pop();

		if (!current.isNull()) {
			mRedoBuffer.push(current.copy());
		} else {
			mImage = mRedoBuffer.pop();
			break;
		}
	}

	update();
}

void ImageWidget::ResetImage()
{
	mUndoBuffer.push(mImage.copy());
	mImage = mOriginal.copy();
	update();
}

bool ImageWidget::IsChanged() const
{
	return mChanged;
}

QString ImageWidget::GetFileName() const
{
	return mFileName;
}

void ImageWidget::ApplyLiveImage()
{
	mUndoBuffer.push(mImage.copy());
	mLive = false;
	mImage = mLiveImage;
}

void ImageWidget::DiscardLiveImage()
{
	mLive = false;
}

void ImageWidget::Operation(IOperation *o, const QHash<QString, QString> &args, OperationType type)
{
	switch (type) {
	case OperationType::Auto:
		mOperation = o;
		mArgs = args;
		mLive = false;
		break;
	case OperationType::Live:
		mOperation = o;
		mArgs = args;
		mLive = true;
		update();
		break;
	case OperationType::Immediately:
		mLive = false;
		DrawImage(Draw(o, args));
		break;
	}
}

void ImageWidget::Arguments(const QHash<QString, QString> &args)
{
	mArgs = args;
	update();
}

QImage ImageWidget::Draw()
{
	return Draw(mOperation, mArgs);
}

QImage ImageWidget::Draw(IOperation* o, const QHash<QString,QString>& args)
{
	mRedoBuffer.clear();
	return o->Draw(mImage, args);
}

void ImageWidget::DrawImage(const QImage& img)
{
	// Wurde der Speicher kopiert dann übernimm  den neuen Speicher
	if (mImage.bits() != img.bits()) {
		mImage = img;

		if (mImage.format() == QImage::Format_RGB32 || mImage.format() == QImage::Format_RGB888) {
			mImage = mImage.convertToFormat(QImage::Format_ARGB32);
		}
	}
	update();
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);

	// Eventlogik
	if (event->button() == Qt::LeftButton) {
		// Speicher Position
		QPoint pos = event->pos();
		mArgs["PreviousX"] = QString::number(pos.x());
		mArgs["PreviousY"] = QString::number(pos.y());
		mArgs["X"] = QString::number(pos.x());
		mArgs["Y"] = QString::number(pos.y());
		// Speicher altes Bild
		mUndoBuffer.push(mImage.copy());
		mChanged = true;
		// Erlaube Zeichnen
		mDraw = true;
		// Aktualisiere Bild
		update();
	}
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
	QWidget::mouseReleaseEvent(event);

	// Eventlogik
	if (event->button() == Qt::LeftButton) {
		mDraw = false;
		// Aktualisiere Bild
		update();
	}
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
	QWidget::mouseMoveEvent(event);

	// Eventlogik
	if (mDraw && mOperation) {
		// Speicher Position
		QPoint pos = event->pos();
		mArgs["PreviousX"] = mArgs["X"];
		mArgs["PreviousY"] = mArgs["Y"];
		mArgs["X"] = QString::number(pos.x());
		mArgs["Y"] = QString::number(pos.y());
		// Aktualisiere Bild
		update();
	}
}

void ImageWidget::wheelEvent(QWheelEvent *event)
{
	QWidget::wheelEvent(event);
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	QRect dirtyRect = event->rect();

#ifdef QT_DEBUG
	try {
#endif
	if (mLive) {
		mLiveImage = mOperation->Draw(mImage.copy(), mArgs);
		painter.drawImage(dirtyRect, mLiveImage, dirtyRect);
	} else if (mDraw) {
		DrawImage(Draw());
		painter.drawImage(dirtyRect, mImage, dirtyRect);
	} else {
		painter.drawImage(dirtyRect, mImage, dirtyRect);
	}
#ifdef QT_DEBUG
	} catch (const Exception& e) {
		QMessageBox::critical(this, "Error", e.Message());
	}
#endif
}
