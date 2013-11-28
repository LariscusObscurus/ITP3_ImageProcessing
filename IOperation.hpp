// IOperation.hpp

#ifndef IOPERATION_HPP
#define IOPERATION_HPP

#include <QMap>
#include <QImage>
#include <QString>

class IOperation
{
public:
	virtual void Initialize() = 0;
	virtual void Draw(QImage& image, const QMap<QString, QString>& args) = 0;
	virtual void Finalize() = 0;
};

#endif

