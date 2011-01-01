/*********************************************************\
 *  File: SoundManager.h                                 *
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


#ifndef __PLSOUND_SOUNDMANAGER_H__
#define __PLSOUND_SOUNDMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include <PLCore/Tools/ResourceManager.h>
#include <PLMath/Vector3.h>
#include "PLSound/Buffer.h"
#include "PLSound/BufferHandler.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSound {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Resource;
class Source;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract sound manager main class
*
*  @note
*    - Does not unload unused resources automatically by default
*/
class SoundManager : public PLCore::Object, public PLCore::ResourceManager<Buffer> {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Listener attributes
		*/
		enum EListener {
			ListenerPosition = 0,	/**< Position (float3, x/y/z) */
			ListenerVelocity = 1,	/**< Velocity in meters per second (float3, x/y/z) */
			ListenerForward  = 2,	/**< Forward unit length orientation vector (float3, x/y/z) */
			ListenerUpward   = 3,	/**< Upwards facing unit length orientation vector (float3, x/y/z) */
			ListenerNumber   = 4	/**< Number of listener properties */
		};


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLSOUND_RTTI_EXPORT, SoundManager, "PLSound", PLCore::Object, "Abstract sound manager main class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Sound statistics
		*/
		struct Statistics {
			PLGeneral::uint32 nNumOfBuffers;		/**< Number of sound buffers */
			PLGeneral::uint32 nNumOfSources;		/**< Number of sound sources */
			PLGeneral::uint32 nNumOfActiveSources;	/**< Number of currently active sound sources */
		};

		/**
		*  @brief
		*    Sound format
		*/
		class Format {
		public:
			PLGeneral::String sFormat;		/**< Sound format */
			PLGeneral::String sDescription;	/**< Sound format description */
			bool operator ==(const Format &cOther) const
			{
				return sFormat == cOther.sFormat && sDescription == cOther.sDescription;
			}
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLSOUND_API virtual ~SoundManager();

		/**
		*  @brief
		*    Returns the sound statistics
		*
		*  @return
		*    The sound statistics
		*/
		PLSOUND_API const Statistics &GetStatistics() const;

		//[-------------------------------------------------------]
		//[ Resources                                             ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of resources
		*
		*  @return
		*    Number of resources
		*/
		PLSOUND_API PLGeneral::uint32 GetNumOfResources() const;

		/**
		*  @brief
		*    Returns a sound resource
		*
		*  @param[in] nIndex
		*    Index of the resource to return
		*
		*  @return
		*    The resource at the given index, NULL on error
		*/
		PLSOUND_API Resource *GetResource(PLGeneral::uint32 nIndex = 0) const;

		/**
		*  @brief
		*    Adds a sound resource to the sound manager
		*
		*  @param[in] cResource
		*    Sound resource to add
		*
		*  @return
		*    'true' if all went fine and the sound resource was added to the sound manager,
		*    else 'false'
		*
		*  @note
		*    - The sound resource itself is only added to the sound manager's list of resources!
		*/
		PLSOUND_API bool AddResource(Resource &cResource);

		/**
		*  @brief
		*    Removes a sound resource from the sound manager
		*
		*  @param[in] cResource
		*    Sound resource to remove
		*
		*  @return
		*    'true' if all went fine and the sound resource was removed from the
		*     sound manager, else 'false' (maybe the resource isn't in the sound manager)
		*
		*  @note
		*    - The sound resource itself isn't destroyed, it is just removed
		*      from the sound manager's list of resources! 
		*/
		PLSOUND_API bool RemoveResource(Resource &cResource);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the sound manager description
		*
		*  @return
		*    Sound manager description
		*/
		virtual PLGeneral::String GetDescription() const = 0;

		/**
		*  @brief
		*    Gets a list of all known sound formats
		*
		*  @param[out] lstList
		*    List to recieve the known sound formats (see Format)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - The given list is NOT cleared before the formats are added
		*/
		virtual bool GetFormatList(PLGeneral::List<Format> &lstList) const = 0;

		/**
		*  @brief
		*    Gets the master volume
		*
		*  @return
		*    Volume (value from 0.0-1.0 -> 0.0 = silence, 1.0 = full volume)
		*/
		virtual float GetVolume() const = 0;

		/**
		*  @brief
		*    Sets the master volume
		*
		*  @param[in] fVolume
		*    Volume (value from 0.0-1.0 -> 0.0 = silence, 1.0 = full volume)
		*/
		virtual void SetVolume(float fVolume = 1.0f) = 0;

