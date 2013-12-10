// Erosion.h

#ifndef EROSION_H
#define EROSION_H

#include "IOperation.h"

class Erosion : public IOperation
{
public:
	Erosion() = default;
	virtual ~Erosion() throw() = default;
	//! keine funktion
	virtual void Initialize();
	//! zeichnet einen erosionseffekt
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

#endif // EROSION_H
