/*********************************************************\
 *  File: MessageFilterRocket.h                          *
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


#ifndef __LIBROCKET_PL_MESSAGEFILTER_H__
#define __LIBROCKET_PL_MESSAGEFILTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/HashMap.h>
#include <PLGui/Gui/Base/MessageFilter.h>
#include "libRocket_PL/libRocket_PL.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class Widget;
}
namespace Rocket {
	namespace Core {
		class Context;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Message filter that feeds PLGui messages into libRocket
*/
class MessageFilterRocket : public PLGui::MessageFilter {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRocketContext
		*    libRocket context to use, just shared, must stay valid as long as this message filter lives
		*  @param[in] pTargetWidget
		*    Message target widget, if null pointer, messages from all widgets are send to libRocket
		*/
		LIBROCKET_PL_API MessageFilterRocket(Rocket::Core::Context &cRocketContext, PLGui::Widget *pTargetWidget = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		LIBROCKET_PL_API virtual ~MessageFilterRocket();

		/**
		*  @brief
		*    Returns the used libRocket context
		*
		*  @return
		*    The used libRocket context
		*/
		LIBROCKET_PL_API Rocket::Core::Context &GetRocketContext() const;

		/**
		*  @brief
		*    Get message target widget
		*
		*  @return
		*    Message target widget, if null pointer, messages from all widgets are send to libRocket
		*/
		LIBROCKET_PL_API PLGui::Widget *GetTargetWidget() const;


	//[-------------------------------------------------------]
	//[ Protected virtual PLGui::MessageFilter functions      ]
	//[-------------------------------------------------------]
	protected:
		LIBROCKET_PL_API virtual void OnGuiMessage(const PLGui::GuiMessage &cMessage) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Builds the key maps
		*/
		void BuildKeyMaps();

		/**
		*  @brief
		*    Gets the libRocket key modifier state
		*
		*  @return
		*    The libRocket key modifier state
		*/
		int GetRocketKeyModifierState() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Rocket::Core::Context												*m_pRocketContext;		/**< libRocket context, always valid! */
		PLGui::Widget													  	*m_pTargetWidget;		/**< Message target widget, if null pointer, messages from all widgets are send to libRocket */
		PLCore::HashMap<PLCore::uint32, Rocket::Core::Input::KeyIdentifier>  m_mapKeyIdentifier;	/**< Key identifier map from PLGui-key to libRocket-key */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL


#endif // __LIBROCKET_PL_MESSAGEFILTER_H__
