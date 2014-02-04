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

#include "InputManager.hpp"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

InputManager::InputManager()
{
}

void InputManager::KeyPressEvent(QKeyEvent *e)
{
	mKeyMap[e->key()] = true;
}

void InputManager::KeyReleaseEvent(QKeyEvent *e)
{
	mKeyMap[e->key()] = false;
}

bool InputManager::IsKeyPressed(int key) const
{
	return mKeyMap[key];
}

void InputManager::MousePressEvent(QMouseEvent *e)
{
	mMousePosition = e->pos();
	mButtonMap[e->button()] = true;
}

void InputManager::MouseReleaseEvent(QMouseEvent *e)
{
	mMousePosition = e->pos();
	mButtonMap[e->button()] = false;
}

void InputManager::MouseMoveEvent(QMouseEvent *e)
{
	mMousePosition = e->pos();
}

void InputManager::MouseDoubleClickEvent(QMouseEvent *e)
{
	mMousePosition = e->pos();
}

void InputManager::MouseWheelEvent(QWheelEvent *e)
{
	mMousePosition = e->pos();
	mWheelState = e->angleDelta();
}

bool InputManager::IsButtonPressed(int b) const
{
	return mButtonMap[b];
}

QPoint InputManager::GetMouseWheel() const
{
	return mWheelState;
}

QPoint InputManager::MousePosition() const
{
	return mMousePosition;
}

