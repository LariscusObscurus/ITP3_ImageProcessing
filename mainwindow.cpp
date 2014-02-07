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
#include "SavePopupDialog.hpp"
#include "LiveFilterDialog.hpp"
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
#include "tool/AirBrush.hpp"
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
	CreateOperations();

	ConnectSignals();
}

MainWindow::~MainWindow()
{
	ClearOperations();
	delete mSizeDialog;
	delete ui;
}

void MainWindow::CreateOperations()
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
		mOperations["AirBrush"] = new AirBrush();
	} catch (const std::bad_alloc& e) {
		ClearOperations();
		QMessageBox::critical(0, "Memory Error", e.what());
	} catch (...) {
		ClearOperations();
		QMessageBox::critical(0, "Unknown Error", "Unknown error occured");
	}

	// Setzte Bleistift als erstes Werkzeug
	mOperation = mOperations["Pencil"];
}

void MainWindow::ConnectSignals()
{
	// Hauptfarbe
	connect(ui->ColorPickerFront, SIGNAL(activated()), ui->ColorPickerBack, SLOT(background()));
	connect(ui->ColorPickerFront, SIGNAL(colorChanged(QColor)), this, SLOT(ColorChanged(QColor)));
	// Sekundärfarbe
	connect(ui->ColorPickerBack, SIGNAL(activated()), ui->ColorPickerFront, SLOT(background()));
	connect(ui->ColorPickerBack, SIGNAL(colorChanged(QColor)), this, SLOT(ColorChanged(QColor)));

	// Werkzeuggröße
	connect(mSizeDialog, SIGNAL(sizeChanged(int)), this, SLOT(SizeChanged(int)));
}

void MainWindow::ClearOperations()
{
	for (auto& it : mOperations) {
		if (it) {
			delete it;
		}
	}
}

ImageWidget* MainWindow::GetImageWidget() const
{
	QWidget* widget = ui->imagetab->currentWidget();

	if (widget) {
		QScrollArea* area = qobject_cast<QScrollArea*>(widget);
		return qobject_cast<ImageWidget*>(area->widget());
	}

	return nullptr;
}

ImageWidget* MainWindow::GetImageWidget(int index) const
{
	QWidget* widget = ui->imagetab->widget(index);

	if (widget) {
		QScrollArea* area = qobject_cast<QScrollArea*>(widget);
		return qobject_cast<ImageWidget*>(area->widget());
	}

	return nullptr;
}

void MainWindow::OpenImage(const QString &fileName)
{
	QScrollArea* area = new QScrollArea();
	ImageWidget* img = new ImageWidget();

	// Nur les- und schreibbare Bildformate werden unterstützt
	if (img->OpenImage(fileName)) {
		QString shortFileName = ParseFileName(fileName);
		shortFileName = shortFileName.mid(0, shortFileName.lastIndexOf('.'));

		// Bild in die ScrollArea laden
		area->setWidget(img);
		area->setStyleSheet("background: qlineargradient(x1: 0, y0: 1, x2:1, y2: 0, stop: 0.96 #383838, stop: 0.99 #2e2e2e);");

		// neuen Tab hinzufügen
		int index = ui->imagetab->addTab(area, shortFileName);
		ui->imagetab->setTabToolTip(index, shortFileName);
		ui->imagetab->setCurrentIndex(index);

		// schließlich Signalhandler setzen
		connect(this, SIGNAL(Arguments(QHash<QString,QString>)), img, SLOT(Arguments(QHash<QString,QString>)));
		connect(this, SIGNAL(Operation(IOperation*,QHash<QString,QString>)), img, SLOT(Operation(IOperation*,QHash<QString,QString>)));
		connect(this, SIGNAL(Operation(IOperation*,QHash<QString,QString>,OperationType)), img, SLOT(Operation(IOperation*,QHash<QString,QString>,OperationType)));
		emit Operation(mOperation, GetArgs());
	}
}

