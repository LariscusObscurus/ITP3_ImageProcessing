// IOperation.h

#ifndef IOPERATION_H
#define IOPERATION_H

// Forward-Deklarationen
class QMap;
class QImage;
class QString;

//! Schnittstelle für Bildoperationen
class IOperation
{
public:
	//! Initialisiert die Bildoperation.
	virtual void Initialize() = 0;
	//! Führt die Bildoperation aus
	/*!
	 * Zeichnet die Bilddaten anhander der Operation um.
	 *
	 * \param image Das Bild das bearbeitet werden soll
	 * \param args Die Argumente für die Bildbearbeitung
	 */
	virtual void Draw(QImage& image, const QMap<QString, QString>& args) = 0;
	//! Beendet die Bildoperation, für eine neue Verwendung muss wieder IOperation::Initialize aufgerufen werden.
	virtual void Finalize() = 0;
};

#endif // IOPERATION_H
