// TestFilter.cpp

#include "TestFilter.hpp"
#include "../Exception.hpp"
#include <QDebug>
#include <QMap>
#include <QImage>

void TestFilter::Draw(QImage &image, const QMap<QString, QString> &args)
{
	qDebug() << "Draw TestFilter";
	throw Exception("Test Exception");
}

QString TestFilter::GetName() const
{
	return "Test Filter";
}
