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
