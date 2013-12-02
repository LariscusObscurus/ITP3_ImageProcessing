// TestFilter.cpp

#include "TestFilter.h"
#include <QDebug>

void TestFilter::Initialize()
{
	qDebug() << "Initialize TestFilter";
}

void TestFilter::Draw(QImage &image, const QMap<QString, QString> &args)
{
	qDebug() << "Draw TestFilter:\n" << image.text() << "\n" << args.size();
}

void TestFilter::Finalize()
{
	qDebug() << "Finalize TestFilter";
}
