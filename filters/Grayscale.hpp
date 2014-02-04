// Grayscale.hpp

#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "../IOperation.hpp"

class Grayscale : public IOperation
{
public:
	Grayscale() { }
	virtual ~Grayscale() throw() { }
	//! Konvertiert die RGB-Werte des Bildes in 8-Bit Graufstufen
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual QString GetName() const;
};

#endif // GRAYSCALE_H
