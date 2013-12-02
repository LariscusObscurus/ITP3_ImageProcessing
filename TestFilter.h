// TestFilter.h

#include "IOperation.h"

class TestFilter : public IOperation
{
public:
	TestFilter() = default;
	virtual ~TestFilter() throw() = default;
	virtual void Initialize();
	virtual void Draw(QImage& image, const QMap<QString, QString>& args);
	virtual void Finalize();
};
