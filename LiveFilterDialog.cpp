#include "LiveFilterDialog.hpp"
#include "ui_LiveFilterDialog.h"
#include <QHash>
#include <QDebug>

LiveFilterDialog::LiveFilterDialog(QHash<QString, QString> &args, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LiveFilterDialog),
	mArgs(args)
{
	ui->setupUi(this);
	ui->horizontalSlider->setRange(1,100);
	ui->spinBox->setRange(1,100);
	layout()->setSizeConstraint(QLayout::SetFixedSize);
	QObject::connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
	QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));
	QObject::connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(ValueChanged(int)));
}

LiveFilterDialog::~LiveFilterDialog()
{
	delete ui;
}

void LiveFilterDialog::ValueChanged(int val)
{
	mArgs["Value"] = QString::number(val);
	emit Arguments(mArgs);
}
