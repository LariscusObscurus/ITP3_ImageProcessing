#include <QtGui>
#include <QtCore>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ueberdialog.h"
#include "imagewidget.h"
#include "filters/BilateralFilter.h"
#include "filters/Blur.h"
#include "filters/Dilation.h"
#include "filters/Erosion.h"
#include "filters/GaussianBlur.h"
#include "filters/Grayscale.h"
#include "filters/MedianBlur.h"
#include "filters/Outline.h"
#include "filters/Sobel.h"
#include "filters/Canny.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_dia(new SizeDialogue)
{
	ui->setupUi(this);

	/*Shortcuts MenuBar*/
	/*Datei*/
	ui->actionBeenden->setShortcut(tr("CTRL+B"));
	ui->actionNeu->setShortcut(tr("CTRL+N"));
	ui->action_ffnen->setShortcut(tr("CTRL+O"));
	ui->actionSpeichern->setShortcut(tr("CTRL+S"));
	ui->actionDrucken->setShortcut(tr("CTRL+P"));
	ui->actionSpeichern_unter->setShortcut(tr("CTRL+SHIFT+S"));
	/*Bearbeiten*/
	ui->actionR_ckg_ngig->setShortcut(tr("CTRL+Z"));
	ui->actionWiederherstellen->setShortcut(tr("CTRL+Y"));
	ui->actionZur_cksetzen->setShortcut(tr("CTRL+SHIFT+Z"));
	ui->actionKopieren->setShortcut(tr("CTRL+C"));
	ui->actionEinf_gen->setShortcut(tr("CTRL+V"));
	/*Hilfe*/
	ui->actionHilfe->setShortcut(tr("CTRL+H"));
	ui->action_ber->setShortcut(tr("CTRL+A"));

	createConnections();

}

MainWindow::~MainWindow()
{
	delete m_dia;
	delete ui;
}

void MainWindow::createConnections()
{
	connect(ui->actionBeenden, SIGNAL(triggered()), this, SLOT(close()));
	//connect(ui->ColorPicker, SIGNAL(colorChanged(QColor)),ui->imageWidget,SLOT(setPenColor(QColor)));
	//connect(m_dia,SIGNAL(sizeChanged(int)),ui->imageWidget, SLOT(setPenWidth(int)));
}

void MainWindow::on_action_ffnen_triggered()
{
	ui->statusbar->showMessage("Datei Öffnen",2000);
	QString fileName = QFileDialog::getOpenFileName(this, tr("Bilddatei öffnen"), QDir::homePath());
	if(!fileName.isEmpty()) {
		//ui->imageWidget->openImage(fileName);
		ImageWidget* image = new ImageWidget();

		if (image->openImage(fileName)) {
			ui->imagetab->addTab(image, extractFileName(fileName));
		}
	}
}

QString MainWindow::extractFileName(QString fileName)
{
	int index = -1;
	fileName.replace('\\', '/');
	index = fileName.lastIndexOf('/');

	if (index == -1) {
		return fileName;
	} else {
		QString tmp = fileName.mid(index+1);
		return (tmp.length() > 16 ? QString("%1...").arg(fileName.mid(index+1, 13)) : tmp);
	}
}

void MainWindow::on_actionBeenden_triggered()
{
	ui->statusbar->showMessage("Programm Beenden",2000);
}

void MainWindow::on_action_ber_triggered()
{
	Ueberdialog about;
	about.setModal(true);
	about.exec();
}

void MainWindow::on_actionSpeichern_triggered()
{
	// do nothing
}

void MainWindow::on_actionSpeichern_unter_triggered()
{
	ui->statusbar->showMessage("Speichern unter", 2000);
	QString fileName = QFileDialog::getSaveFileName(this, tr("Bilddatei abspeichern"),
		QDir::homePath(), tr("png(*.png);;jpg(*.jpg *jpeg)"));
	QStringList splitedFile = fileName.split(".");
	QString ext;
	if(!splitedFile.isEmpty()) {
		ext = splitedFile.takeLast();
	}
	if(!fileName.isEmpty()) {
		ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
		img->saveImage(fileName, ext.toLatin1());
	}
}

void MainWindow::on_actionR_ckg_ngig_triggered()
{
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	ui->statusbar->showMessage("Rückgängig", 2000);
	img->undo();
}

void MainWindow::on_actionZur_cksetzen_triggered()
{
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	ui->statusbar->showMessage("Zurücksetzen", 2000);
	img->resetImage();
}

void MainWindow::on_btnBrush_clicked()
{
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->setPenStyle(ImageWidget::dots);
}

void MainWindow::on_actionPinsel_gr_e_triggered()
{
	m_dia->setModal(true);
	m_dia->exec();
}

void MainWindow::on_btnTest_clicked()
{
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->setPenStyle(ImageWidget::solid);
}

void MainWindow::on_actionBlur_triggered()
{
	Blur f;
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->applyFilter(f);
}

void MainWindow::on_actionGaussian_Blur_triggered()
{
	GaussianBlur f;
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->applyFilter(f);
}

void MainWindow::on_actionMedian_Blur_triggered()
{
	MedianBlur f;
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->applyFilter(f);
}

void MainWindow::on_actionBilateral_Filter_triggered()
{
	BilateralFilter f;
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->applyFilter(f);
}

void MainWindow::on_actionSobel_triggered()
{
	Sobel f;
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->applyFilter(f);
}

void MainWindow::on_actionEdge_triggered()
{
	Outline f;
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->applyFilter(f);
}

void MainWindow::on_actionCanny_triggered()
{
	Canny f;
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->applyFilter(f);
}

void MainWindow::on_actionDilation_triggered()
{
	Dilation f;
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->applyFilter(f);
}

void MainWindow::on_actionErotion_triggered()
{
	Erosion f;
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	img->applyFilter(f);
}

void MainWindow::on_imagetab_tabCloseRequested(int index)
{
	delete (ui->imagetab->currentWidget());
	//ui->imagetab->removeTab(index);
}

void MainWindow::on_imagetab_currentChanged(int index)
{
	ImageWidget* img = dynamic_cast<ImageWidget*>(ui->imagetab->currentWidget());
	connect(ui->ColorPicker, SIGNAL(colorChanged(QColor)), img, SLOT(setPenColor(QColor)));
	connect(m_dia, SIGNAL(sizeChanged(int)), img, SLOT(setPenWidth(int)));
}
