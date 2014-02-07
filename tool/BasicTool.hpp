// BasicBrush.hpp

/* © 2014 David Wolf
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

#ifndef BASICTOOL_HPP
#define BASICTOOL_HPP

#include "../IOperation.hpp"
#include <QPoint>
#include <QColor>

namespace cv {
	template <typename T>
	class Scalar_;
	template <typename T>
	class Point_;
}

class BasicTool : public IOperation
{
public:
	virtual ~BasicTool() throw() { }
protected:
	virtual void Arguments(const QHash<QString, QString>& args, cv::Point_<int>&, cv::Point_<int>&, cv::Scalar_<double>&, int&);
	virtual void Arguments(const QHash<QString, QString> &args, QPoint&, QPoint&, QColor&, int&);
};

#endif
