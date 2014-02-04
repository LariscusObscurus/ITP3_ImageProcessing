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

	void on_actionClose_triggered();

	void on_actionAbout_triggered();

	void on_actionSaveAs_triggered();

	void on_actionUndo_triggered();

	void on_actionUndoHistory_triggered();

	void on_actionResetImage_triggered();

	void on_btnPencil_clicked();

	void on_actionBrushSize_triggered();

	void on_imagetab_currentChanged(int index);

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
	void showError(const Exception &e);
	void applyFilter(IOperation *operation);
	ImageWidget* getImageWidget() const;

	Ui::MainWindow *ui;
	SizeDialogue *mDia;
	QHash<QString, IOperation*> mFilters;
};

#endif // MAINWINDOW_H
