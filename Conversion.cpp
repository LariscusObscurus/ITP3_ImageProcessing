// Conversion.cpp

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

#include "Conversion.hpp"
#include "Exception.hpp"

QImage::Format ConvertCvFormat(int format)
{
	switch (format) {
	case CV_8UC4:
		return QImage::Format_ARGB32;
	case CV_8UC3:
		return QImage::Format_RGB888;
	case CV_8UC1:
		return QImage::Format_Indexed8;
	default:
		return QImage::Format_Invalid;
	}
}

QImage ConvertQ4(const cv::Mat& argb)
{
	return QImage(argb.data, argb.cols, argb.rows, argb.step, QImage::Format_ARGB32);
}

QImage ConvertQ3(const cv::Mat& bgr)
{
	return QImage(bgr.data, bgr.cols, bgr.rows, bgr.step, QImage::Format_RGB888).rgbSwapped();
}

QImage ConvertQ1(const cv::Mat& gray)
{
	static QVector<QRgb>  sColorTable;

	if (sColorTable.isEmpty()) {
		for (int i = 0; i < 256; i++) {
			sColorTable.push_back(qRgb(i, i, i));
		}
	}

	QImage img(gray.data, gray.cols, gray.rows, gray.step, QImage::Format_Indexed8);
	img.setColorTable(sColorTable);
	return img;
}

QImage MatToQImage(const cv::Mat& mat)
{
	QImage::Format format = ConvertCvFormat(mat.type());

	switch (format) {
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
		return ConvertQ4(mat);
	case QImage::Format_RGB888:
		return ConvertQ3(mat);
	case QImage::Format_Indexed8:
		return ConvertQ1(mat);
	default:
		throw FormatException("can't convert this pixel format");
	}
}

int ConvertQformat(QImage::Format format)
{
	switch (format) {
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
		return CV_8UC4;
	case QImage::Format_RGB888:
		return CV_8UC3;
	case QImage::Format_Indexed8:
		return CV_8UC1;
	default:
		return 0;
	}
}

cv::Mat ConvertMat4(const QImage& argb) // argb.format() == Format_ARGB32 || argb.format() == Format_RGB32
{
	return cv::Mat(argb.height(), argb.width(), CV_8UC4, const_cast<uchar*>(argb.bits()), argb.bytesPerLine());
}

cv::Mat ConvertMat3(const QImage& rgb) // rgb.format() == Format_RGB888
{
	QImage bgr = rgb.rgbSwapped();
	return cv::Mat(bgr.height(), bgr.width(), CV_8UC3, const_cast<uchar*>(bgr.bits()), bgr.bytesPerLine()).clone();
}

cv::Mat ConvertMat1(const QImage& gray) // gray.format() == Format_Indexed8
{
	return cv::Mat(gray.height(), gray.width(), CV_8UC1, const_cast<uchar*>(gray.bits()), gray.bytesPerLine());
}

cv::Mat QImageToMat(const QImage& img)
{
	int format = ConvertQformat(img.format());

	switch (format) {
	case CV_8UC4:
		return ConvertMat4(img);
	case CV_8UC3:
		return ConvertMat3(img);
	case CV_8UC1:
		return ConvertMat1(img);
	default:
		throw FormatException("can't convert this pixel format");
	}
}

cv::Mat QImageRgb32ToMat24(const QImage &img)
{
	if (img.format() == QImage::Format_ARGB32 || img.format() == QImage::Format_RGB32) {
		return QImageToMat(img.convertToFormat(QImage::Format_RGB888));
	}
	return QImageToMat(img);
}