QHash<QString, QString>& MainWindow::GetArgs()
{
	mArgs["Value"] = QString::number(1);
	mArgs["Size"] = QString::number(mSize);
	mArgs["Red"] = QString::number(mColor.red());
	mArgs["Green"] = QString::number(mColor.green());
	mArgs["Blue"] = QString::number(mColor.blue());
	mArgs["Alpha"] = QString::number(mColor.alpha());

	return mArgs;
}

void MainWindow::ApplyLiveOperation(IOperation *o)
{
	ImageWidget* img = GetImageWidget();

	if (img) {
		// Setze Bildfilter
		img->Operation(o, GetArgs(), OperationType::Live);
		// Erzeuge Live-Dialog
		LiveDialog(img);
		// Setze zurück auf vorherige Bildoperation
		img->Operation(mOperation, GetArgs());
	}
}

void MainWindow::ApplyImmediateOperation(IOperation *o)
{
	ImageWidget* img = GetImageWidget();

	if (img) {
		// Setze Bildfilter
		img->Operation(o, GetArgs(), OperationType::Immediately);
		// Setze zurück auf vorherige Bildoperation
		img->Operation(mOperation, GetArgs());
	}
}

bool MainWindow::CloseImage(ImageWidget *img)
{
	if (img && img->IsChanged()) {
		SavePopupDialog::Result result;
		SavePopupDialog dialog(this, ParseFileName(img->GetFileName()));
		dialog.setModal(true);
		dialog.exec();
		result = static_cast<SavePopupDialog::Result>(dialog.result());

		switch (result) {
		case SavePopupDialog::Result::Save:
			if (!img->SaveImage()) {
				on_actionSaveAs_triggered();
			}
			return true;
		case SavePopupDialog::Result::Close:
			return true;
		case SavePopupDialog::Result::Cancel:
			return false;
		}
	}

	return true;
}

void MainWindow::LiveDialog(ImageWidget* img)
{
	LiveFilterDialog dialog(mArgs, this);
	connect(&dialog, SIGNAL(Arguments(QHash<QString,QString>)), img, SLOT(Arguments(QHash<QString,QString>)));
	dialog.setModal(true);
	dialog.exec();

	if (dialog.result() == QMessageBox::Accepted) {
		img->ApplyLiveImage();
	} else {
		img->DiscardLiveImage();
	}
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

void MainWindow::SizeChanged(int s)
{
	mSize = s;
	emit Arguments(GetArgs());
}

void MainWindow::ColorChanged(const QColor &c)
{
	mColor = c;
	emit Arguments(GetArgs());
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
		ImageWidget* img = GetImageWidget(i);

		if (img) {
			// ist das Bild bereits geladen, dann ändere zu den entsprechenden Tab
			if (img && img->GetFileName() == fileName) {
				ui->imagetab->setCurrentIndex(i);
				return;
			}
		}
	}

	// Falls das Bild noch nicht geladen wurde, dann lade es jetzt
	OpenImage(fileName);
}

void MainWindow::on_actionClose_triggered()
{
	QWidget* widget = ui->imagetab->currentWidget();
	ImageWidget* img = GetImageWidget();

	if (CloseImage(img)) {
		ui->statusbar->showMessage("Closed Image",2000);
		ui->imagetab->removeTab(ui->imagetab->currentIndex());
		widget->deleteLater();
	} else {
		ui->statusbar->showMessage("Canceled Closing",2000);
	}
}

void MainWindow::on_actionCloseAll_triggered()
{
	int count = ui->imagetab->count();
	ui->imagetab->setCurrentIndex(0);

	for (int i = 0; i < count; i++) {
		QScrollArea* area = qobject_cast<QScrollArea*>(ui->imagetab->currentWidget());

		if (area) {
			ImageWidget* img = qobject_cast<ImageWidget*>(area->widget());

			if (CloseImage(img)) {
				ui->statusbar->showMessage("Closed Image",2000);
				ui->imagetab->removeTab(ui->imagetab->currentIndex());
				ui->imagetab->setCurrentIndex(0);
				area->deleteLater();
			} else {
				ui->statusbar->showMessage("Canceled Closing",2000);
			}
		}
	}
}

