// Blur.h

#ifndef BLUR_H
#define BLUR_H

#include "IOperation.h"

class Blur : public IOperation
{
public:
	//! Default constructor
	Blur() = default;
	//! Default destructor
	virtual ~Blur() throw() = default;
	//! keine funktion
	virtual void Initialize();
	//! zeichnet "homogeneous blur"
	/*!
	 * \b Exceptions:
	 * - FormatException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
};

#endif // BLUR_H
