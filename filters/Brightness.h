// Brightness.h

#ifndef BRIGHNTESS_H
#define BRIGHNTESS_H

#include "IOperation.h"

class Brightness : public IOperation
{
public:
	//! Default constructor
	Brightness() = default;
	//! Default destructor
	virtual ~Brightness() throw() = default;
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

#endif // BRIGHNTESS_H
