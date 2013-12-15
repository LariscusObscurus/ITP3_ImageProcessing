// Conversion.h

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
 * \return Ein valides QImage-objekt
 */
QImage MatToQimage(cv::Mat& mat);
//! Konvertiert QImage zu cv::Mat
/*!
 * \param img Bildobjekt aus Qt
 * \return Eine valide OpenCV-Matrix
 */
cv::Mat QimageToMat(QImage& img);


#endif // CONVERSION_H

