// MedianBlur.h

#ifndef MEDIANBLUR_H
#define MEDIANBLUR_H

#include "IOperation.h"

class MedianBlur : public IOperation
{
public:
	MedianBlur() = default;
	virtual ~MedianBlur() throw() = default;
	virtual void Initialize();
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual void Finalize();
};

#endif // MEDIANBLUR_H
