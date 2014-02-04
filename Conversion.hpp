// Conversion.hpp

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

/////////////////////////////////////////////////////////////////////////////////////////
///
/// Für die Verwendung dieses Headers ist libopencv_core und libopencv_imgproc notwendig.
///
/// Für Linux reicht das Installieren der nötigen Packages, da die Bibliotheken bereits
/// in der Bildbearbeitung.pro eingebunden sind.
///
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONVERSION_H
#define CONVERSION_H

#include <QImage>
#include <opencv2/core/core.hpp>

//! Konvertiert cv::Mat zu QImage
/*!
 * \param mat Matrixobjekt aus OpenCV
 * \return Ein valides QImage-Objekt
 */
QImage MatToQimage(const cv::Mat& mat);
//! Konvertiert QImage zu cv::Mat
/*!
 * \param img Bildobjekt aus Qt
 * \return Eine valide OpenCV-Matrix
 */
cv::Mat QimageToMat(const QImage& img);


#endif // CONVERSION_H
