// BilateralFilter.cpp

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

#include "BilateralFilter.hpp"
#include "../Conversion.hpp"
#include "../Exception.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QHash>
#include <QImage>
#include <QDebug>

QImage BilateralFilter::Draw(const QImage &image, const QHash<QString, QString>& args)
{
	int d = 9;
	double sigmaColor = 150;
	double sigmaSpace = 150;
	cv::Mat mat = QImageRgb32ToMat24(image);

	Arguments(args, d, sigmaColor, sigmaSpace);

	cv::bilateralFilter(mat.clone(), mat, d, sigmaColor, sigmaSpace);
	return MatToQImage(mat);
}

void BilateralFilter::Arguments(const QHash<QString, QString> &args, int &d, double &sigmaColor, double &sigmaSpace)
{
	bool ok = false;
	QHash<QString, QString>::const_iterator it;

	if ((it = args.find("Value")) != args.end()) {
		sigmaColor = sigmaSpace = static_cast<double>(it.value().toInt(&ok)) * 2.5;
		if (!ok) {
			throw FormatException("couldn't convert \"Value\" argument for bilateral filter");
		}
	}

	if ((it = args.find("Diameter")) != args.end()) {
		d = it.value().toDouble(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"SigmaColor\" argument for bilateral filter");
		}
	}

	if ((it = args.find("SigmaColor")) != args.end()) {
		sigmaColor = it.value().toDouble(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"SigmaSpace\" argument for bilateral filter");
		}
	}

	if ((it = args.find("SigmaSpace")) != args.end()) {
		sigmaSpace = it.value().toDouble(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"SigmaSpace\" argument for bilateral filter");
		}
	}
}

QString BilateralFilter::GetName() const
{
	return "BilateralFilter";
}
