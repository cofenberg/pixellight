/*********************************************************\
 *  File: UniformBuffer.inl                              *
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
#include <PLCore/Core/MemoryManager.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copies data from a given buffer into this uniform buffer
*/
inline void UniformBuffer::CopyDataFrom(const void *pData)
{
	// Lock the uniform buffer
	if (Lock(Lock::WriteOnly)) {
		// Copy over all the uniform data at once
		PLCore::MemoryManager::Copy(GetData(), pData, GetSize());

		// Unlock the uniform buffer
		Unlock();
	}
}

/**
*  @brief
*    Copies data from this uniform buffer into a given buffer
*/
inline void UniformBuffer::CopyDataTo(void *pData)
{
	// Lock the uniform buffer
	if (Lock(Lock::ReadOnly)) {
		// Copy over all the uniform data at once
		PLCore::MemoryManager::Copy(pData, GetData(), GetSize());

		// Unlock the uniform buffer
		Unlock();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
