// GaussianBlur.hpp

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

#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "../IOperation.hpp"

class GaussianBlur : public IOperation
{
public:
	GaussianBlur() { }
	virtual ~GaussianBlur() throw() { }
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
	virtual QString GetName() const;
private:
	void Arguments(const QMap<QString, QString> &args, int& ksize, double& sigma);
};

#endif // GAUSSIANBLUR_H
