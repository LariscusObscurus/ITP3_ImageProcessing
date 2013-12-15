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
	 * \b Argumente:
	 * - KernelSize: Gibt die Größe der Kernelmatrix an.
	 *	Dieser Wert bestimmt wieviele Pixel aus der Nachbarschaft des zentralen Pixel gemessen werden. Werte müssen >= 0 sein.
	 *
	 * \b Exceptions:
	 * - FormatException
	 * - ArgumentException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
};

#endif // MEDIANBLUR_H
