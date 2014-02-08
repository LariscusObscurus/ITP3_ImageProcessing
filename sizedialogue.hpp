/* © 2013 Leonhardt Schwarz
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

#ifndef SIZEDIALOGUE_H
#define SIZEDIALOGUE_H

#include <QDialog>

namespace Ui {
class SizeDialogue;
}

class SizeDialogue : public QDialog
{
	Q_OBJECT

public:
	explicit SizeDialogue(QWidget *parent = 0);
	~SizeDialogue();
signals:
	void sizeChanged(int size);

private slots:
	void on_buttonBox_accepted();

private:
	Ui::SizeDialogue *ui;
};

#endif // SIZEDIALOGUE_H
