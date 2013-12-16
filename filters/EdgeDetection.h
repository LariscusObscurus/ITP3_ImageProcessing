// EdgeDetection.h

#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include "IOperation.h"

class EdgeDetection : public IOperation
{
public:
	//! keine Funktion
	virtual void Initialize();
	//! Einfacher Algorithmus für Kantenfindung
	/*!
	 * Die Argumente in der QMap sind nicht für die Kantenfindung direkt bestimmt,
	 * sondern für die darunter liegende Blur-Operation.
	 *
	 * \b Argumente:
	 * - KernelSize: Gibt die Größe der Kernelmatrix an.
	 *	Dieser Wert bestimmt wieviele Pixel aus der Nachbarschaft des zentralen Pixel gemessen werden. Werte müssen >= 0 sein.
	 *
	 * \b Exceptions:
	 * - FormatException
	 * - ArgumentException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine Funktion
	virtual void Finalize();
private:
	void SetupOperation(QImage &image, QMap<QString, QString> args);
};

#endif // EDGEDETECTION_H
