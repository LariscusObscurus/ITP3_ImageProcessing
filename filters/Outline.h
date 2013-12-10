// Outline.h

#ifndef OUTLINE_H
#define OUTLINE_H

#include "IOperation.h"

class Outline : public IOperation
{
public:
	Outline() = default;
	virtual ~Outline() throw() = default;
	virtual void Initialize();
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString>& args, int &shape, int &size);
};

#endif // OUTLINE_H
