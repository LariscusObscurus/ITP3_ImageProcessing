// Sobel.hpp

#ifndef SOBEL_H
#define SOBEL_H

#include "../IOperation.hpp"

class Sobel : public IOperation
{
public:
	Sobel() { }
	virtual ~Sobel() throw() { }
	//!
	/*!
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual QString GetName() const;
private:
	void SetupOperation(QImage &image, QMap<QString, QString> args, int ksize);
};

#endif // EDGEDETECTION_H
