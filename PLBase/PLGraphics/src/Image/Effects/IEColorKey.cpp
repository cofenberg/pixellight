/*********************************************************\
 *  File: IEColorKey.cpp                                 *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGraphics/Image/ImageBuffer.h"
#include "PLGraphics/Image/ImageEffects.h"
#include "PLGraphics/Image/Effects/IEColorKey.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Data process template
*/
template <typename DataType>
class ProcessData {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in, out] cImageBuffer
		*    Image buffer (MUST have valid data and a color format with alpha channel!)
		*  @param[in]      nRedKey
		*    Red color component of the key
		*  @param[in]      nGreenKey
		*    Green color component of the key
		*  @param[in]      nBlueKey
		*    Blue color component of the key
		*  @param[in]      nTolerance
		*    Tolerance
		*  @param[in]      nTransparent
		*    Alpha value for transparent pixel
		*  @param[in]      nNoneTransparent
		*    Alpha value for none transparent pixel
		*/
		ProcessData(const ImageBuffer &cImageBuffer, DataType nRedKey, DataType nGreenKey, DataType nBlueKey, DataType nTolerance, DataType nTransparent, DataType nNoneTransparent)
		{
			// Get the data pointer
			DataType *pData = (DataType*)cImageBuffer.GetData();

			// Get the number of color components
			const uint32 nNumOfColorComponents = cImageBuffer.GetComponentsPerPixel();

			// Process data format dependent
			switch (cImageBuffer.GetColorFormat()) {
				case ColorRGBA:
					// Loop through all pixels
					for (const DataType *pDataEnd=pData+cImageBuffer.GetDataSize(); pData<pDataEnd; pData+=nNumOfColorComponents) {
						// Get the red color component difference
						const DataType nRedDifference = (pData[0] > nRedKey) ? pData[0] - nRedKey : nRedKey - pData[0];

						// Get the green color component difference
						const DataType nGreenDifference = (pData[1] > nGreenKey) ? pData[1] - nGreenKey : nGreenKey - pData[1];

						// Get the blue color component difference
						const DataType nBlueDifference = (pData[2] > nBlueKey) ? pData[2] - nBlueKey : nBlueKey - pData[2];

						// Is this pixel transparent or not?
						pData[3] = (nRedDifference <= nTolerance && nGreenDifference <= nTolerance && nBlueDifference <= nTolerance) ? nTransparent : nNoneTransparent;
					}
					break;

				case ColorBGRA:
					// Loop through all pixels
					for (const DataType *pDataEnd=pData+cImageBuffer.GetDataSize(); pData<pDataEnd; pData+=nNumOfColorComponents) {
						// Get the blue color component difference
						const DataType nBlueDifference = (pData[2] > nRedKey) ? pData[2] - nRedKey : nRedKey - pData[2];

						// Get the green color component difference
						const DataType nGreenDifference = (pData[1] > nGreenKey) ? pData[1] - nGreenKey : nGreenKey - pData[1];

						// Get the red color component difference
						const DataType nRedDifference = (pData[0] > nBlueKey) ? pData[0] - nBlueKey : nBlueKey - pData[0];

						// Is this pixel transparent or not?
						pData[3] = (nBlueDifference <= nTolerance && nGreenDifference <= nTolerance && nRedDifference <= nTolerance) ? nTransparent : nNoneTransparent;
					}
					break;

				case ColorGrayscaleA:
				{
					// Convert RGB to grayscale using "Human formula"... our eyes recognize color components not uniformly
					const DataType nKey = DataType(nRedKey*0.299 + nGreenKey*0.587 + nBlueKey*0.114);

					// Loop through all pixels
					for (const DataType *pDataEnd=pData+cImageBuffer.GetDataSize(); pData<pDataEnd; pData+=nNumOfColorComponents) {
						// Get the grayscale component difference
						const DataType nDifference = (pData[0] > nKey) ? pData[0] - nKey : nKey - pData[0];

						// Is this pixel transparent or not?
						pData[1] = (nDifference <= nTolerance) ? nTransparent : nNoneTransparent;
					}
					break;
				}
			}
		}


};


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(IEColorKey)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
IEColorKey::IEColorKey(const Color3 &cColor, float fTolerance) :
	m_cColor(cColor),
	m_fTolerance(fTolerance)
{
	// Validate the tolerance
	if (m_fTolerance < 0.0f)
		m_fTolerance = 0.0f;
	if (m_fTolerance > 1.0f)
		m_fTolerance = 1.0f;
}

/**
*  @brief
*    Destructor
*/
IEColorKey::~IEColorKey()
{
}

/**
*  @brief
*    Get color
*/
Color3 IEColorKey::GetColor() const
{
	return m_cColor;
}

/**
*  @brief
*    Get tolerance
*/
float IEColorKey::GetTolerance() const
{
	return m_fTolerance;
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
bool IEColorKey::Apply(ImageBuffer &cImageBuffer) const
{
	// The color format "ColorPalette" is not supported
	if (cImageBuffer.GetColorFormat() != ColorPalette) {
		// Has the original color format an alpha channel?
		if (!ImageBuffer::IsAlphaChannelColorFormat(cImageBuffer.GetColorFormat())) {
			// Get a version with alpha channel of the given color format
			const EColorFormat nAlphaChannelColorFormat = ImageBuffer::GetAlphaChannelColorFormat(cImageBuffer.GetColorFormat());

			// Has the found color format an alpha channel?
			if (!ImageBuffer::IsAlphaChannelColorFormat(nAlphaChannelColorFormat))
				return false; // Error, we were not able to get a color format version with an alpha channel!

			// Convert the image buffer into the new color format
			if (!ImageEffects::Convert(cImageBuffer.GetDataFormat(), nAlphaChannelColorFormat).Apply(cImageBuffer))
				return false; // Error!
		}

		// Process data format dependent
		switch (cImageBuffer.GetDataFormat()) {
			case DataByte:
			{
				ProcessData<uint8> cProcessData(cImageBuffer, m_cColor.GetRInt(), m_cColor.GetGInt(), m_cColor.GetBInt(), uint8(m_fTolerance*255), 0, 255);
				break;
			}

			case DataWord:
			{
				ProcessData<uint16> cProcessData(cImageBuffer, uint16(m_cColor.GetR()*65535), uint16(m_cColor.GetG()*65535), uint16(m_cColor.GetB()*65535), uint16(m_fTolerance*65535), 0, 255);
				break;
			}

			case DataFloat:
			{
				ProcessData<float> cProcessData(cImageBuffer, m_cColor.GetR(), m_cColor.GetG(), m_cColor.GetB(), m_fTolerance, 0.0f, 1.0f);
				break;
			}

			case DataDouble:
			{
				ProcessData<double> cProcessData(cImageBuffer, m_cColor.GetR(), m_cColor.GetG(), m_cColor.GetB(), m_fTolerance, 0, 1);
				break;
			}
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
