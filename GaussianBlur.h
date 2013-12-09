// GaussianBlur.h

#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "IOperation.h"

class GaussianBlur : public IOperation
{
public:
	GaussianBlur() = default;
	virtual ~GaussianBlur() throw() = default;
	virtual void Initialize();
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString> &args, int& ksize, double& sigma);
};

#endif // GAUSSIANBLUR_H
