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
