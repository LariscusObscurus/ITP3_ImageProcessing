/* © 2013 Leonhardt Schwarz, Tom Schalbar, David Wolf
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

#include <QtGui>
#include <QtCore>
#include <QStyle>
#include <QChar>
#include <QFileDialog>
#include <QScrollArea>
#include <QMessageBox>
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "ueberdialog.hpp"
#include "filters/BilateralFilter.hpp"
#include "filters/Blur.hpp"
#include "filters/Dilation.hpp"
#include "filters/Erosion.hpp"
#include "filters/GaussianBlur.hpp"
#include "filters/Grayscale.hpp"
#include "filters/MedianBlur.hpp"
#include "filters/Outline.hpp"
#include "filters/Sobel.hpp"
#include "filters/Canny.hpp"
#include "Exception.hpp"
#include "Utility.hpp"
#include "InputManager.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mDia(new SizeDialogue),
	mInputManager(new InputManager()),
	mDummyImage(new ImageWidget())
{
	ui->setupUi(this);
	setWindowTitle("Image Processing");

	ui->ColorPickerFront->setColor(Qt::black);
	ui->ColorPickerBack->setColor(Qt::white);
	ui->ColorPickerFront->foreground();
	ui->ColorPickerBack->background();

	// Mouse Tracking standardmäßig deaktivieren
	setMouseTracking(false);

	connectSignals();
}

MainWindow::~MainWindow()
{
	delete mDummyImage;
	delete mInputManager;
	delete mDia;
	delete ui;
}

void MainWindow::connectSignals()
{
	// DummyImage
	connect(ui->ColorPickerFront, SIGNAL(colorChanged(QColor)), mDummyImage, SLOT(setPenColor(QColor)));
	connect(this, SIGNAL(toolChanged(Tool)), mDummyImage, SLOT(toolChanged(Tool)));
	connect(mDia, SIGNAL(sizeChanged(int)), mDummyImage, SLOT(setPenWidth(int)));

	// Vor- und Hintergrundfarbe
	connect(ui->ColorPickerFront, SIGNAL(activated()), ui->ColorPickerBack, SLOT(background()));
	connect(ui->ColorPickerBack, SIGNAL(activated()), ui->ColorPickerFront, SLOT(background()));

	// close
	//connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::on_actionOpen_triggered()
{
	ui->statusbar->showMessage("Open File",2000);
	QString fileName = QFileDialog::getOpenFileName(
				this,
				tr("Open Image File"),
				QDir::homePath(),
				tr("Images (*.bmp *.png *.jpg *.jpeg *.ppm *.xbm *.xpm);;All Files (*)"));

	if(fileName.isEmpty()) {
		return;
	}

	// Überprüfe ob das Bild bereits offen ist
	for (int i = 0; i < ui->imagetab->count(); i++) {
		QWidget* widget = ui->imagetab->widget(i);

		if (widget) {
			QScrollArea* area = qobject_cast<QScrollArea*>(widget);
			ImageWidget* img = qobject_cast<ImageWidget*>(area->widget());

			// ist das Bild bereits geladen, dann änder zu den entsprechenden Tab
			if (img && img->getFileName() == fileName) {
				ui->imagetab->setCurrentIndex(i);
				return;
			}
		}
	}

	// Falls das Bild noch nicht geladen wurde, dann lade es jetzt
	openImage(fileName);
}

void MainWindow::openImage(const QString &fileName)
{
	QScrollArea* area = new QScrollArea();
	ImageWidget* img = new ImageWidget();

	// Nur les- und schreibbare Bildformate werden unterstützt
	if (img->openImage(fileName)) {
		QString shortFileName = ExtractFileName(fileName);
		shortFileName = shortFileName.mid(0, shortFileName.lastIndexOf('.'));

		// Bild in die ScrollArea laden
		area->setWidget(img);
		area->setStyleSheet("background: qlineargradient(x1: 0, y0: 1, x2:1, y2: 0, stop: 0.96 #383838, stop: 0.99 #2e2e2e);");

		// neuen Tab hinzufügen
		int index = ui->imagetab->addTab(area, shortFileName);
		ui->imagetab->setTabToolTip(index, shortFileName);
		ui->imagetab->setCurrentIndex(index);

		// schließlich Signalhandler setzen
		connect(ui->ColorPickerFront, SIGNAL(colorChanged(QColor)), img, SLOT(setPenColor(QColor)));
		connect(this, SIGNAL(toolChanged(Tool)), img, SLOT(toolChanged(Tool)));
		connect(mDia, SIGNAL(sizeChanged(int)), img, SLOT(setPenWidth(int)));
		img->setPenColor(ui->ColorPickerFront->getColor());
	}
}

ImageWidget* MainWindow::getImageWidget() const
{
	QWidget* widget = ui->imagetab->currentWidget();

	if (widget) {
		QScrollArea* area = qobject_cast<QScrollArea*>(widget);
		return qobject_cast<ImageWidget*>(area->widget());
	} else {
		return nullptr;
	}
}

/*
void MainWindow::on_actionClose_triggered()
{
	ui->statusbar->showMessage("Quit Image Processing",2000);
}
*/

