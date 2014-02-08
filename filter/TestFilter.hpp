// TestFilter.hpp

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

#include "../IOperation.hpp"

//! Dieser Filter hat keine direkte Bildoperation, er gibt lediglich Debugdaten aus.
class TestFilter : public IOperation
{
public:
	TestFilter() { }
	virtual ~TestFilter() throw() { }
	virtual QImage Draw(const QImage&, const QHash<QString, QString>&);
	virtual QString GetName() const;
};
