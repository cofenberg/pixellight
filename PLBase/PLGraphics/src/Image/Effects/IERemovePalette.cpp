/*********************************************************\
 *  File: IERemovePalette.cpp                            *
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
#include "PLGraphics/Color/Color3.h"
#include "PLGraphics/Image/ImageBuffer.h"
#include "PLGraphics/Image/ImagePalette.h"
#include "PLGraphics/Image/Effects/IERemovePalette.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(IERemovePalette)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
IERemovePalette::IERemovePalette()
{
}

/**
*  @brief
*    Destructor
*/
IERemovePalette::~IERemovePalette()
{
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
bool IERemovePalette::Apply(ImageBuffer &cImageBuffer) const
{
	// Must be a palette color format
	if (cImageBuffer.GetColorFormat() == ColorPalette) {
		// Get the palette
		const ImagePalette *pImagePalette = cImageBuffer.GetPalette();
		if (pImagePalette) {
			// Create the new image buffer
			ImageBuffer cOldImageBuffer = cImageBuffer;
			cImageBuffer.CreateImage(cOldImageBuffer.GetDataFormat(), ColorRGB, cOldImageBuffer.GetSize());

			// Remove palette data format dependent
			switch (cImageBuffer.GetDataFormat()) {
				case DataByte:
				{
					// Get the data pointers
						  uint8 *pNewData = cImageBuffer   .GetData();
					const uint8 *pOldData = cOldImageBuffer.GetData();

					// Fill the new buffer
					for (const uint8 *pNewDataEnd=cImageBuffer.GetData()+cImageBuffer.GetDataSize(); pNewData<pNewDataEnd; ) {
						// Get the color from the palette
						const Color3 cColor = pImagePalette->GetColor(*pOldData);

						// Next color index, please
						pOldData++;

						// Write down the red color component into the new buffer and go to the next color component
						*pNewData = cColor.GetRInt();
						pNewData++;

						// Write down the green color component into the new buffer and go to the next color component
						*pNewData = cColor.GetGInt();
						pNewData++;

						// Write down the blue color component into the new buffer and go to the next color component
						*pNewData = cColor.GetBInt();
						pNewData++;

					}
					break;
				}

				case DataWord:
				{
					// Get the data pointers
						  uint16 *pNewData = (uint16*)cImageBuffer   .GetData();
					const uint16 *pOldData = (uint16*)cOldImageBuffer.GetData();

					// Fill the new buffer
					for (const uint8 *pNewDataEnd=cImageBuffer.GetData()+cImageBuffer.GetDataSize(); (uint8*)pNewData<pNewDataEnd; ) {
						// Get the color from the palette
						const Color3 cColor = pImagePalette->GetColor(*pOldData);

						// Next color index, please
						pOldData++;

						// Write down the red color component into the new buffer and go to the next color component
						*pNewData = cColor.GetRInt();
						pNewData++;

						// Write down the green color component into the new buffer and go to the next color component
						*pNewData = cColor.GetGInt();
						pNewData++;

						// Write down the blue color component into the new buffer and go to the next color component
						*pNewData = cColor.GetBInt();
						pNewData++;

					}
					break;
				}

				case DataFloat:
					// [TODO] Is this possible within a palette?
					break;

				case DataDouble:
					// [TODO] Is this possible within a palette?
					break;
			}
		}
	}

	// Not implemented
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
