// TestFilter.hpp

#include "../IOperation.hpp"

//! Dieser Filter hat keine direkte Bildoperation, er gibt lediglich Debugdaten aus.
class TestFilter : public IOperation
{
public:
	TestFilter() { }
	virtual ~TestFilter() throw() { }
	virtual void Draw(QImage& image, const QMap<QString, QString>& args);
	virtual QString GetName() const;
};
