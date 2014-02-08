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