void MainWindow::on_actionAbout_triggered()
{
	Ueberdialog about;
	about.setModal(true);
	about.exec();
}

void MainWindow::on_actionSave_triggered()
{
	ImageWidget* img = getImageWidget();

	if (img) {
		img->saveImage();
	}
}

void MainWindow::on_actionSaveAs_triggered()
{
	ui->statusbar->showMessage("Save As", 2000);

	// Nur les- und schreibbare Bildformate werden unterstützt
	QString fileName = QFileDialog::getSaveFileName(
				this,
				tr("Save Image"),
				QDir::homePath(),
				tr("Windows Bitmap (*.bmp);;Joint Photographic Experts Group (*.jpg *.jpeg);;Portable Network Graphics (*.png);;Portable Pixmap (*.ppm);;X11 Bitmap (*.xbm);;X11 Pixmap (*.xpm)"));
	QStringList splitedFile = fileName.split(".");
	QString ext;

	if(!splitedFile.isEmpty()) {
		ext = splitedFile.takeLast();
	}

	if(!fileName.isEmpty()) {
		ImageWidget* img = getImageWidget();

		if (img) {
			img->saveImage(fileName, ext.toLatin1());
		}
	}
}

void MainWindow::on_actionUndo_triggered()
{
	ImageWidget* img = getImageWidget();

	if (img) {
		ui->statusbar->showMessage("Undo", 2000);
		img->undo();
	}
}

void MainWindow::on_actionRedo_triggered()
{
	ImageWidget* img = getImageWidget();

	if (img) {
		ui->statusbar->showMessage("Redo", 2000);
		img->redo();
	}
}

void MainWindow::on_actionUndoHistory_triggered()
{
	ImageWidget* img = getImageWidget();

	if (img) {
		ui->statusbar->showMessage("Undo History", 2000);
		img->undoHistory();
	}
}

void MainWindow::on_actionResetImage_triggered()
{
	ImageWidget* img = getImageWidget();

	if (img) {
		ui->statusbar->showMessage("Reset Image", 2000);
		img->resetImage();
	}
}

void MainWindow::on_btnPencil_clicked()
{
	emit toolChanged(Tool::Pencil);
}

void MainWindow::on_btnBrush_clicked()
{
	emit toolChanged(Tool::Brush);
}

void MainWindow::on_btnEraser_clicked()
{
	emit toolChanged(Tool::Eraser);
}

void MainWindow::on_btnMagicWand_clicked()
{
	emit toolChanged(Tool::MagicWand);
}

void MainWindow::on_btnMagnifier_clicked()
{
	emit toolChanged(Tool::Magnifiere);
}

void MainWindow::on_btnFloodFill_clicked()
{
	emit toolChanged(Tool::FloodFill);
}

