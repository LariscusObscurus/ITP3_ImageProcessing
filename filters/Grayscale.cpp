// Grayscale.cpp

#include "Grayscale.h"
#include "../Exception.h"
#include "../Conversion.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void Grayscale::Initialize() { }

void Grayscale::Draw(QImage &image, const QMap<QString, QString> &args)
{
	cv::Mat mat = QimageToMat(image);
	cv::cvtColor(mat.clone(), mat, CV_BGR2GRAY);
	image = MatToQimage(mat);
}

void Grayscale::Finalize() { }
