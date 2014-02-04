// IOperation.hpp

/* © 2013 David Wolf
 *
 * This file is part of ImageProcessing.
 *
 * ImageProcessing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ImageProcessing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ImageProcessing.  If not, see <http://www.gnu.org/licenses/>.
 */

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