void MainWindow::on_btnCrop_clicked()
{
	emit toolChanged(Tool::Crop);
}

void MainWindow::on_btnStamp_clicked()
{
	emit toolChanged(Tool::Stamp);
}

void MainWindow::on_btnGeometry_clicked()
{
	emit toolChanged(Tool::Geometry);
}

void MainWindow::on_btnText_clicked()
{
	emit toolChanged(Tool::Text);
}

void MainWindow::on_btnSprayCan_clicked()
{
	emit toolChanged(Tool::SprayCan);
}

void MainWindow::on_btnInk_clicked()
{
	emit toolChanged(Tool::Ink);
}

void MainWindow::on_btnAirbrush_clicked()
{
	emit toolChanged(Tool::Airbrush);
}

void MainWindow::on_btnEyedropper_clicked()
{
	emit toolChanged(Tool::EyeDropper);
}

void MainWindow::on_actionBrushSize_triggered()
{
	mDia->setModal(true);
	mDia->exec();
	ui->statusbar->showMessage("Brush Size", 2000);
}

void MainWindow::on_imagetab_currentChanged(int)
{
	ImageWidget* img = getImageWidget();

	if (img) {
		setWindowTitle(ExtractFileName(img->getFileName()));
	} else {
		setWindowTitle("Image Processing");
	}
}

void MainWindow::on_imagetab_tabCloseRequested(int index)
{
	QWidget* widget = ui->imagetab->widget(index);
	ui->imagetab->removeTab(index);

	if (widget) {
		widget->deleteLater();
	}
}

void MainWindow::showError(const Exception &e)
{
	QMessageBox::critical(0, "Error", e.Message());
}

void MainWindow::applyFilter(IOperation* operation)
{
	try {
		ImageWidget* img = getImageWidget();

		if (img) {
			img->applyFilter(operation);
		}
	} catch (Exception& e) {
		showError(e);
	}

	delete operation;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	// Basis Event
	QMainWindow::keyPressEvent(e);
	// Eventlogik
	mInputManager->KeyPressEvent(e);
}

void MainWindow::keyReleasedEvent(QKeyEvent *e)
{
	// Basis Event
	QMainWindow::keyReleaseEvent(e);
	// Eventlogik
	mInputManager->KeyReleaseEvent(e);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	// Basis Event
	QMainWindow::mousePressEvent(e);
	// Eventlogik
	mInputManager->MousePressEvent(e);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
	// Basis Event
	QMainWindow::mouseReleaseEvent(e);
	// Eventlogik
	mInputManager->MouseReleaseEvent(e);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
	// Basis Event
	QMainWindow::mouseDoubleClickEvent(e);
	// Eventlogik
	mInputManager->MouseDoubleClickEvent(e);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	// Basis Event
	QMainWindow::mouseMoveEvent(e);
	// Eventlogik
	mInputManager->MouseMoveEvent(e);
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
	// Basis Event
	QMainWindow::wheelEvent(e);
	// Eventlogik
	mInputManager->MouseWheelEvent(e);
}

void MainWindow::on_actionBlur_triggered()
{
	applyFilter(new Blur());
}

void MainWindow::on_actionGaussianBlur_triggered()
{
	applyFilter(new GaussianBlur());
}

void MainWindow::on_actionMedianBlur_triggered()
{
	applyFilter(new MedianBlur());
}

void MainWindow::on_actionBilateralFilter_triggered()
{
	applyFilter(new BilateralFilter());
}

void MainWindow::on_actionEdge_triggered()
{
	applyFilter(new Outline());
}

void MainWindow::on_actionCanny_triggered()
{
	applyFilter(new Canny());
}

void MainWindow::on_actionSobel_triggered()
{
	applyFilter(new Sobel());
}

void MainWindow::on_actionDilation_triggered()
{
	applyFilter(new Dilation());
}

void MainWindow::on_actionErosion_triggered()
{
	applyFilter(new Erosion());
}

void MainWindow::on_actionGrayscale_triggered()
{
	applyFilter(new Grayscale());
}
