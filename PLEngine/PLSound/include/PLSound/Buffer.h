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


#ifndef __PLSOUND_BUFFER_H__
#define __PLSOUND_BUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Resource.h>
#include "PLSound/Resource.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSound {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Source;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract sound buffer resource
*/
class Buffer : public Resource, public PLCore::Resource<Buffer> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Source;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLSOUND_API virtual ~Buffer();

		/**
		*  @brief
		*    Returns the number of sources
		*
		*  @return
		*    Number of sources
		*/
		PLSOUND_API PLGeneral::uint32 GetNumOfSources() const;

		/**
		*  @brief
		*    Returns a sound source
		*
		*  @param[in] nIndex
		*    Index of the resource to return
		*
		*  @return
		*    The source at the given index, a null pointer on error
		*/
		PLSOUND_API const Source *GetSource(PLGeneral::uint32 nIndex = 0) const;

		/**
		*  @brief
		*    Returns a sound source
		*
		*  @param[in] nIndex
		*    Index of the resource to return
		*
		*  @return
		*    The source at the given index, a null pointer on error
		*/
		PLSOUND_API Source *GetSource(PLGeneral::uint32 nIndex = 0);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Loads the sound buffer with the given data from a file
		*
		*  @param[in] sFilename
		*    Sound filename (full path, supported file formats are API dependent)
		*  @param[in] bStream
		*    Stream the file?
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Not each sound buffer can be streamed, use IsStreamed()
		*      to check whether streaming is used
		*/
		virtual bool LoadBuffer(const PLGeneral::String &sFilename, bool bStream) = 0;

		/**
		*  @brief
		*    Loads the sound buffer with the given data from memory
		*
		*  @param[in] nData
		*    Sound data
		*  @param[in] nSize
		*    Number of data bytes (MUST be valid!)
		*  @param[in] bStream
		*    Stream the data?
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If bStream is 'true' nData MUST stay valid!
		*    - Not each sound buffer can be streamed, use IsStreamed() to check whether streaming is used
		*/
		virtual bool LoadBuffer(const PLGeneral::uint8 nData[], PLGeneral::uint32 nSize, bool bStream = false) = 0;

		/**
		*  @brief
		*    Returns whether the buffer is loaded or not
		*
		*  @return
		*    'true' if the buffer is loaded, else 'false'
		*/
		virtual bool IsLoaded() const = 0;

		/**
		*  @brief
		*    Returns whether the buffer is streamed or not
		*
		*  @return
		*    'true' if the buffer is streamed, else 'false'
		*/
		virtual bool IsStreamed() const = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSoundManager
		*    Owner sound manager
		*  @param[in] sName
		*    Resource name to set
		*/
		PLSOUND_API Buffer(SoundManager &cSoundManager, const PLGeneral::String &sName = "");


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
		Buffer(const Buffer &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::List<Source*> m_lstSources;	/**< List of sources using this buffer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound


#endif // __PLSOUND_BUFFER_H__
