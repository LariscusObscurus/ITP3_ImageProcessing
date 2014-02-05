// Tool.hpp

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

#ifndef TOOL_HPP
#define TOOL_HPP

#include <QtGlobal>

enum class Tool {
	Pencil,
	Brush,
	Airbrush,
	SprayCan,
	FloodFill,
	Eraser,
	Crop,
	Stamp,
	Text,
	Geometry,
	MagicWand,
	Magnifiere,
	EyeDropper,
	Ink
};

static inline uint qHash(Tool key, uint = 0)
{
	return static_cast<uint>(key);
}

#endif // TOOL_HPP
