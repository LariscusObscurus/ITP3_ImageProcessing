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

#ifndef KEYMANAGER_HPP
#define KEYMANAGER_HPP

#include <QHash>
#include <QPoint>

class QKeyEvent;
class QWheelEvent;
class QMouseEvent;

class InputManager
{
	QHash<int, bool> mKeyMap;
	QHash<int, bool> mButtonMap;
	QPoint mMousePosition;
	QPoint mWheelState;
public:
	InputManager();

	// Keyboard Eventhandler
	void KeyPressEvent(QKeyEvent*);
	void KeyReleaseEvent(QKeyEvent*);
	// Key abfrage
	bool IsKeyPressed(int) const;

	// Mouse Eventhandler
	void MousePressEvent(QMouseEvent*);
	void MouseReleaseEvent(QMouseEvent*);
	void MouseMoveEvent(QMouseEvent*);
	void MouseDoubleClickEvent(QMouseEvent*);
	void MouseWheelEvent(QWheelEvent*);
	// Button abfrage
	bool IsButtonPressed(int) const;
	// Mouse-Rad abfrage
	QPoint GetMouseWheel() const;
	// Mouse Position
	QPoint MousePosition() const;
};

#endif // KEYMANAGER_HPP
