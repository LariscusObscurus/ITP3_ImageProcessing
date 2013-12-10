// Grayscale.h

#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "IOperation.h"

class Grayscale : public IOperation
{
public:
	Grayscale() = default;
	virtual ~Grayscale() throw() = default;
	virtual void Initialize();
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual void Finalize();
};

#endif // GRAYSCALE_H
