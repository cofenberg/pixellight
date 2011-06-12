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
#include "PLSoundNull/SoundManager.h"
#include "PLSoundNull/Source.h"
#include "PLSoundNull/Buffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLSoundNull {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
Buffer::~Buffer()
{
	// Unload sound
	Unload();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Buffer::Buffer(PLSound::SoundManager &cSoundManager, const String &sName, bool bStream) :
	PLSound::Buffer(cSoundManager, sName)
{
	// Load the sound buffer
	if (sName.GetLength())
		LoadBuffer(sName, bStream);
}


//[-------------------------------------------------------]
//[ Public virtual PLSound::Buffer functions              ]
//[-------------------------------------------------------]
bool Buffer::LoadBuffer(const String &sFilename, bool bStream)
{
	// Check parameter
	return (sFilename.GetLength() != 0);
}

bool Buffer::LoadBuffer(const uint8 nData[], uint32 nSize, bool bStream)
{
	// Check parameters
	return (nSize != 0);
}

bool Buffer::IsLoaded() const
{
	return false;
}

bool Buffer::IsStreamed() const
{
	return false;
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Resource functions             ]
//[-------------------------------------------------------]
bool Buffer::Load(const String &sName)
{
	return LoadBuffer(sName, false);
}

bool Buffer::Unload()
{
	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundNull
