// EdgeDetection.h

#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include "IOperation.h"

class EdgeDetection : public IOperation
{
public:
	virtual void Initialize();
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual void Finalize();
private:
	void SetupOperation(QImage &image, QMap<QString, QString> args, int ksize);
};

#endif // EDGEDETECTION_H
