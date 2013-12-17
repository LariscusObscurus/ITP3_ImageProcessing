// ConvexHull.h

#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include "IOperation.h"

class ConvexHull : public IOperation
{
public:
	//! Default constructor
	ConvexHull() = default;
	//! Default destructor
	virtual ~ConvexHull() throw() = default;
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

#endif // CONVEXHULL_H
