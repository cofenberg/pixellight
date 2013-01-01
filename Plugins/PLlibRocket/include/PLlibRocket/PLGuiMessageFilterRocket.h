/*********************************************************\
 *  File: PLGuiMessageFilterRocket.h                     *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLLIBROCKET_PLGUIMESSAGEFILTER_H__
#define __PLLIBROCKET_PLGUIMESSAGEFILTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/HashMap.h>
#include <PLGui/Gui/Base/MessageFilter.h>


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
namespace PLlibRocket {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Message filter that feeds PLGui messages into libRocket
*/
class PLGuiMessageFilterRocket : public PLGui::MessageFilter {


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
		PLGuiMessageFilterRocket(Rocket::Core::Context &cRocketContext, PLGui::Widget *pTargetWidget = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLGuiMessageFilterRocket();

		/**
		*  @brief
		*    Returns the used libRocket context
		*
		*  @return
		*    The used libRocket context
		*/
		Rocket::Core::Context &GetRocketContext() const;

		/**
		*  @brief
		*    Get message target widget
		*
		*  @return
		*    Message target widget, if null pointer, messages from all widgets are send to libRocket
		*/
		PLGui::Widget *GetTargetWidget() const;


	//[-------------------------------------------------------]
	//[ Protected virtual PLGui::MessageFilter functions      ]
	//[-------------------------------------------------------]
	protected:
		virtual void OnGuiMessage(const PLGui::GuiMessage &cMessage) override;


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
} // PLlibRocket


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLlibRocket/PLGuiMessageFilterRocket.inl"


#endif // __PLLIBROCKET_PLGUIMESSAGEFILTER_H__
