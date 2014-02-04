// Canny.hpp

#ifndef CANNY_H
#define CANNY_H

#include "../IOperation.hpp"

class Canny : public virtual IOperation
{
public:
	//! Default constructor
	Canny() { }
	//! Default destructor
	virtual ~Canny() throw() { }
	//!
	/*!
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual QString GetName() const;
private:
	void Arguments(const QMap<QString, QString>& args, int& ksize, int &threshold);
};

#endif // CANNY_H
