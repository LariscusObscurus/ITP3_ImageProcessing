// Contrast.h

#ifndef CONTRAST_H
#define CONTRAST_H

#include "IOperation.h"

class Contrast : public IOperation
{
public:
	//! Default constructor
	Contrast() = default;
	//! Default destructor
	virtual ~Contrast() throw() = default;
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

#endif // CONTRAST_H
