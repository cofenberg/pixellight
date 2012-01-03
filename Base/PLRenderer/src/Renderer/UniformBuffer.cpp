/*********************************************************\
 *  File: UniformBuffer.cpp                              *
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
#include "PLRenderer/Renderer/UniformBuffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
UniformBuffer::~UniformBuffer()
{
}

/**
*  @brief
*    Copy operator
*/
UniformBuffer &UniformBuffer::operator =(const UniformBuffer &cSource)
{
	// Lock the source buffer
	if (const_cast<UniformBuffer&>(cSource).Lock(Lock::ReadOnly)) {
		// Clear old uniform buffer
		Clear();

		// Copy
		Allocate(cSource.GetNumOfElements(), cSource.GetUsage(), cSource.IsManaged());
		if (Lock(Lock::WriteOnly)) {
			MemoryManager::Copy(GetData(), const_cast<UniformBuffer&>(cSource).GetData(), cSource.GetSize());
			Unlock();
		}

		// Unlock the source buffer
		const_cast<UniformBuffer&>(cSource).Unlock();
	}

	// Done
	return *this;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
UniformBuffer::UniformBuffer(Renderer &cRenderer) : Buffer(cRenderer, TypeUniformBuffer)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
UniformBuffer::UniformBuffer(const UniformBuffer &cSource) : Buffer(cSource.GetRenderer(), TypeUniformBuffer)
{
	// No implementation because the copy constructor is never used
}


//[-------------------------------------------------------]
//[ Public virtual Buffer functions                       ]
//[-------------------------------------------------------]
void *UniformBuffer::GetData()
{
	// We need this dummy default implementation because this function is used within this file!
	return nullptr;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
