// Dilation.h

#ifndef DILATION_H
#define DILATION_H

#include "IOperation.h"

class Dilation : public IOperation
{
public:
	Dilation() = default;
	virtual ~Dilation() throw() = default;
	//! keine funktion
	virtual void Initialize();
	//! zeichnet einen dilationseffekt
	/*!
	 * \b Exceptions
	 * - FormatException
	 * - ArgumentException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString>& args, int &shape, int &ksize);
};

#endif // DILATION_H
