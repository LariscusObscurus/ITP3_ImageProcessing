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
#include "imagewidget.hpp"
#include "ui_mainwindow.h"
#include "ueberdialog.hpp"
#include "filter/BilateralFilter.hpp"
#include "filter/Blur.hpp"
#include "filter/Dilation.hpp"
#include "filter/Erosion.hpp"
#include "filter/GaussianBlur.hpp"
#include "filter/MedianBlur.hpp"
#include "filter/Outline.hpp"
#include "filter/Sobel.hpp"
#include "filter/Canny.hpp"
#include "color/Grayscale.hpp"
#include "tool/Pencil.hpp"
#include "tool/Flood.hpp"
#include "tool/Brush.hpp"
#include "Exception.hpp"
#include "Utility.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mSizeDialog(new SizeDialogue),
	mSize(1),
	mOperation(nullptr)
{
	ui->setupUi(this);
	setWindowTitle("Image Processing");

	ui->ColorPickerFront->setColor(Qt::black);
	ui->ColorPickerBack->setColor(Qt::white);
	ui->ColorPickerFront->foreground();
	ui->ColorPickerBack->background();

	// Mouse Tracking standardmäßig deaktivieren
	setMouseTracking(false);

	// Erzeuge alle Operationen
	createOperations();

	connectSignals();
}

MainWindow::~MainWindow()
{
	clearOperations();
	delete mSizeDialog;
	delete ui;
}

void MainWindow::createOperations()
{
	try {
		// Filter
		mOperations["BilateralFilter"] = new BilateralFilter();
		mOperations["Blur"] = new Blur();
		mOperations["Canny"] = new Canny();
		mOperations["Dilation"] = new Dilation();
		mOperations["Erosion"] = new Erosion();
		mOperations["GaussianBlur"] = new GaussianBlur();
		mOperations["MedianBlur"] = new MedianBlur();
		mOperations["Outline"] = new Outline();
		mOperations["Sobel"] = new Sobel();

		// Color
		mOperations["Grayscale"] = new Grayscale();

		// Tool
		mOperations["Pencil"] = new Pencil();
		mOperations["Brush"] = new Brush();
		mOperations["FloodFill"] = new Flood();
	} catch (const std::bad_alloc& e) {
		clearOperations();
		QMessageBox::critical(0, "Memory Error", e.what());
	} catch (...) {
		clearOperations();
		QMessageBox::critical(0, "Unknown Error", "Unknown error occured");
	}

	// Setzte Bleistift als erstes Werkzeug
	mOperation = mOperations["Pencil"];
}

void MainWindow::connectSignals()
{
	// Hauptfarbe
	connect(ui->ColorPickerFront, SIGNAL(activated()), ui->ColorPickerBack, SLOT(background()));
	connect(ui->ColorPickerFront, SIGNAL(colorChanged()), this, SLOT(ColorChanged()));
	// Sekundärfarbe
	connect(ui->ColorPickerBack, SIGNAL(activated()), ui->ColorPickerFront, SLOT(background()));

	// Werkzeuggröße
	connect(mSizeDialog, SIGNAL(sizeChanged(int)), this, SLOT(SizeChanged(int)));

	// close
	//connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::clearOperations()
{
	for (auto& it : mOperations) {
		if (it) {
			delete it;
		}
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

void MainWindow::openImage(const QString &fileName)
{
	QScrollArea* area = new QScrollArea();
	ImageWidget* img = new ImageWidget();

	// Nur les- und schreibbare Bildformate werden unterstützt
	if (img->OpenImage(fileName)) {
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
		connect(this, SIGNAL(Operation(IOperation*,QHash<QString,QString>)), img, SLOT(Operation(IOperation*,QHash<QString,QString>)));
		connect(this, SIGNAL(Operation(IOperation*,QHash<QString,QString>,bool)), img, SLOT(Operation(IOperation*,QHash<QString,QString>,bool)));
		emit Operation(mOperation, GetArgs());
	}
}

QHash<QString,QString> MainWindow::GetArgs() const
{
	QHash<QString, QString> args;
	QColor color = ui->ColorPickerFront->getColor();

	args["Size"] = QString::number(mSize);
	args["Red"] = QString::number(color.red());
	args["Green"] = QString::number(color.green());
	args["Blue"] = QString::number(color.blue());
	args["Alpha"] = QString::number(color.alpha());

	return args;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	// Basis Event
	QMainWindow::keyPressEvent(e);
}

void MainWindow::keyReleasedEvent(QKeyEvent *e)
{
	// Basis Event
	QMainWindow::keyReleaseEvent(e);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	// Basis Event
	QMainWindow::mousePressEvent(e);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
	// Basis Event
	QMainWindow::mouseReleaseEvent(e);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *e)
{
	// Basis Event
	QMainWindow::mouseDoubleClickEvent(e);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	// Basis Event
	QMainWindow::mouseMoveEvent(e);
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
	// Basis Event
	QMainWindow::wheelEvent(e);
}

void MainWindow::SizeChanged(int value)
{
	mSize = value;
	emit Operation(mOperation, GetArgs());
}

void MainWindow::ColorChanged()
{
	emit Operation(mOperation, GetArgs());
}

void MainWindow::on_actionNew_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionOpen_triggered()
{
	ui->statusbar->showMessage("Open File",2000);
	QString fileName = QFileDialog::getOpenFileName(
				this,
				tr("Open Image File"),
				QDir::homePath(),
				tr("Images (*.bmp *.png *.jpg *.jpeg *.ppm *.xbm *.xpm);;All Files (*)"));

	if (fileName.isEmpty()) {
		return;
	}

	// Überprüfe ob das Bild bereits offen ist
	for (int i = 0; i < ui->imagetab->count(); i++) {
		QWidget* widget = ui->imagetab->widget(i);

		if (widget) {
			QScrollArea* area = qobject_cast<QScrollArea*>(widget);
			ImageWidget* img = qobject_cast<ImageWidget*>(area->widget());

			// ist das Bild bereits geladen, dann ändere zu den entsprechenden Tab
			if (img && img->GetFileName() == fileName) {
				ui->imagetab->setCurrentIndex(i);
				return;
			}
		}
	}

	// Falls das Bild noch nicht geladen wurde, dann lade es jetzt
	openImage(fileName);
}

void MainWindow::on_actionClose_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
	//ui->statusbar->showMessage("Quit Image Processing",2000);
}

void MainWindow::on_actionCloseAll_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionQuit_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

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
		img->SaveImage();
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
			img->SaveImage(fileName, ext.toLatin1());
		}
	}
}

