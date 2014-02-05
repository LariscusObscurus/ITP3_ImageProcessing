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
#include "tools/Pencil.hpp"
#include "tools/Flood.hpp"

QHash<Tool, IOperation*> ImageWidget::s_tools;

ImageWidget::ImageWidget(QWidget *parent) :
	QWidget(parent),
	m_penColor(Qt::black),
	m_changed(false),
	m_undoBuffer(20),
	m_redoBuffer(20),
	m_pen(m_penColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
	m_penWidth(2),
	m_tool(Tool::Pencil),
	m_fileName("")
{
	setAttribute(Qt::WA_StaticContents);

	if (s_tools.isEmpty()) {
		s_tools[Tool::Pencil] = new Pencil();
		s_tools[Tool::FloodFill] = new Flood();
	}
}

ImageWidget::~ImageWidget() throw()
{
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

	if (m_image.save(m_fileName, ext.toLatin1())) {
		m_changed = false;
		return true;
	}

	return false;
}

bool ImageWidget::saveImage(const QString &fileName, const char *fileFormat)
{
	if (m_image.save(fileName, fileFormat)) {
		m_fileName = fileName;
		m_changed = false;
		return true;
	}

	return false;
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
	m_tool = tool;
}

void ImageWidget::applyFilter(IOperation* filter)
{
	m_undoBuffer.push(m_image.copy());
	QHash<QString, QString> arg;
	m_image = filter->Draw(m_image, arg);
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

bool ImageWidget::isChanged() const
{
	return m_changed;
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
		m_changed = true;
	}
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton)) {
		draw(event->pos());
	}
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		draw(event->pos());
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

void ImageWidget::clearTools()
{
	for (auto& it : s_tools) {
		delete it;
	}
}

void ImageWidget::drawImage()
{
	QPainter painter(&m_image);
	painter.drawImage(QPoint(0,0), m_image);
}

void ImageWidget::draw(const QPoint &endPoint)
{
#ifdef QT_DEBUG
	try {
#endif
	switch (m_tool) {
	case Tool::Pencil:
		drawBasicBrush(Tool::Pencil, endPoint);
		break;
	case Tool::FloodFill:
		drawFloodFill(endPoint);
		break;
	default:
		QMessageBox::information(0, "Information", "Tool is not yet implemented.");
		break;
	}

	update();
	m_lastPoint = endPoint;
#ifdef QT_DEBUG
	} catch (Exception& e) {
		QMessageBox::critical(0, "Error", e.Message());
	}
#endif
}

void ImageWidget::drawGeneric(IOperation* o, const QHash<QString, QString> &args)
{
	QImage img = o->Draw(m_image, args);

	if (img.format() == QImage::Format_RGB888) {
		m_image = img.convertToFormat(QImage::Format_ARGB32);
	}
}

void ImageWidget::drawBasicBrush(Tool tool, const QPoint &endPoint)
{
	QHash<QString, QString> args;

	// Setze notwendige Argumente
	args["X1"] = QString::number(m_lastPoint.x());
	args["Y1"] = QString::number(m_lastPoint.y());
	args["X2"] = QString::number(endPoint.x());
	args["Y2"] = QString::number(endPoint.y());
	args["Size"] = QString::number(m_penWidth);
	args["Red"] = QString::number(m_penColor.red());
	args["Green"] = QString::number(m_penColor.green());
	args["Blue"] = QString::number(m_penColor.blue());

	drawGeneric(s_tools[tool], args);
}

void ImageWidget::drawFloodFill(const QPoint &endPoint)
{
	QImage img;
	QHash<QString, QString> args;
	IOperation* o = s_tools[Tool::FloodFill];

	// Setze notwendige Argumente
	args["X"] = QString::number(endPoint.x());
	args["Y"] = QString::number(endPoint.y());
	args["Red"] = QString::number(m_penColor.red());
	args["Green"] = QString::number(m_penColor.green());
	args["Blue"] = QString::number(m_penColor.blue());

	img = o->Draw(m_image, args);

	if (img.format() == QImage::Format_RGB888) {
		m_image = img.convertToFormat(QImage::Format_ARGB32);
	}
}
