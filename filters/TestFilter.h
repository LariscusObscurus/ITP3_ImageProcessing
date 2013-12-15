// TestFilter.h

#include "IOperation.h"

//! Dieser Filter hat keine direkte Bildoperation, er gibt lediglich Debugdaten aus.
class TestFilter : public IOperation
{
public:
	TestFilter() = default;
	virtual ~TestFilter() throw() = default;
	virtual void Initialize();
	virtual void Draw(QImage& image, const QMap<QString, QString>& args);
	virtual void Finalize();
};
