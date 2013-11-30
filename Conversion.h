// Conversion.h

/////////////////////////////////////////////////////////////////////////////////////////
///
/// Für die Verwendung dieses Headers ist libopencv_core und libopencv_imgproc notwendig.
///
/// Für Linux reicht das installieren der nötigen Packages, da Bibliotheken bereits in
/// der Bildbearbeitung.pro eingebunden sind.
///
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONVERSION_H
#define CONVERSION_H

#include <QImage>
#include <opencv2/core/core.hpp>

//! Konvertiert cv::Mat zu QImage (Standardformat richtig?)
/*!
 * \param mat Matrixobjekt aus OpenCV
 * \param format Das zu verwendende Format
 * \return Ein valides QImage-objekt
 */
QImage MatToQimage(cv::Mat& mat, int format = CV_8UC3);
//! Konvertiert QImage zu cv::Mat
/*!
 * \param img Bildobjekt aus Qt
 * \param format Qt-Format das verwendet wird
 * \return Eine valide OpenCV-Matrix
 */
cv::Mat QimageToMat(QImage& img, QImage::Format format = QImage::Format_RGB888);

#endif // CONVERSION_H

