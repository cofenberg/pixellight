/*********************************************************\
 *  File: Source.h                                       *
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


#ifndef __PLSOUNDNULL_SOURCE_H__
#define __PLSOUNDNULL_SOURCE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/Source.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundNull {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null sound source resource
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


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float			m_fVolume;						/**< Source volume */
		bool			m_b2D;							/**< Is the source 2D? */
		bool			m_bLooping;						/**< Is the source looping? */
		float			m_fPitch;						/**< Pitch */
		float			m_fReferenceDistance;			/**< Used to increase or decrease the range of a source by decreasing or increasing the attenuation, respectively */
		float			m_fMaxDistance;					/**< Defines a distance beyond which the source will not be further attenuated by distance */
		float			m_fRolloffFactor;				/**< This will scale the distance attenuation over the applicable range */
		PLMath::Vector3 m_vAttributes[NumOfAttributes];	/**< Source attributes */


	//[-------------------------------------------------------]
	//[ Public virtual PLSound::Source functions              ]
	//[-------------------------------------------------------]
	public:
		virtual bool Load(PLSound::Buffer *pBuffer = nullptr) override;
		virtual bool Play(bool bRestart = false) override;
		virtual bool IsPlaying() const override;
		virtual void Pause() override;
		virtual bool IsPaused() const override;
		virtual void Stop() override;
		virtual float GetVolume() const override;
		virtual void SetVolume(float fVolume = 1.0f) override;
		virtual bool Is2D() const override;
		virtual void Set2D(bool b2D = false) override;
		virtual bool IsLooping() const override;
		virtual void SetLooping(bool bLooping = false) override;
		virtual float GetPitch() const override;
		virtual void SetPitch(float fPitch = 1.0f) override;
		virtual float GetReferenceDistance() const override;
		virtual void SetReferenceDistance(float fReferenceDistance = 1.01f) override;
		virtual float GetMaxDistance() const override;
		virtual void SetMaxDistance(float fMaxDistance = 100000.0f) override;
		virtual float GetRolloffFactor() const override;
		virtual void SetRolloffFactor(float fRolloffFactor = 1.0f) override;
		virtual PLMath::Vector3 GetAttribute(EAttributes nAttribute) const override;
		virtual bool SetAttribute(EAttributes nAttribute, const PLMath::Vector3 &vV) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundNull


#endif // __PLSOUNDNULL_SOURCE_H__
