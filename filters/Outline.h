// Outline.h

#ifndef OUTLINE_H
#define OUTLINE_H

#include "../IOperation.h"

class Outline : public IOperation
{
public:
	Outline() { }
	virtual ~Outline() throw() { }
	//! keine Funktion
	virtual void Initialize();
	//! Zeichnet Aussenlinien (Algorithmus muss noch geteset werden)
	/*!
	 * \b Argumente:
	 * - KernelSize: Gibt die Größe der Kernelmatrix an.
	 *	Dieser Wert bestimmt wieviele Pixel aus der Nachbarschaft des zentralen Pixel gemessen werden. Werte müssen >= 0 sein.
	 * - Shape: Dieser Wert entscheidet die Anordnung des Strukturelements. Folgende Werte werden als String definiert:
	 *	-- Rect: Das Strukturelement hat eine Rechtecksanordnung
	 *	-- Ellipse: Das Strukturelement hat eine elliptische Anordnung
	 *	-- Cross: Das Strukturelement hat eine Kreuzanordnung
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString>& args, int &shape, int &size);
};

#endif // OUTLINE_H
