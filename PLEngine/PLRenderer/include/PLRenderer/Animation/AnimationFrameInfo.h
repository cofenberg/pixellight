/*********************************************************\
 *  File: AnimationFrameInfo.h                           *
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


#ifndef __PLRENDERER_ANIMATIONFRAMEINFO_H__
#define __PLRENDERER_ANIMATIONFRAMEINFO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Animation frame information
*/
class AnimationFrameInfo {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLRENDERER_API AnimationFrameInfo();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API ~AnimationFrameInfo();

		/**
		*  @brief
		*    Returns the speed of an animation frame
		*
		*  @return
		*    Animation frame speed
		*
		*  @note
		*    - If speed is 0 the frame will be skipped
		*    - If speed is less 0 there's no frame interpolation
		*/
		PLRENDERER_API float GetSpeed() const;

		/**
		*  @brief
		*    Sets the animation frame speed
		*
		*  @param[in] fSpeed
		*    Animation frame speed
		*
		*  @see
		*    - GetSpeed()
		*/
		PLRENDERER_API void SetSpeed(float fSpeed = 1.0f);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this class instance
		*/
		PLRENDERER_API AnimationFrameInfo &operator =(const AnimationFrameInfo &cSource);

		/**
		*  @brief
		*    Compare operator
		*
		*  @param[in] cSource
		*    Source to compare with
		*
		*  @return
		*    'true' if the two animation frame information are equal, else 'false'
		*/
		PLRENDERER_API bool operator ==(const AnimationFrameInfo &cSource) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fSpeed;	/**< Frame speed */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_ANIMATIONFRAMEINFO_H__
