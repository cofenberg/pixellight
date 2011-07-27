/*********************************************************\
 *  File: IEMonochrome.cpp                               *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLGraphics/Image/Effects/IEMonochrome.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
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
		*    Image buffer (MUST have valid data!)
		*/
		ProcessData(ImageBuffer &cImageBuffer)
		{
			// Get the data pointer
			DataType *pData = reinterpret_cast<DataType*>(cImageBuffer.GetData());

			// Get the number of color components
			const uint32 nNumOfColorComponents = cImageBuffer.GetComponentsPerPixel();

			// Convert color format dependent
			switch (cImageBuffer.GetColorFormat()) {
				case ColorRGB:
				case ColorRGBA:
					// Loop through all pixels
					for (const DataType *pDataEnd=pData+cImageBuffer.GetDataSize(); pData<pDataEnd; pData+=nNumOfColorComponents) {
						// Convert RGB to grayscale using "Human formula"... our eyes recognize color components not uniformly
						const DataType nGrayscale = DataType(pData[0]*0.299 + pData[1]*0.587 + pData[2]*0.114);

						// Set new values
						pData[0] = nGrayscale;
						pData[1] = nGrayscale;
						pData[2] = nGrayscale;
					}
					break;

				case ColorBGR:
				case ColorBGRA:
					// Loop through all pixels
					for (const DataType *pDataEnd=pData+cImageBuffer.GetDataSize(); pData<pDataEnd; pData+=nNumOfColorComponents) {
						// Convert BGR to grayscale using "Human formula"... our eyes recognize color components not uniformly
						const DataType nGrayscale = DataType(pData[2]*0.299 + pData[1]*0.587 + pData[0]*0.114);

						// Set new values
						pData[0] = nGrayscale;
						pData[1] = nGrayscale;
						pData[2] = nGrayscale;
					}
					break;
			}
		}


};


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(IEMonochrome)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
IEMonochrome::IEMonochrome()
{
}

/**
*  @brief
*    Destructor
*/
IEMonochrome::~IEMonochrome()
{
}


//[-------------------------------------------------------]
//[ Public virtual ImageEffect functions                  ]
//[-------------------------------------------------------]
bool IEMonochrome::Apply(ImageBuffer &cImageBuffer) const
{
	// ColorPalette as color format is not supported
	if (cImageBuffer.GetColorFormat() != ColorPalette) {
		// Process data format dependent
		switch (cImageBuffer.GetDataFormat()) {
			case DataByte:
			{
				ProcessData<uint8> cProcessData(cImageBuffer);
				break;
			}

			case DataWord:
			{
				ProcessData<uint16> cProcessData(cImageBuffer);
				break;
			}

			case DataHalf:
			{
				// [TODO] DataHalf - Implement me
				break;
			}

			case DataFloat:
			{
				ProcessData<float> cProcessData(cImageBuffer);
				break;
			}

			case DataDouble:
			{
				ProcessData<double> cProcessData(cImageBuffer);
				break;
			}
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
