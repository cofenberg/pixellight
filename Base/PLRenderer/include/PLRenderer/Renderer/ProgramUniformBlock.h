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
#include <PLCore/PLCore.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class String;
}
namespace PLRenderer {
	class UniformBuffer;
}


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
		*    Sets the uniform buffer feeding this uniform block with data
		*
		*  @param[in] pUniformBuffer
		*    The uniform buffer feeding this uniform block with data, can be a null pointer
		*  @param[in] nBindingPoint
		*    Binding point to use
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the number of bytes within the given uniform buffer
		*    is less than the number of bytes within this uniform block or there's a shader language mismatch)
		*
		*  @remarks
		*    The binding point is somewhat similar a texture unit. The total number of binding points
		*    which can be used at the same time during rendering are limited to e.g. 45 (just an example!)
		*    binding points.
		*/
		virtual bool SetUniformBuffer(UniformBuffer *pUniformBuffer, PLCore::uint32 nBindingPoint) = 0;

		/**
		*  @brief
		*    Returns the uniform block index
		*
		*  @return
		*    The uniform block index
		*/
		virtual PLCore::uint32 GetIndex() const = 0;

		/**
		*  @brief
		*    Returns the uniform block data size (in bytes)
		*
		*  @return
		*    The uniform block data size (in bytes)
		*/
		virtual PLCore::uint32 GetSize() const = 0;

		/**
		*  @brief
		*    Returns the offset (in bytes) of an uniform inside the uniform block
		*
		*  @param[in] sUniformName
		*    Name of the uniform
		*
		*  @return
		*    The offset (in bytes) of an uniform inside the uniform block
		*/
		virtual PLCore::uint32 GetUniformOffset(const PLCore::String &sUniformName) const = 0;

		/**
		*  @brief
		*    Returns the size (in bytes) of an uniform inside the uniform block
		*
		*  @return
		*    The size (in bytes) of an uniform inside the uniform block
		*/
		virtual PLCore::uint32 GetUniformSize(const PLCore::String &sUniformName) const = 0;

		/**
		*  @brief
		*    Returns the number of array elements of an uniform inside the uniform block
		*
		*  @return
		*    The number of array elements of an uniform inside the uniform block, 1 for none array uniforms
		*/
		virtual PLCore::uint32 GetUniformNumOfArrayElements(const PLCore::String &sUniformName) const = 0;


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
