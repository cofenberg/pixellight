/*********************************************************\
 *  File: ClipBoardNull.cpp                              *
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
#include "PLGui/Gui/Data/DataObject.h"
#include "PLGui/Backend/Null/ClipBoardNull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ClipBoardNull::ClipBoardNull(ClipBoard &cClipBoard) : ClipBoardImpl(cClipBoard)
{
}

/**
*  @brief
*    Destructor
*/
ClipBoardNull::~ClipBoardNull()
{
}


//[-------------------------------------------------------]
//[ Private virtual ClipBoardImpl functions               ]
//[-------------------------------------------------------]
DataObject ClipBoardNull::GetData()
{
	// Not implemented
	DataObject cData;
	return cData;
}

void ClipBoardNull::SetData(const DataObject &cData)
{
	// Not implemented
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui
