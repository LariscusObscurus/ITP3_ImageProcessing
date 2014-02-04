// IOperation.hpp

#ifndef IOPERATION_H
#define IOPERATION_H

// classes
template <typename T, typename U>
class QMap;
class QImage;

// headers
#include <QString>

//! Schnittstelle für Bildoperationen
class IOperation
{
public:
	//! Default destructor
	virtual ~IOperation() throw() { }
	//! Initialisiert die Bildoperation. (falls Speicher angelegt werden muss)
	virtual void Initialize() { }
	//! Führt die Bildoperation aus
	/*!
	 * Zeichnet die Bilddaten anhande der Operation um.
	 *
	 * \param image Das Bild das bearbeitet werden soll
	 * \param args Die Argumente für die Bildbearbeitung
	 */
	virtual void Draw(QImage& image, const QMap<QString, QString>& args) = 0;
	//! Beendet die Bildoperation. (falls Speicher freigegeben werden muss)
	virtual void Dispose() { }
	//! Überprüft ob die Bildoperation freigegeben wurde
	virtual bool IsDisposed() const { return true; }
	//! Liest den Namen der Bildoperation
	virtual QString GetName() const = 0;
};

#endif // IOPERATION_H
