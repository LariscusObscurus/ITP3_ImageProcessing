// BilateralFilter.h

#ifndef BILATERALFILTER_H
#define BILATERALFILTER_H

#include "../IOperation.h"
namespace cv {
	class Mat;
}

class BilateralFilter : public IOperation
{
public:
	BilateralFilter() { }
	virtual ~BilateralFilter() throw() { }
	//! keine funktion
	virtual void Initialize();
	//! zeichnet "bilateral filter"
	/*!
	 * Folgende Argumente werden agenommen:
	 * \b Argumente:
	 * - Diameter: Stellt die Filtergröße dar. Werte die größer als 5 sind können eine sehr lange Berechnungszeit hervorrufen.
	 *	Empfohlener Wert ist 9.
	 * - SigmaColor: Gibt die Reichweite der verwendeten Pixel innerhalb des berechneten Pixels an.
	 *	Je größer, umso mehr Pixel werden verwendet. Werte kleiner 10 haben kaum sichtbare veränderungen.
	 *	Werte größer als 150 lassen das Bild wie einen Cartoon wirken.
	 * - SigmaSpace: Es gilt dasselbe wie bei SigmaColor.
	 *
	 * \b Exceptions:
	 * - FormatException
	 * - ArgumentException
	 */
	virtual void Draw(QImage &image, const QMap<QString, QString> &args);
	//! keine funktion
	virtual void Finalize();
private:
	void Arguments(const QMap<QString, QString> &args, int& d, double& sigmaColor, double& sigmaSpace);
	cv::Mat QimageRgb32ToMat24(QImage& img);
};

#endif // BILATERALFILTER_H
