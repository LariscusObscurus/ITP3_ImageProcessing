// BilateralFilter.h

#ifndef BILATERALFILTER_H
#define BILATERALFILTER_H

#include "IOperation.h"

class BilateralFilter : public IOperation
{
public:
	BilateralFilter() = default;
	virtual ~BilateralFilter() throw() = default;
	//! keine funktion
	virtual void Initialize();
	//! zeichnet "bilateral filter"
	/*!
	 * \b Exceptions:
	 * - FormatException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString> &args, int& d, double& sigmaColor, double& sigmaSpace);
};

#endif // BILATERALFILTER_H
