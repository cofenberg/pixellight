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


#ifndef __PLSOUNDNULL_SOUNDMANAGER_H__
#define __PLSOUNDNULL_SOUNDMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLSound/SoundManager.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLSoundNull {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Null sound backend
*/
class SoundManager : public PLSound::SoundManager {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SoundManager, "PLSoundNull", PLSound::SoundManager, "Null sound backend")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SoundManager();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SoundManager();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float			m_fVolume;							   /**< Master volume */
		float			m_fPitch;							   /**< Master pitch */
		float			m_fDopplerFactor;					   /**< Doppler factor */
		PLMath::Vector3 m_vListenerAttributes[ListenerNumber]; /**< Listener attributes */


	//[-------------------------------------------------------]
	//[ Public virtual PLSound::SoundManager functions        ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetDescription() const;
		virtual bool GetFormatList(PLGeneral::List<Format> &lstList) const;
		virtual float GetVolume() const;
		virtual void SetVolume(float fVolume = 1.0f);
		virtual float GetPitch() const;
		virtual void SetPitch(float fPitch = 1.0f);
		virtual float GetDopplerFactor() const;
		virtual void SetDopplerFactor(float fFactor = 1.0f);

		//[-------------------------------------------------------]
		//[ Create sound buffer/source                            ]
		//[-------------------------------------------------------]
		virtual PLSound::Buffer *CreateSoundBuffer(const PLGeneral::String &sFilename = "", bool bStream = false);
		virtual PLSound::Source *CreateSoundSource(PLSound::Buffer *pSoundBuffer = nullptr);

		//[-------------------------------------------------------]
		//[ Listener                                              ]
		//[-------------------------------------------------------]
		virtual PLMath::Vector3 GetListenerAttribute(EListener nAttribute) const;
		virtual bool SetListenerAttribute(EListener nAttribute, const PLMath::Vector3 &vV);


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::ResourceManager functions      ]
	//[-------------------------------------------------------]
	public:
		virtual bool Init();
		virtual bool DeInit();
		virtual bool Update();


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ResourceManager functions     ]
	//[-------------------------------------------------------]
	private:
		virtual PLSound::Buffer *CreateResource(const PLGeneral::String &sName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLSoundNull


#endif // __PLSOUNDNULL_SOUNDMANAGER_H__
