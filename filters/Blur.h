// Blur.h

#ifndef BLUR_H
#define BLUR_H

#include "../IOperation.h"

class Blur : public IOperation
{
public:
	//! Default constructor
	Blur() { }
	//! Default destructor
	virtual ~Blur() throw() { }
	//! keine funktion
	virtual void Initialize();
	//! zeichnet "homogeneous blur"
	/*!
	 * \b Argumente:
	 * - KernelSize: Gibt die Größe der Kernelmatrix an.
	 *	Dieser Wert bestimmt wieviele Pixel aus der Nachbarschaft des zentralen Pixel gemessen werden. Werte müssen >= 0 sein.
	 * \b Exceptions:
	 * - FormatException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
};

#endif // BLUR_H