void MainWindow::on_actionQuit_triggered()
{
	on_actionCloseAll_triggered();
	ui->statusbar->showMessage("Quit Image Processing",2000);
	close();
}

void MainWindow::on_actionAbout_triggered()
{
	Ueberdialog about;
	about.setModal(true);
	about.exec();
}

void MainWindow::on_actionSave_triggered()
{
	ImageWidget* img = GetImageWidget();

	if (img) {
		img->SaveImage();
		ui->statusbar->showMessage(QString("Saved").arg(ParseFileName(img->GetFileName())), 2000);
	}
}

void MainWindow::on_actionSaveAs_triggered()
{

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
		ImageWidget* img = GetImageWidget();

		if (img) {
			img->SaveImage(fileName, ext.toLatin1());
			ui->statusbar->showMessage(QString("Saved as \"%1\"").arg(ParseFileName(fileName)), 2000);
		}
	}
}

void MainWindow::on_actionUndo_triggered()
{
	ImageWidget* img = GetImageWidget();

	if (img) {
		ui->statusbar->showMessage("Undo", 2000);
		img->Undo();
	}
}

void MainWindow::on_actionRedo_triggered()
{
	ImageWidget* img = GetImageWidget();

	if (img) {
		ui->statusbar->showMessage("Redo", 2000);
		img->Redo();
	}
}

void MainWindow::on_actionUndoHistory_triggered()
{
	ImageWidget* img = GetImageWidget();

	if (img) {
		ui->statusbar->showMessage("Undo History", 2000);
		img->UndoHistory();
	}
}

void MainWindow::on_actionResetImage_triggered()
{
	ImageWidget* img = GetImageWidget();

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
	mOperation = mOperations["Brush"];
	emit Operation(mOperation, GetArgs());
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
	mOperation = mOperations["AirBrush"];
	emit Operation(mOperation, GetArgs());
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
	ImageWidget* img = GetImageWidget();

	if (img) {
		setWindowTitle(ParseFileName(img->GetFileName()));
	} else {
		setWindowTitle("Image Processing");
	}
}

void MainWindow::on_imagetab_tabCloseRequested(int index)
{
	QWidget* widget = ui->imagetab->widget(index);

	if (widget) {
		QScrollArea* area = qobject_cast<QScrollArea*>(widget);
		ImageWidget* img = qobject_cast<ImageWidget*>(area->widget());

		if (CloseImage(img)) {
			widget->deleteLater();
		}
	}
}

void MainWindow::on_actionBlur_triggered()
{
	ApplyLiveOperation(mOperations["Blur"]);
}

void MainWindow::on_actionGaussianBlur_triggered()
{
	ApplyLiveOperation(mOperations["GaussianBlur"]);
}

void MainWindow::on_actionMedianBlur_triggered()
{
	ApplyLiveOperation(mOperations["MedianBlur"]);
}

void MainWindow::on_actionBilateralFilter_triggered()
{
	ApplyLiveOperation(mOperations["BilateralFilter"]);
}

void MainWindow::on_actionEdge_triggered()
{
	ApplyLiveOperation(mOperations["Outline"]);
}

void MainWindow::on_actionCanny_triggered()
{
	ApplyLiveOperation(mOperations["Canny"]);
}

void MainWindow::on_actionSobel_triggered()
{
	ApplyLiveOperation(mOperations["Sobel"]);
}

void MainWindow::on_actionDilation_triggered()
{
	ApplyLiveOperation(mOperations["Dilation"]);
}

void MainWindow::on_actionErosion_triggered()
{
	ApplyLiveOperation(mOperations["Erosion"]);
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
	ApplyImmediateOperation(mOperations["Grayscale"]);
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
