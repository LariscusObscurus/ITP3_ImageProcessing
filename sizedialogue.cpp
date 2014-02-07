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

#include "sizedialogue.hpp"
#include "ui_sizedialogue.h"

SizeDialogue::SizeDialogue(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SizeDialogue)
{
	ui->setupUi(this);
	ui->horizontalSlider->setRange(1,100);
	ui->spinBox->setRange(1,100);
	layout()->setSizeConstraint(QLayout::SetFixedSize);
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
