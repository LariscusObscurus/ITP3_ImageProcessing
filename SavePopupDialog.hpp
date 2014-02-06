#ifndef SAVEPOPUPDIALOG_HPP
#define SAVEPOPUPDIALOG_HPP

#include <QDialog>

namespace Ui {
class SavePopupDialog;
}

class SavePopupDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SavePopupDialog(QWidget *parent = 0, const QString& fileName = "");
	~SavePopupDialog();

	enum class Result {
		Save,
		Close,
		Cancel
	};

	virtual int result();

private slots:
	void on_btnClose_clicked();

	void on_btnCancel_clicked();

	void on_btnSave_clicked();

private:
	Ui::SavePopupDialog *ui;
	Result mResult;
};

#endif // SAVEPOPUPDIALOG_HPP
