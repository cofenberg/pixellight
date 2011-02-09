/*********************************************************\
 *  File: Source.cpp                                     *
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
Source::~Source()
{
	// Unload
	Unload();
}

/**
*  @brief
*    Returns the buffer the source is using
*/
Buffer *Source::GetBuffer() const
{
	return static_cast<Buffer*>(m_cBufferHandler.GetResource());
}

/**
*  @brief
*    Returns the source flags
*/
uint32 Source::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Sets the source flags
*/
void Source::SetFlags(uint32 nFlags)
{
	m_nFlags = nFlags;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Source::Source(SoundManager &cSoundManager) : Resource(cSoundManager, Resource::TypeSource),
	m_nFlags(0)
{
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads the sound source with the given sound buffer
*/
bool Source::Load(Buffer *pBuffer)
{
	// Unload the old buffer
	Unload();

	// Add this source to the buffer
	if (pBuffer) {
		m_cBufferHandler.SetResource(pBuffer);
		pBuffer->m_lstSources.Add(this);
	}

	// Done
	return true;
}

/**
*  @brief
*    Unload the source
*/
void Source::Unload()
{
	// Is a buffer loaded?
	Buffer *pBuffer = static_cast<Buffer*>(m_cBufferHandler.GetResource());
	if (pBuffer) {
		// Remove this source from the buffer
		pBuffer->m_lstSources.Remove(this);
		m_cBufferHandler.SetResource();
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Source::Source(const Source &cSource) : Resource(cSource.GetSoundManager(), cSource.GetType()),
	m_nFlags(cSource.GetFlags())
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Source &Source::operator =(const Source &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound
