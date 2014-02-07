/* © 2014 David Wolf
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

#include "SavePopupDialog.hpp"
#include "ui_SavePopupDialog.h"

SavePopupDialog::SavePopupDialog(QWidget *parent, const QString &fileName) :
	QDialog(parent),
	ui(new Ui::SavePopupDialog),
	mResult(Result::Cancel)
{
	ui->setupUi(this);
	ui->header->setText(QString("<html><head/><body><p><span style='font-size:10pt; font-weight:600;'>Save changes to \"%1\" before closing?</span></p></body></html>").arg(fileName));
	layout()->setSizeConstraint(QLayout::SetFixedSize);
}

SavePopupDialog::~SavePopupDialog()
{
	delete ui;
}

int SavePopupDialog::result()
{
	return static_cast<int>(mResult);
}

void SavePopupDialog::on_btnClose_clicked()
{
	mResult = Result::Close;
	close();
}

void SavePopupDialog::on_btnCancel_clicked()
{
	mResult = Result::Cancel;
	close();
}

void SavePopupDialog::on_btnSave_clicked()
{
	mResult = Result::Save;
	close();
}