void MainWindow::on_actionUndo_triggered()
{
	ImageWidget* img = getImageWidget();

	if (img) {
		ui->statusbar->showMessage("Undo", 2000);
		img->Undo();
	}
}

void MainWindow::on_actionRedo_triggered()
{
	ImageWidget* img = getImageWidget();

	if (img) {
		ui->statusbar->showMessage("Redo", 2000);
		img->Redo();
	}
}

void MainWindow::on_actionUndoHistory_triggered()
{
	ImageWidget* img = getImageWidget();

	if (img) {
		ui->statusbar->showMessage("Undo History", 2000);
		img->UndoHistory();
	}
}

void MainWindow::on_actionResetImage_triggered()
{
	ImageWidget* img = getImageWidget();

	if (img) {
		ui->statusbar->showMessage("Reset Image", 2000);
		img->ResetImage();
	}
}

void MainWindow::on_btnPencil_clicked()
{
	mOperation = mOperations["Pencil"];
	emit Operation(mOperation, GetArgs());
}

void MainWindow::on_btnBrush_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnEraser_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnMagicWand_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnMagnifier_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnFloodFill_clicked()
{
	mOperation = mOperations["FloodFill"];
	emit Operation(mOperation, GetArgs());
}

void MainWindow::on_btnCrop_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnGeometry_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnText_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnSprayCan_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnAirbrush_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnEyedropper_clicked()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_btnPalette_clicked()
{
	QColor swap = ui->ColorPickerFront->getColor();
	ui->ColorPickerFront->setColor(ui->ColorPickerBack->getColor());
	ui->ColorPickerBack->setColor(swap);
	emit Operation(mOperation, GetArgs());
}

void MainWindow::on_actionBrushSize_triggered()
{
	mSizeDialog->setModal(true);
	mSizeDialog->exec();
	ui->statusbar->showMessage("Brush Size", 2000);
}

void MainWindow::on_imagetab_currentChanged(int)
{
	ImageWidget* img = getImageWidget();

	if (img) {
		setWindowTitle(ExtractFileName(img->GetFileName()));
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

void MainWindow::on_actionBlur_triggered()
{
	emit Operation(mOperations["Blur"], QHash<QString,QString>(), true);
}

void MainWindow::on_actionGaussianBlur_triggered()
{
	emit Operation(mOperations["GaussianBlur"], QHash<QString,QString>(), true);
}

void MainWindow::on_actionMedianBlur_triggered()
{
	emit Operation(mOperations["MedianBlur"], QHash<QString,QString>(), true);
}

void MainWindow::on_actionBilateralFilter_triggered()
{
	emit Operation(mOperations["BilateralFilter"], QHash<QString,QString>(), true);
}

void MainWindow::on_actionEdge_triggered()
{
	emit Operation(mOperations["Outline"], QHash<QString,QString>(), true);
}

void MainWindow::on_actionCanny_triggered()
{
	emit Operation(mOperations["Canny"], QHash<QString,QString>(), true);
}

void MainWindow::on_actionSobel_triggered()
{
	emit Operation(mOperations["Sobel"], QHash<QString,QString>(), true);
}

void MainWindow::on_actionDilation_triggered()
{
	emit Operation(mOperations["Dilation"], QHash<QString,QString>(), true);
}

void MainWindow::on_actionErosion_triggered()
{
	emit Operation(mOperations["Erosion"], QHash<QString,QString>(), true);
}

void MainWindow::on_actionCartoon_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionOilify_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionGrayscale_triggered()
{
}

void MainWindow::on_actionColorize_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionSaturation_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionBrightness_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionContrast_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionDisaturate_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionBalance_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionHistogram_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionInvertColor_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionZoom_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionEyedropper_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionText_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionAll_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionNone_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionInvertSelect_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionByColor_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionMagicWand_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionGrowth_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionShrink_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionCopy_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionPaste_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionCut_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}

void MainWindow::on_actionHelp_triggered()
{
	QMessageBox::information(this, "Information", "Action is not yet implemented.");
}
