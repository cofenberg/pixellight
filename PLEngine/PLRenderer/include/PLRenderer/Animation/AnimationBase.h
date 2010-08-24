/*********************************************************\
 *  File: AnimationBase.h                                *
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


#ifndef __PLRENDERER_ANIMATIONBASE_H__
#define __PLRENDERER_ANIMATIONBASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Animation/AnimationInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Animation base class
*/
class AnimationBase : public AnimationInfo {


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Animation frame keys
		*/
		class FrameKeys {


			//[-------------------------------------------------------]
			//[ Public data                                           ]
			//[-------------------------------------------------------]
			public:
				PLGeneral::Array<float> lstFrameKeys;


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				PLRENDERER_API bool operator ==(const FrameKeys &cKeys) const
				{
					return lstFrameKeys == cKeys.lstFrameKeys;
				}


		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API AnimationBase();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~AnimationBase();

		/**
		*  @brief
		*    Returns the frame rate
		*
		*  @return
		*    Frames per second
		*/
		PLRENDERER_API float GetFrameRate() const;

		/**
		*  @brief
		*    Sets the frame rate
		*
		*  @param[in] fFrameRate
		*    Frames per second
		*/
		PLRENDERER_API void SetFrameRate(float fFrameRate = 24.0f);

		/**
		*  @brief
		*    Returns the frame keys
		*
		*  @return
		*    Frame keys
		*/
		PLRENDERER_API PLGeneral::Array<FrameKeys> &GetFrameKeys();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		float						m_fFrameRate;	/**< Frame rate */
		PLGeneral::Array<FrameKeys> m_lstFrameKeys;	/**< Frame keys */


	//[-------------------------------------------------------]
	//[ Public virtual AnimationInfo functions                ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual AnimationBase &operator =(const AnimationBase &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_ANIMATIONBASE_H__
