/*********************************************************\
 *  File: ImageTools.cpp                                 *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Math.h>
#include <PLGraphics/Color/Color3.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include "PLVolume/TransferFunctionControl/ImageTools.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
namespace PLVolume {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ImageTools::ImageTools(ImageBuffer &cImageBuffer) :
	m_pImageBuffer(&cImageBuffer),
	m_nWidth(cImageBuffer.GetSize().x),
	m_nHeight(cImageBuffer.GetSize().y),
	m_pImageData(cImageBuffer.GetData()),
	m_nBytesPerPixel(cImageBuffer.GetBytesPerPixel()),
	m_nRed(0),
	m_nGreen(0),
	m_nBlue(0)
{
}

/**
*  @brief
*    Copy constructor
*/
ImageTools::ImageTools(const ImageTools &cSource) :
	m_pImageBuffer(cSource.m_pImageBuffer),
	m_nWidth(cSource.m_nWidth),
	m_nHeight(cSource.m_nHeight),
	m_pImageData(cSource.m_pImageData),
	m_nBytesPerPixel(cSource.m_nBytesPerPixel),
	m_nRed(cSource.m_nRed),
	m_nGreen(cSource.m_nGreen),
	m_nBlue(cSource.m_nBlue)
{
}

/**
*  @brief
*    Destructor
*/
ImageTools::~ImageTools()
{
}

/**
*  @brief
*    Copy operator
*/
ImageTools &ImageTools::operator =(const ImageTools &cSource)
{
	// Copy data
	m_pImageBuffer   = cSource.m_pImageBuffer;
	m_nWidth         = cSource.m_nWidth;
	m_nHeight        = cSource.m_nHeight;
	m_pImageData     = cSource.m_pImageData;
	m_nBytesPerPixel = cSource.m_nBytesPerPixel;
	m_nRed           = cSource.m_nRed;
	m_nGreen         = cSource.m_nGreen;
	m_nBlue          = cSource.m_nBlue;

	// Return a reference to this instance
	return *this;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws a Bresenham line
*/
void ImageTools::DrawBresenhamLine(const Color3 &cColor, int nXStart, int nYStart, int nXEnd, int nYEnd)
{
	// Cache color
	m_nRed   = cColor.GetRInt();
	m_nGreen = cColor.GetGInt();
	m_nBlue  = cColor.GetBInt();

	// See: http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	int nDeltaX = nXEnd - nXStart;
	const char ix = (nDeltaX > 0) - (nDeltaX < 0);
	nDeltaX = Math::Abs(nDeltaX) << 1;

	int nDeltaY = nYEnd - nYStart;
	const char iy = (nDeltaY > 0) - (nDeltaY < 0);
	nDeltaY = Math::Abs(nDeltaY) << 1;

	DrawPixel(nXStart, nYStart);

	if (nDeltaX >= nDeltaY) {
		// Error may go below zero
		int nError = nDeltaY - (nDeltaX >> 1);

		while (nXStart != nXEnd) {
			if (nError >= 0) {
				if (nError || (ix > 0)) {
					nYStart += iy;
					nError -= nDeltaX;
				}
			}

			nXStart += ix;
			nError += nDeltaY;

			DrawPixel(nXStart, nYStart);
		}
	} else {
		// Error may go below zero
		int nError = nDeltaX - (nDeltaY >> 1);

		while (nYStart != nYEnd) {
			if (nError >= 0) {
				if (nError || (iy > 0)) {
					nXStart += ix;
					nError -= nDeltaY;
				}
			}

			nYStart += iy;
			nError += nDeltaX;

			DrawPixel(nXStart, nYStart);
		}
	}
}

/**
*  @brief
*    Draws a Bresenham circle (aka "midpoint circle algorithm")
*/
void ImageTools::DrawBresenhamCircle(const Color3 &cColor, int nX, int nY, int nRadius)
{
	// Cache color
	m_nRed   = cColor.GetRInt();
	m_nGreen = cColor.GetGInt();
	m_nBlue  = cColor.GetBInt();

	// Source: http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
	int f     = 1 - nRadius;
	int ddF_x = 1;
	int ddF_y = -2 * nRadius;
	int x     = 0;
	int y     = nRadius;

	DrawPixel(nX, nY + nRadius);
	DrawPixel(nX, nY - nRadius);
	DrawPixel(nX + nRadius, nY);
	DrawPixel(nX - nRadius, nY);

	while (x < y) {
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - nRadius*nRadius + 2*x - y + 1;
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		DrawPixel(nX + x, nY + y);
		DrawPixel(nX - x, nY + y);
		DrawPixel(nX + x, nY - y);
		DrawPixel(nX - x, nY - y);
		DrawPixel(nX + y, nY + x);
		DrawPixel(nX - y, nY + x);
		DrawPixel(nX + y, nY - x);
		DrawPixel(nX - y, nY - x);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws a pixel using the current settings
*/
void ImageTools::DrawPixel(int nX, int nY) const
{
	// Check if valid pixel coordinate
	if (nX >= 0 && nX < m_nWidth && nY >= 0 && nY < m_nHeight) {
		// Get pixel memory address
		uint8 *pData = &m_pImageData[(nX + nY*m_nWidth)*m_nBytesPerPixel];

		// Set RGB value
		*pData = m_nRed;
		pData++;
		*pData = m_nGreen;
		pData++;
		*pData = m_nBlue;
		pData++;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
