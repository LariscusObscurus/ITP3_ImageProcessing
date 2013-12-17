// Remapping.h

#ifndef REMAPPING_H
#define REMAPPING_H

#include "IOperation.h"

class Remapping : public IOperation
{
public:
	Remapping() = default;
	virtual ~Remapping() throw() = default;
	//! keine funktion
	virtual void Initialize();

	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString>& args);
};

#endif // REMAPPING_H