		/**
		*  @brief
		*    Returns the master pitch multiplier
		*
		*  @return
		*    Pitch multiplier
		*
		*  @remarks
		*    pitch < 1.0 = slower\n
		*    pitch = 1.0 = normal\n
		*    pitch > 1.0 = faster
		*/
		virtual float GetPitch() const = 0;

		/**
		*  @brief
		*    Sets the master pitch multiplier
		*
		*  @param[in] fPitch
		*    Pitch multiplier
		*
		*  @see
		*    - GetPitch()
		*/
		virtual void SetPitch(float fPitch = 1.0f) = 0;

		/**
		*  @brief
		*    Gets the doppler factor
		*
		*  @return
		*    Doppler factor
		*
		*  @remarks
		*    If velocities are applied to the listener object or to any source object, then
		*    doppler shift will be applied to the audio. The following formula is used to 
		*    calculate doppler shift:\n
		*    f’ = f*(DV – DF*vl)/(DV + DF*vs)\n
		*    DV = doppler velocity\n
		*    DF = doppler factor\n
		*    vl = listener velocity (scalar value along source-to-listener vector)\n
		*    vs = source velocity (scalar value along source-to-listener vector)\n
		*    f = frequency of sample\n
		*    f’ = Doppler shifted frequency\n
		*    The doppler velocity (340) represents the speed of sound.\n
		*    The doppler factor is used to exaggerate or de-emphasize the doppler shift.
		*/
		virtual float GetDopplerFactor() const = 0;

		/**
		*  @brief
		*    Sets the doppler factor
		*
		*  @param[in] fFactor
		*    Doppler factor
		*
		*  @see
		*    - GetDopplerFactor()
		*/
		virtual void SetDopplerFactor(float fFactor = 1.0f) = 0;

		//[-------------------------------------------------------]
		//[ Create sound buffer/source                            ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Creates a sound buffer
		*
		*  @param[in] sFilename
		*    Sound filename, if empty, only create the sound buffer without loading it (full path, supported file formats are API dependent)
		*  @param[in] bStream
		*   Stream the file? (recommended for large files!)
		*
		*  @return
		*    The created sound buffer, NULL on error
		*
		*  @note
		*    - If there's already a sound buffer with this name, this sound buffer is returned
		*    - Not each sound buffer can be streamed, use SoundBuffer::IsStreamed() to
		*      check whether streaming is used.
		*/
		virtual Buffer *CreateSoundBuffer(const PLGeneral::String &sFilename = "", bool bStream = false) = 0;

		/**
		*  @brief
		*    Creates a sound source
		*
		*  @param[in] pSoundBuffer
		*    Sound buffer to load, NULL if load no sound buffer by default
		*
		*  @return
		*    The created sound source, NULL on error
		*
		*  @remarks
		*    The simplest creation of a sound source ready for playback would be\n
		*    SoundSource *pSS = pSM->CreateSoundSource(CreateSoundBuffer("MySound.wav"));\n
		*    Whereby 'MySound.wav' isn't loaded twice if there's already such a sound buffer.
		*/
		virtual Source *CreateSoundSource(Buffer *pSoundBuffer = NULL) = 0;

		//[-------------------------------------------------------]
		//[ Listener                                              ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Gets a listener attribute value
		*
		*  @param[in] nAttribute
		*    Listener attribute to return
		*
		*  @return
		*    Requested listener attribute value
		*/
		virtual PLMath::Vector3 GetListenerAttribute(EListener nAttribute) const = 0;

		/**
		*  @brief
		*    Sets a listener attribute value
		*
		*  @param[in] nAttribute
		*    Listener attribute to set
		*  @param[in] vV
		*    New listener attribute value
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool SetListenerAttribute(EListener nAttribute, const PLMath::Vector3 &vV) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLSOUND_API SoundManager();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Statistics					m_sStatistics;	/**< Sound statistics */
		PLGeneral::Array<Resource*> m_lstResources;	/**< Sound resources of this sound manager */


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
		SoundManager(const SoundManager &cSource);

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
		SoundManager &operator =(const SoundManager &cSource);


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ResourceManager functions     ]
	//[-------------------------------------------------------]
	private:
		virtual Buffer *CreateResource(const PLGeneral::String &sName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSound


#endif // __PLSOUND_SOUNDMANAGER_H__
