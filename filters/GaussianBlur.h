// GaussianBlur.h

#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "IOperation.h"

class GaussianBlur : public IOperation
{
public:
	GaussianBlur() = default;
	virtual ~GaussianBlur() throw() = default;
	//! keine funktion
	virtual void Initialize();
	//! zeichnet "gaussian blur"
	/*!
	 * \b Argumente:
	 * - KernelSize: Gibt die Größe der Kernelmatrix an.
	 *	Dieser Wert bestimmt wieviele Pixel aus der Nachbarschaft des zentralen Pixel gemessen werden. Werte müssen >= 0 sein.
	 * - Sigma: Stellt die Standardabweichung für die berechneten Werte dar.
	 *	Wert muss >= 0.82 sein. Für einen starken Effekt werden Werte >= 6 empfohlen.
	 *
	 * \b Exceptions:
	 * - FormatException
	 * - ArgumentException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString> &args, int& ksize, double& sigma);
};

#endif // GAUSSIANBLUR_H
