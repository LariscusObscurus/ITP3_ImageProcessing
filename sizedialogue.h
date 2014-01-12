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
