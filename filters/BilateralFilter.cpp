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
	auto it = args.find("Diameter");

	if (it != args.end() && it.key() == "Diameter") {
		d = it.value().toInt(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"Diameter\" argument for bilateral filter");
		}
	}
	it = args.find("SigmaColor");

	if (it != args.end() && it.key() == "SigmaColor") {
		sigmaColor = it.value().toDouble(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"SigmaColor\" argument for bilateral filter");
		}
	}
	it = args.find("SigmaSpace");

	if (it != args.end() && it.key() == "SigmaSpace") {
		sigmaSpace = it.value().toDouble(&ok);
		if (!ok) {
			throw FormatException("couldn't convert \"SigmaSpace\" argument for bilateral filter");
		}
	}
}

QString BilateralFilter::GetName() const
{
	return "Bilateral Filter";
}
