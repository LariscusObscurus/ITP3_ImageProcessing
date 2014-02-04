/* © 2013 Leonhardt Schwarz, Tom Schalbar, David Wolf
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QMap>
#include <QString>
#include <QAction>
#include "sizedialogue.hpp"

namespace Ui {
class MainWindow;
}

template <typename T, typename U>
class QHash;
class IOperation;
class ImageWidget;
class Exception;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionOpen_triggered();

	//void on_actionClose_triggered();

	void on_actionAbout_triggered();

	void on_actionSaveAs_triggered();

	void on_actionUndo_triggered();

	void on_actionUndoHistory_triggered();

	void on_actionResetImage_triggered();

	void on_btnPencil_clicked();

	void on_actionBrushSize_triggered();

	void on_imagetab_currentChanged(int);

	void on_imagetab_tabCloseRequested(int index);

	void on_actionSave_triggered();

	void on_actionRedo_triggered();

	void on_actionBlur_triggered();

	void on_actionGaussianBlur_triggered();

	void on_actionMedianBlur_triggered();

	void on_actionBilateralFilter_triggered();

	void on_actionEdge_triggered();

	void on_actionCanny_triggered();

	void on_actionSobel_triggered();

	void on_actionDilation_triggered();

	void on_actionErosion_triggered();

	void on_actionGrayscale_triggered();

private:
	void openImage(const QString& fileName);
	void showError(const Exception &e);
	void applyFilter(IOperation *operation);
	ImageWidget* getImageWidget() const;

	Ui::MainWindow *ui;
	SizeDialogue *mDia;
	QHash<QString, IOperation*> mFilters;
};

#endif // MAINWINDOW_H
