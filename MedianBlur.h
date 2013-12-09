// MedianBlur.h

#ifndef MEDIANBLUR_H
#define MEDIANBLUR_H

#include "IOperation.h"

class MedianBlur : public IOperation
{
public:
	MedianBlur() = default;
	virtual ~MedianBlur() throw() = default;
	//! keine funktion
	virtual void Initialize();
	//! zeichnet "median blur"
	/*!
	 * \b Exceptions:
	 * - FormatException
	 * - ArgumentException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
};

#endif // MEDIANBLUR_H
