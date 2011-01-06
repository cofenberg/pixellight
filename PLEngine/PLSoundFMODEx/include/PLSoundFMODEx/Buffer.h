/*********************************************************\
 *  File: Buffer.h                                       *
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


#ifndef __PLSOUNDFMODEX_BUFFER_H__
#define __PLSOUNDFMODEX_BUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/Buffer.h>
#include "PLSoundFMODEx/PLSoundFMODEx.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundFMODEx {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    FMOD Ex sound buffer resource
*/
class Buffer : public PLSound::Buffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SoundManager;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Buffer();

		/**
		*  @brief
		*    Returns the FMOD Ex sound instance
		*
		*  @return
		*    The FMOD Ex sound instance, a null pointer on error
		*/
		FMOD::Sound *GetSound() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSoundManager
		*    Owner sound manager
		*  @param[in] sName
		*    Resource name to set
		*  @param[in] bStream
		*    Stream the file?
		*/
		Buffer(PLSound::SoundManager &cSoundManager, const PLGeneral::String &sName = "", bool bStream = false);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FMOD::Sound *m_pSound;		/**< Sound pointer, can be a null pointer */
		bool		 m_bStreamed;	/**< Is the sound streamed? */


	//[-------------------------------------------------------]
	//[ Public virtual PLSound::Buffer functions              ]
	//[-------------------------------------------------------]
	public:
		virtual bool LoadBuffer(const PLGeneral::String &sFilename, bool bStream);
		virtual bool LoadBuffer(const PLGeneral::uint8 nData[], PLGeneral::uint32 nSize, bool bStream = false);
		virtual bool IsLoaded() const;
		virtual bool IsStreamed() const;


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Resource functions             ]
	//[-------------------------------------------------------]
	public:
		virtual bool Load(const PLGeneral::String &sName);
		virtual bool Unload();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundFMODEx


#endif // __PLSOUNDFMODEX_BUFFER_H__
