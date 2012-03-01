/*********************************************************\
 *  File: IEFlipYAxis.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLGraphics/Image/Effects/IEFlipYAxis.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(IEFlipYAxis)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
IEFlipYAxis::IEFlipYAxis()
{
}

/**
*  @brief
*    Destructor
*/
IEFlipYAxis::~IEFlipYAxis()
{
}


//[-------------------------------------------------------]
//[ Public virtual ImageEffect functions                  ]
//[-------------------------------------------------------]
bool IEFlipYAxis::Apply(ImageBuffer &cImageBuffer) const
{
	// Get the number of bytes per row
	const uint32 nBytesPerRow = cImageBuffer.GetBytesPerRow();
	if (nBytesPerRow) {
		// Allocate memory to backup one row
		uint8 *pnUpperRowBackup = new uint8[nBytesPerRow];

		// Loop through rows
		uint8 *pnUpperRow = cImageBuffer.GetData();
		uint8 *pnLowerRow = pnUpperRow + cImageBuffer.GetDataSize() - nBytesPerRow;
		for (; pnUpperRow<pnLowerRow; pnUpperRow+=nBytesPerRow, pnLowerRow-=nBytesPerRow) {
			// Backup the content of the current upper row
			MemoryManager::Copy(pnUpperRowBackup, pnUpperRow, nBytesPerRow);

			// Copy the content of the current lower row to the current upper row
			MemoryManager::Copy(pnUpperRow, pnLowerRow, nBytesPerRow);

			// Copy the backup content of the current upper row to the current lower row
			MemoryManager::Copy(pnLowerRow, pnUpperRowBackup, nBytesPerRow);
		}

		// Cleanup upper row backup memory
		delete [] pnUpperRowBackup;

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
