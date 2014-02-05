// Outline.hpp

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

#ifndef OUTLINE_H
#define OUTLINE_H

#include "../IOperation.hpp"

class Outline : public IOperation
{
public:
	Outline() { }
	virtual ~Outline() throw() { }
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
	virtual QImage Draw(const QImage& img, const QHash<QString, QString>& args);
	virtual QString GetName() const;
private:
	void Arguments(const QHash<QString, QString>& args, int &shape, int &size);
};

#endif // OUTLINE_H
