/*********************************************************\
 *  File: ProgramUniformBlock.h                          *
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


#ifndef __PLRENDERER_PROGRAMUNIFORMBLOCK_H__
#define __PLRENDERER_PROGRAMUNIFORMBLOCK_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer program uniform block
*/
class ProgramUniformBlock {


	//[-------------------------------------------------------]
	//[ Public virtual ProgramUniformBlock functions          ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the uniform block index
		*
		*  @return
		*    The uniform block index
		*/
		virtual PLGeneral::uint32 GetIndex() const = 0;

		/**
		*  @brief
		*    Returns the uniform block data size (in bytes)
		*
		*  @return
		*    The uniform block data size (in bytes)
		*/
		virtual PLGeneral::uint32 GetSize() const = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API ProgramUniformBlock();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~ProgramUniformBlock();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		ProgramUniformBlock(const ProgramUniformBlock &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		ProgramUniformBlock &operator =(const ProgramUniformBlock &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_PROGRAMUNIFORMBLOCK_H__
