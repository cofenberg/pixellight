/*********************************************************\
 *  File: Modifier.h                                     *
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


#ifndef __PLGUI_MODIFIER_H__
#define __PLGUI_MODIFIER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLGui/Gui/Base/WidgetFunctions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Widget;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Modifier base class
*/
class Modifier : public PLCore::Object, public WidgetFunctions {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, Modifier, "PLGui", PLCore::Object, "Modifier base class")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Widget;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGUI_API Modifier();

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~Modifier();

		/**
		*  @brief
		*    Return the widget to which the modifier belongs
		*
		*  @return
		*    Widget that contains the modifier
		*/
		PLGUI_API Widget *GetWidget() const;

		/**
		*  @brief
		*    Get name of modifier
		*
		*  @return
		*    Name
		*/
		PLGUI_API PLGeneral::String GetName() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Set name of modifier
		*
		*  @param[in] sName
		*    Name
		*/
		PLGUI_API void SetName(const PLGeneral::String &sName);

		/**
		*  @brief
		*    Attach the modifier to a widget
		*
		*  @param[in] cWidget
		*    Widget to which the modifier is attached
		*/
		PLGUI_API void Attach(Widget &cWidget);

		/**
		*  @brief
		*    Detach the modifier
		*/
		PLGUI_API void Detach();


	//[-------------------------------------------------------]
	//[ Protected virtual Modifier functions                  ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when the modifier is attached to a widget
		*
		*  @param[in] cWidget
		*    Widget to which the modifier is attached
		*/
		virtual void OnAttach(Widget &cWidget);

		/**
		*  @brief
		*    Called when the modifier is detached from a widget
		*
		*  @param[in] cWidget
		*    Widget from which the modifier is detached
		*/
		virtual void OnDetach(Widget &cWidget);


	//[-------------------------------------------------------]
	//[ Protected virtual WidgetFunctions functions           ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API virtual void OnMessage(const GuiMessage &cMessage);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Widget			  *m_pWidget;	/**< Widget to which the modifier belongs */
		PLGeneral::String  m_sName;		/**< Name of modifier */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_MODIFIER_H__
