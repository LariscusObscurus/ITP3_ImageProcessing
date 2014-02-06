// BilateralFilter.hpp

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

#ifndef BILATERALFILTER_H
#define BILATERALFILTER_H

#include "../IOperation.hpp"
namespace cv {
	class Mat;
}

class BilateralFilter : public IOperation
{
public:
	BilateralFilter() { }
	virtual ~BilateralFilter() throw() { }
	//! zeichnet "bilateral filter"
	/*!
	 * Folgende Argumente werden agenommen:
	 * \b Argumente:
	 * - Diameter: Stellt die Filtergröße dar. Werte die größer als 5 sind können eine sehr lange Berechnungszeit hervorrufen.
	 *	Empfohlener Wert ist 9.
	 * - SigmaColor: Gibt die Reichweite der verwendeten Pixel innerhalb des berechneten Pixels an.
	 *	Je größer, umso mehr Pixel werden verwendet. Werte kleiner 10 haben kaum sichtbare veränderungen.
	 *	Werte größer als 150 lassen das Bild wie einen Cartoon wirken.
	 * - SigmaSpace: Es gilt dasselbe wie bei SigmaColor.
	 *
	 * \b Exceptions:
	 * - FormatException
	 * - ArgumentException
	 */
	virtual QImage Draw(const QImage& img, const QHash<QString, QString>& args);
	virtual QString GetName() const;
private:
	void Arguments(const QHash<QString, QString> &args, int& d, double& sigmaColor, double& sigmaSpace);
};

#endif // BILATERALFILTER_H
