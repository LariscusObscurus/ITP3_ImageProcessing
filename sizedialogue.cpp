#include "sizedialogue.h"
#include "ui_sizedialogue.h"

SizeDialogue::SizeDialogue(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SizeDialogue)
{
	ui->setupUi(this);
	ui->horizontalSlider->setRange(1,20);
	ui->spinBox->setRange(1,20);
	QObject::connect(ui->spinBox, SIGNAL(valueChanged(int)),ui->horizontalSlider, SLOT(setValue(int)));
	QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),ui->spinBox, SLOT(setValue(int)));
}

SizeDialogue::~SizeDialogue()
{
	delete ui;
}

void SizeDialogue::on_buttonBox_accepted()
{
    emit sizeChanged(ui->spinBox->value());
}
