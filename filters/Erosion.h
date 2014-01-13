// Erosion.h

#ifndef EROSION_H
#define EROSION_H

#include "../IOperation.h"

class Erosion : public IOperation
{
public:
	Erosion() { }
	virtual ~Erosion() throw() { }
	//! keine funktion
	virtual void Initialize();
	//! zeichnet einen erosionseffekt
	/*!
	 * \b Argumente:
	 * - KernelSize: Gibt die Größe der Kernelmatrix an.
	 *	Dieser Wert bestimmt wieviele Pixel aus der Nachbarschaft des zentralen Pixel gemessen werden. Werte müssen >= 0 sein.
	 * - Shape: Dieser Wert entscheidet die Anordnung des Strukturelements. Folgende Werte werden als String definiert:
	 *	-- Rect: Das Strukturelement hat eine Rechtecksanordnung
	 *	-- Ellipse: Das Strukturelement hat eine elliptische Anordnung
	 *	-- Cross: Das Strukturelement hat eine Kreuzanordnung
	 *
	 * \b Exceptions
	 * - FormatException
	 * - ArgumentException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString>& args, int &shape, int &ksize);
};

#endif // EROSION_H
