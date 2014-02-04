#ifndef UEBER_H
#define UEBER_H

#include <QDialog>

namespace Ui {
class Ueberdialog;
}

class Ueberdialog : public QDialog
{
	Q_OBJECT

public:
	explicit Ueberdialog(QWidget *parent = 0);
	~Ueberdialog();

private:
	Ui::Ueberdialog *ui;
};

#endif // UEBER_H
