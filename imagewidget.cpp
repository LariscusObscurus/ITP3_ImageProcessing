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
	m_penColor(Qt::black),
	m_drawing(false),
	m_undoBuffer(20),
	m_redoBuffer(20),
	m_pen(m_penColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
	m_penWidth(2),
	m_tool(Tool::Pencil),
	m_fileName("")
{
	setAttribute(Qt::WA_StaticContents);
}

bool ImageWidget::openImage(const QString &fileName)
{
	QImage loadedImage;

	if(!loadedImage.load(fileName)) {
		return false;
	}

	QSize imageSize = loadedImage.size();
	resize(imageSize);
	loadedImage.convertToFormat(QImage::Format_ARGB32);
	m_image = m_original = loadedImage;
	m_fileName = fileName;
	drawImage();
	update();

	return true;
}

bool ImageWidget::saveImage()
{
	QStringList splitedFile = m_fileName.split(".");
	QString ext;

	if (!splitedFile.isEmpty()) {
		ext = splitedFile.last();
	}

	return (m_image.save(m_fileName, ext.toLatin1()));
}

bool ImageWidget::saveImage(const QString &fileName, const char *fileFormat)
{
	return (m_image.save(fileName, fileFormat));
}

QColor ImageWidget::getPenColor() const
{
	return m_penColor;
}

void ImageWidget::setPenColor(const QColor &newColor)
{
	m_penColor = newColor;
	m_pen.setColor(m_penColor);
}

void ImageWidget::setPenWidth(int width)
{
	m_penWidth = width;
}

void ImageWidget::toolChanged(Tool tool)
{
	switch (tool) {
	case Tool::Pencil:
		m_tool = tool;
		break;
	default:
		QMessageBox::critical(0, "Error", "Tool is not yet implemented.");
		break;
	}
}

void ImageWidget::applyFilter(IOperation* filter)
{
	m_undoBuffer.push(m_image.copy());
	QMap<QString, QString> arg;
	filter->Draw(m_image, arg);
	update();

}

bool ImageWidget::undo()
{
	QImage old = m_undoBuffer.pop();

	if (!old.isNull()) {
		m_redoBuffer.push(m_image.copy());
	} else {
		return false;
	}

	m_image = old;
	update();
	return true;
}

bool ImageWidget::redo()
{
	QImage redo = m_redoBuffer.pop();

	if (redo.isNull()) {
		return false;
	}

	m_undoBuffer.push(m_image.copy());
	m_image = redo;
	update();
	return true;
}

void ImageWidget::undoHistory()
{
	m_redoBuffer.push(m_image.copy());

	while (true) {
		QImage current = m_undoBuffer.pop();

		if (!current.isNull()) {
			m_redoBuffer.push(current.copy());
		} else {
			m_image = m_redoBuffer.pop();
			break;
		}
	}

	update();
}

void ImageWidget::resetImage()
{
	m_undoBuffer.push(m_image.copy());
	m_image = m_original;
	update();
}

void ImageWidget::clearImage()
{
	m_image.fill(Qt::white);
	update();
}

QString ImageWidget::getFileName() const
{
	return m_fileName;
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{

	if (event->button() == Qt::LeftButton) {
		m_undoBuffer.push(m_image.copy());
		m_lastPoint = event->pos();
		m_redoBuffer.clear();
		m_drawing = true;
	}
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton) && m_drawing) {
		drawLineTo(event->pos());
	}
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && m_drawing) {
		drawLineTo(event->pos());
		m_drawing = false;
	}
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, m_image, dirtyRect);
}

void ImageWidget::drawImage()
{
	QPainter painter(&m_image);
	painter.drawImage(QPoint(0,0), m_image);
}

void ImageWidget::drawLineTo(const QPoint &endPoint)
{
	bool ok = false;

	QPainter painter(&m_image);
	painter.setBrush(QBrush(m_penColor));
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setPen(m_pen);

	switch (m_tool) {
	case Tool::Pencil:
		m_pen.setWidth(m_penWidth);
		painter.drawLine(m_lastPoint, endPoint);
		ok = true;
		break;
	default:
		break;
	}

	if (ok) {
		update();
		m_lastPoint = endPoint;
	}
}
