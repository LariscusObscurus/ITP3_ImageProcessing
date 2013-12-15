// Grayscale.h

#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "IOperation.h"

class Grayscale : public IOperation
{
public:
	Grayscale() = default;
	virtual ~Grayscale() throw() = default;
	//! keine Funktion
	virtual void Initialize();
	//! Konvertiert die RGB-Werte des Bildes in 8-Bit Graufstufen
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine Funktion
	virtual void Finalize();
};

#endif // GRAYSCALE_H
