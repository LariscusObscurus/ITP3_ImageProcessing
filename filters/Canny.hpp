// Canny.hpp

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

#ifndef CANNY_H
#define CANNY_H

#include "../IOperation.hpp"

class Canny : public virtual IOperation
{
public:
	//! Default constructor
	Canny() { }
	//! Default destructor
	virtual ~Canny() throw() { }
	//!
	/*!
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual QString GetName() const;
private:
	void Arguments(const QMap<QString, QString>& args, int& ksize, int &threshold);
};

#endif // CANNY_H
