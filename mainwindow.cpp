#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    ui->actionR_ckg_gngig->setShortcut(tr("CTRL+Z"));
    ui->actionWiederherstellen->setShortcut(tr("CTRL+Y"));
    ui->actionKopieren->setShortcut(tr("CTRL+C"));
    ui->actionEinf_gen->setShortcut(tr("CTRL+V"));
    /*Hilfe*/
    ui->actionHilfe->setShortcut(tr("CTRL+H"));
    ui->action_ber->setShortcut(tr("CTRL+A"));

    createConnections();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createConnections()
{
    connect(ui->actionBeenden, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::on_action_ffnen_triggered()
{
    ui->statusbar->showMessage("Datei Öffnen",2000);
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
