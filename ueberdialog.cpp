#include "ueberdialog.h"
#include "ui_ueberdialog.h"

Ueberdialog::Ueberdialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Ueberdialog)
{
	ui->setupUi(this);
}

Ueberdialog::~Ueberdialog()
{
	delete ui;
}
