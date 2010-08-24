/*********************************************************\
 *  File: Source.h                                       *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSOUNDOPENAL_SOURCE_H__
#define __PLSOUNDOPENAL_SOURCE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/Source.h>
#include "PLSoundOpenAL/PLSoundOpenAL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundOpenAL {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Stream;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenAL sound source resource
*/
class Source : public PLSound::Source {


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
		virtual ~Source();


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
		*/
		Source(PLSound::SoundManager &cSoundManager);

		/**
		*  @brief
		*    Updates the source
		*
		*  @note
		*    - This must only be done for currently active sources
		*/
		void Update();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ALuint			 m_nSource;				/**< Sound source */
		Stream			*m_pStream;				/**< Sound source stream if streamed buffer is used, else NULL */
		bool			 m_b2D;					/**< Is this a 2D sound? */
		bool			 m_bLooping;			/**< Is the source looping? */
		float			 m_fPitch;				/**< Pitch */
		float			 m_fReferenceDistance;	/**< Used to increase or decrease the range of a source by decreasing or increasing the attenuation, respectively */
		float			 m_fMaxDistance;		/**< Defines a distance beyond which the source will not be further attenuated by distance */
		float			 m_fRolloffFactor;		/**< This will scale the distance attenuation over the applicable range */
		PLMath::Vector3  m_vPosition;			/**< Sound position */
		PLMath::Vector3  m_vVelocity;			/**< Sound velocity */


	//[-------------------------------------------------------]
	//[ Public virtual PLSound::Source functions              ]
	//[-------------------------------------------------------]
	public:
		virtual bool Load(PLSound::Buffer *pBuffer = NULL);
		virtual void Unload();
		virtual bool Play(bool bRestart = false);
		virtual bool IsPlaying() const;
		virtual void Pause();
		virtual bool IsPaused() const;
		virtual void Stop();
		virtual float GetVolume() const;
		virtual void SetVolume(float fVolume = 1.0f);
		virtual bool Is2D() const;
		virtual void Set2D(bool b2D = false);
		virtual bool IsLooping() const;
		virtual void SetLooping(bool bLooping = false);
		virtual float GetPitch() const;
		virtual void SetPitch(float fPitch = 1.0f);
		virtual float GetReferenceDistance() const;
		virtual void SetReferenceDistance(float fReferenceDistance = 1.0f);
		virtual float GetMaxDistance() const;
		virtual void SetMaxDistance(float fMaxDistance = 10000.0f);
		virtual float GetRolloffFactor() const;
		virtual void SetRolloffFactor(float fRolloffFactor = 1.0f);
		virtual PLMath::Vector3 GetAttribute(EAttributes nAttribute) const;
		virtual bool SetAttribute(EAttributes nAttribute, const PLMath::Vector3 &vV);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundOpenAL


#endif // __PLSOUNDOPENAL_SOURCE_H__
