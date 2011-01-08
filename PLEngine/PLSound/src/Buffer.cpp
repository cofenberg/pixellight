/*********************************************************\
 *  File: Buffer.cpp                                     *
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
#include "PLSound/Source.h"
#include "PLSound/SoundManager.h"
#include "PLSound/Buffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLSound {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Buffer::~Buffer()
{
	// Unload all sources using this buffer
	while (m_lstSources.GetNumOfElements())
		m_lstSources[0]->Unload();
}

/**
*  @brief
*    Returns the number of sources
*/
uint32 Buffer::GetNumOfSources() const
{
	return m_lstSources.GetNumOfElements();
}

/**
*  @brief
*    Returns a sound source
*/
const Source *Buffer::GetSource(uint32 nIndex) const
{
	return m_lstSources[nIndex];
}

/**
*  @brief
*    Returns a sound source
*/
Source *Buffer::GetSource(uint32 nIndex)
{
	return m_lstSources[nIndex];
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*   Constructor
*/
Buffer::Buffer(SoundManager &cSoundManager, const String &sName) :
	Resource(cSoundManager, TypeBuffer), PLCore::Resource<Buffer>(sName, &cSoundManager)
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Buffer::Buffer(const Buffer &cSource) :
	Resource(cSource.GetSoundManager(), cSource.GetType()), PLCore::Resource<Buffer>(cSource.GetName(), &cSource.GetSoundManager())
{
	// No implementation because the copy constructor is never used
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound
