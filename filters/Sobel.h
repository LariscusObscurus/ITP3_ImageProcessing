// Sobel.h

#ifndef SOBEL_H
#define SOBEL_H

#include "IOperation.h"

class Sobel : public IOperation
{
public:
	virtual void Initialize();
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual void Finalize();
private:
	void SetupOperation(QImage &image, QMap<QString, QString> args, int ksize);
};

#endif // EDGEDETECTION_H
