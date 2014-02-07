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

#ifndef LIVEFILTERDIALOG_HPP
#define LIVEFILTERDIALOG_HPP

#include <QDialog>
#include <QString>
#include <QHash>

namespace Ui {
class LiveFilterDialog;
}

class LiveFilterDialog : public QDialog
{
	Q_OBJECT

public:
	explicit LiveFilterDialog(QHash<QString,QString>&, QWidget *parent = 0);
	~LiveFilterDialog();

signals:
	void Arguments(const QHash<QString,QString>&);

private slots:
	void ValueChanged(int);

private:
	Ui::LiveFilterDialog *ui;
	QHash<QString,QString>& mArgs;
};

#endif // LIVEFILTERDIALOG_HPP
