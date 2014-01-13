#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "sizedialogue.h"

namespace Ui {
class MainWindow;
}

class ImageWidget;
class Exception;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_action_ffnen_triggered();

	void on_actionBeenden_triggered();

	void on_action_ber_triggered();

	void on_actionSpeichern_unter_triggered();

	void on_actionR_ckg_ngig_triggered();

	void on_actionZur_cksetzen_triggered();

	void on_btnBrush_clicked();

	void on_actionPinsel_gr_e_triggered();

	void on_btnTest_clicked();

	void on_actionBlur_triggered();

	void on_actionGaussian_Blur_triggered();

	void on_actionMedian_Blur_triggered();

	void on_actionBilateral_Filter_triggered();

	void on_actionSobel_triggered();

	void on_actionEdge_triggered();

	void on_actionCanny_triggered();

	void on_actionDilation_triggered();

	void on_actionErotion_triggered();

	void on_imagetab_tabCloseRequested(int index);

	void on_actionSpeichern_triggered();

	void on_imagetab_currentChanged(int index);

private:
	Ui::MainWindow *ui;
	//Dialogs


	void createConnections();
	void showError(const Exception &e);
	ImageWidget* getImageWidget() const;
	QString extractFileName(QString fileName);
	SizeDialogue *m_dia;
};

#endif // MAINWINDOW_H
