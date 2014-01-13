// Canny.h

#ifndef CANNY_H
#define CANNY_H

#include "../IOperation.h"

class Canny : public virtual IOperation
{
public:
	//! Default constructor
	Canny() { }
	//! Default destructor
	virtual ~Canny() throw() { }
	//! keine funktion
	virtual void Initialize();
	//!
	/*!
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString>& args, int& ksize, int &threshold);
};

#endif // CANNY_H
