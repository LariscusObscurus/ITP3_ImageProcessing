// Sobel.cpp

/* © 2013 David Wolf
 *
 * This file is part of ImageProcessing.
 *
 * ImageProcessing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ImageProcessing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ImageProcessing.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Sobel.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include "Grayscale.hpp"
#include "GaussianBlur.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QHash>
#include <QImage>

QImage Sobel::Draw(const QImage &image, const QHash<QString, QString>& args)
{
	int ddepth = CV_16U;
	int ksize = 3;
	cv::Mat srcGray, grad, result;
	cv::Mat gradX, gradY;
	cv::Mat absGradX, absGradY;
	SetupOperation(image, args, 1);
	srcGray = QImageToMat(image);
	cv::Sobel(srcGray, gradX, ddepth, 1, 0, ksize);
	cv::convertScaleAbs( gradX, absGradX );
	cv::Sobel(srcGray, gradY, ddepth, 0, 1, ksize);
	cv::convertScaleAbs(gradY, absGradY);
	cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, grad);
	grad.convertTo(result, CV_8U);
	return MatToQImage(result);
}

void Sobel::SetupOperation(const QImage& image, QHash<QString, QString> args, int ksize)
{
	bool ok = false;
	GaussianBlur gauss;
	//Grayscale gray;

	if (args.find("KernelSize") == args.end()) {
		args["KernelSize"] = QString().setNum(ksize);
	} else {
		ksize = args["KernelSize"].toInt(&ok);

		if (!ok) {
			throw FormatException("couldn't convert \"KernelSize\" argument for gaussian blur");
		} else if (ksize < 0) {
			throw ArgumentException("\"KernelSize\" argument for gaussian blur must be positive");
		}
	}
	gauss.Draw(image, args);
	//gray.Draw(image, args);
}

QString Sobel::GetName() const
{
	return "Sobel";
}
