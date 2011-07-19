/*********************************************************\
 *  File: IEFlipXAxis.cpp                                *
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
#include "PLGraphics/Image/Effects/IEFlipXAxis.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(IEFlipXAxis)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
IEFlipXAxis::IEFlipXAxis()
{
}

/**
*  @brief
*    Destructor
*/
IEFlipXAxis::~IEFlipXAxis()
{
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
bool IEFlipXAxis::Apply(ImageBuffer &cImageBuffer) const
{
	// Get the number of bytes per row
	const uint32 nRowSize = cImageBuffer.GetRowSize();
	if (nRowSize) {
		// Get the number of bytes per pixel
		const uint32 nBytesPerPixel = cImageBuffer.GetBytesPerPixel();
		if (nBytesPerPixel) {
			// Allocate memory to backup one pixel
			uint8 *pnLeftPixelBackup = new uint8[nBytesPerPixel];

			// Loop through all rows
			      uint8 *pnRow     = cImageBuffer.GetData();
			const uint8 *pnDataEnd = pnRow + cImageBuffer.GetDataSize();
			for (; pnRow<pnDataEnd; pnRow+=nRowSize) {
				// Loop through pixels within the row
				uint8 *pnLeftPixel  = pnRow;
				uint8 *pnRightPixel = pnRow + nRowSize - nBytesPerPixel;
				for (; pnLeftPixel<pnRightPixel; pnLeftPixel+=nBytesPerPixel, pnRightPixel-=nBytesPerPixel) {
					// Backup the content of the current left pixel
					MemoryManager::Copy(pnLeftPixelBackup, pnLeftPixel, nBytesPerPixel);

					// Copy the content of the current right pixel to the current left pixel
					MemoryManager::Copy(pnLeftPixel, pnRightPixel, nBytesPerPixel);

					// Copy the backup content of the current left pixel to the current right pixel
					MemoryManager::Copy(pnRightPixel, pnLeftPixelBackup, nBytesPerPixel);
				}
			}

			// Cleanup left pixel backup memory
			delete [] pnLeftPixelBackup;
		}

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
