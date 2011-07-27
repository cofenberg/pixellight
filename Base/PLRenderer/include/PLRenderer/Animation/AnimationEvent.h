/*********************************************************\
 *  File: AnimationEvent.h                               *
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


#ifndef __PLRENDERER_ANIMATIONEVENT_H__
#define __PLRENDERER_ANIMATIONEVENT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/Element.h>
#include <PLCore/Container/ElementManager.h>
#include "PLRenderer/PLRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class AnimationEventManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Animation event
*/
class AnimationEvent : public PLCore::Element<AnimationEvent> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nID
		*    Event ID
		*  @param[in] nFrame
		*    Frame causing this event
		*  @param[in] pManager
		*    Event manager using this element, can be a null pointer
		*  @param[in] sName
		*    Name of the event, if empty, a default name is set automatically
		*
		*  @note
		*    - If you provide the pointer to the owner manager the animation
		*      event will check in the animation event manager name list
		*/
		PLRENDERER_API AnimationEvent(int nID, PLCore::uint32 nFrame, AnimationEventManager *pManager = nullptr, const PLCore::String &sName = "");

		/**
		*  @brief
		*    Returns the event ID
		*
		*  @return
		*    Event ID
		*/
		PLRENDERER_API int GetID() const;

		/**
		*  @brief
		*    Sets the event ID
		*
		*  @param[in] nID
		*    Event ID
		*/
		PLRENDERER_API void SetID(int nID);

		/**
		*  @brief
		*    Returns the frame which will cause this event
		*
		*  @return
		*    The frame which will cause this event
		*/
		PLRENDERER_API PLCore::uint32 GetFrame() const;

		/**
		*  @brief
		*    Sets the frame causing this event
		*
		*  @param[in] nFrame
		*    Frame causing this event
		*/
		PLRENDERER_API void SetFrame(PLCore::uint32 nFrame);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int			   m_nID;		/**< Event ID */
		PLCore::uint32 m_nFrame;	/**< Frame causing this event */


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Element functions              ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual AnimationEvent &operator =(const AnimationEvent &cSource);


};

/**
*  @brief
*    Animation event manager
*/
class AnimationEventManager : public PLCore::ElementManager<AnimationEvent> {


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::ElementManager functions      ]
	//[-------------------------------------------------------]
	private:
		virtual AnimationEvent *CreateElement(const PLCore::String &sName) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_ANIMATIONEVENT_H__
