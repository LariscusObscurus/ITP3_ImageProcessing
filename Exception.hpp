// Exception.hpp

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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class Exception {
	QString _message;
public:
	Exception() : _message("") { }
	Exception(const QString& message) : _message(message) { }
	virtual inline QString Message() const { return _message; }
};
class ArgumentException : public virtual Exception {
public:
	ArgumentException() : Exception() { }
	ArgumentException(const QString& message) : Exception(message) { }
};
class ArgumentOutOfRangeException : public virtual ArgumentException {
public:
	ArgumentOutOfRangeException() : ArgumentException() { }
	ArgumentOutOfRangeException(const QString& message) : ArgumentException(message) { }
};
class ArgumentNullException : public virtual ArgumentException {
public:
	ArgumentNullException() : ArgumentException() { }
	ArgumentNullException(const QString& message) : ArgumentException(message) { }
};
class NullPointerException : public virtual Exception {
public:
	NullPointerException() : Exception() { }
	NullPointerException(const QString& message) : Exception(message) { }
};
class IOException : public virtual Exception {
public:
	IOException() : Exception() { }
	IOException(const QString& message) : Exception(message) { }
};
class FileNotFoundException : public virtual IOException {
public:
	FileNotFoundException() : IOException() { }
	FileNotFoundException(const QString& message) : IOException(message) { }
};
class FileLoadException : public virtual IOException {
public:
	FileLoadException() : IOException() { }
	FileLoadException(const QString& message) : IOException(message) { }
};
class FileSaveException : public virtual IOException {
public:
	FileSaveException() : IOException() { }
	FileSaveException(const QString& message) : IOException(message) { }
};
class PathToLongException : public virtual IOException {
public:
	PathToLongException() : IOException() { }
	PathToLongException(const QString& message) : IOException(message) { }
};
class DirectoryNotFoundException : public virtual IOException {
public:
	DirectoryNotFoundException() : IOException() { }
	DirectoryNotFoundException(const QString& message) : IOException(message) { }
};
class UnauthorizedAccessException : public virtual Exception {
public:
	UnauthorizedAccessException() : Exception() { }
	UnauthorizedAccessException(const QString& message) : Exception(message) { }
};
class OutOfMemoryException : public virtual Exception {
public:
	OutOfMemoryException() : Exception() { }
	OutOfMemoryException(const QString& message) : Exception(message) { }
};
class NotSupportedException : public virtual Exception {
public:
	NotSupportedException() : Exception() { }
	NotSupportedException(const QString& message) : Exception(message) { }
};
class NotImplementedException : public virtual Exception {
public:
	NotImplementedException() : Exception() { }
	NotImplementedException(const QString& message) : Exception(message) { }
};
class ArithmeticException : public virtual Exception {
public:
	ArithmeticException() : Exception() { }
	ArithmeticException(const QString& message) : Exception(message) { }
};
class DividedByZeroException : public virtual ArithmeticException {
public:
	DividedByZeroException() : ArithmeticException() { }
	DividedByZeroException(const QString& message) : ArithmeticException(message) { }
};
class NotFiniteNumberException : public virtual ArithmeticException {
public:
	NotFiniteNumberException() : ArithmeticException() { }
	NotFiniteNumberException(const QString& message) : ArithmeticException(message) { }
};
class OverflowException : public virtual ArithmeticException {
public:
	OverflowException() : ArithmeticException() { }
	OverflowException(const QString& message) : ArithmeticException(message) { }
};
class AccessViolationException : public virtual Exception {
public:
	AccessViolationException() : Exception () { }
	AccessViolationException(const QString& message) : Exception(message) { }
};
class FormatException : public virtual Exception {
public:
	FormatException() : Exception () { }
	FormatException(const QString& message) : Exception(message) { }
};

#endif

