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
#include "OperationType.hpp"
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

signals:
	void Arguments(const QHash<QString,QString>&);
	void Operation(IOperation*,const QHash<QString,QString>&);
	void Operation(IOperation*,const QHash<QString,QString>&,OperationType);

private slots:
	void SizeChanged(int);
	void ColorChanged(const QColor&);

	void on_actionOpen_triggered();

	void on_actionClose_triggered();

	void on_actionAbout_triggered();

	void on_actionSaveAs_triggered();

	void on_actionUndo_triggered();

	void on_actionUndoHistory_triggered();

	void on_actionResetImage_triggered();

	void on_btnPencil_clicked();

	void on_btnBrush_clicked();

	void on_btnEraser_clicked();

	void on_btnMagicWand_clicked();

	void on_btnMagnifier_clicked();

	void on_btnFloodFill_clicked();

	void on_btnCrop_clicked();

	void on_btnGeometry_clicked();

	void on_btnText_clicked();

	void on_btnSprayCan_clicked();

	void on_btnAirbrush_clicked();

	void on_btnEyedropper_clicked();

	void on_btnPalette_clicked();

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

	void on_actionColorize_triggered();

	void on_actionSaturation_triggered();

	void on_actionBrightness_triggered();

	void on_actionContrast_triggered();

	void on_actionDisaturate_triggered();

	void on_actionBalance_triggered();

	void on_actionHistogram_triggered();

	void on_actionInvertColor_triggered();

	void on_actionEyedropper_triggered();

	void on_actionText_triggered();

	void on_actionAll_triggered();

	void on_actionNone_triggered();

	void on_actionInvertSelect_triggered();

	void on_actionByColor_triggered();

	void on_actionMagicWand_triggered();

	void on_actionGrowth_triggered();

	void on_actionShrink_triggered();

	void on_actionNew_triggered();

	void on_actionCopy_triggered();

	void on_actionPaste_triggered();

	void on_actionHelp_triggered();

	void on_actionCut_triggered();

	void on_actionCloseAll_triggered();

	void on_actionQuit_triggered();

	void on_actionCartoon_triggered();

	void on_actionOilify_triggered();

	void on_actionZoom_triggered();

protected:
	virtual void keyPressEvent(QKeyEvent*);
	virtual void keyReleasedEvent(QKeyEvent*);
	virtual void mousePressEvent(QMouseEvent*);
	virtual void mouseReleaseEvent(QMouseEvent*);
	virtual void mouseDoubleClickEvent(QMouseEvent*);
	virtual void mouseMoveEvent(QMouseEvent*);
	virtual void wheelEvent(QWheelEvent*);

private:
	void OpenImage(const QString& fileName);
	ImageWidget* GetImageWidget() const;
	ImageWidget* GetImageWidget(int) const;
	void CreateOperations();
	void ClearOperations();
	void ConnectSignals();
	QHash<QString,QString> GetArgs() const;
	void ApplySingleOperation(IOperation*, const QHash<QString, QString>&, OperationType);
	bool CloseImage(ImageWidget*);

	// Felder
	Ui::MainWindow *ui;
	SizeDialogue *mSizeDialog;
	QHash<QString, IOperation*> mOperations;
	int mSize;
	IOperation* mOperation;
	QColor mColor;
};

#endif // MAINWINDOW_H
