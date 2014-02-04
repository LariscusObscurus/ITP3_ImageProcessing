// Grayscale.cpp

#include "Grayscale.hpp"
#include "../Exception.hpp"
#include "../Conversion.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMap>
#include <QImage>

void Grayscale::Draw(QImage &image, const QMap<QString, QString> &args)
{
	cv::Mat mat = QimageToMat(image);
	cv::cvtColor(mat.clone(), mat, CV_BGR2GRAY);
	image = MatToQimage(mat);
}

QString Grayscale::GetName() const
{
	return "Grayscale";
}
