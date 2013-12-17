// Contour.h

#ifndef CONTOUR_H
#define CONTOUR_H

#include "IOperation.h"

class Contour : public IOperation
{
public:
	//! Default constructor
	Contour() = default;
	//! Default destructor
	virtual ~Contour() throw() = default;
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

#endif // CONTOUR_H
