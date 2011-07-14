/*********************************************************\
 *  File: GuiMessage.h                                   *
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


#ifndef __PLGUI_GUIMESSAGE_H__
#define __PLGUI_GUIMESSAGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
#include <PLMath/Vector2i.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Widget;
class Graphics;
class DataObject;
class Timer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GUI message/event
*/
class GuiMessage {


	//[-------------------------------------------------------]
	//[ Public named constructors                             ]
	//[-------------------------------------------------------]
	public:
		PLGUI_API static GuiMessage OnWakeup();
		PLGUI_API static GuiMessage OnExit();
		PLGUI_API static GuiMessage OnTimer(Timer *pTimer);
		PLGUI_API static GuiMessage OnUserMessage(Widget *pWidget, PLGeneral::uint32 nData, void *pData);
		PLGUI_API static GuiMessage OnInternalMessage(PLGeneral::uint32 nData, PLGeneral::uint32 nExtData);
		PLGUI_API static GuiMessage OnThemeChanged(Widget *pWidget);
		PLGUI_API static GuiMessage OnUpdateContent(Widget *pWidget);
		PLGUI_API static GuiMessage OnUpdateChildWidget(Widget *pWidget, Widget *pChildWidget);
		PLGUI_API static GuiMessage OnAddChildWidget(Widget *pWidget, Widget *pChildWidget);
		PLGUI_API static GuiMessage OnRemoveChildWidget(Widget *pWidget, Widget *pChildWidget);
		PLGUI_API static GuiMessage OnClose(Widget *pWidget);
		PLGUI_API static GuiMessage OnCreate(Widget *pWidget);
		PLGUI_API static GuiMessage OnDestroy(Widget *pWidget);
		PLGUI_API static GuiMessage OnShow(Widget *pWidget);
		PLGUI_API static GuiMessage OnHide(Widget *pWidget);
		PLGUI_API static GuiMessage OnEnable(Widget *pWidget);
		PLGUI_API static GuiMessage OnDisable(Widget *pWidget);
		PLGUI_API static GuiMessage OnGetFocus(Widget *pWidget);
		PLGUI_API static GuiMessage OnLooseFocus(Widget *pWidget);
		PLGUI_API static GuiMessage OnActivate(Widget *pWidget, bool bActivate);
		PLGUI_API static GuiMessage OnDrawBackground(Widget *pWidget, Graphics *pGraphics);
		PLGUI_API static GuiMessage OnDraw(Widget *pWidget, Graphics *pGraphics);
		PLGUI_API static GuiMessage OnMove(Widget *pWidget, const PLMath::Vector2i &vPos);
		PLGUI_API static GuiMessage OnSize(Widget *pWidget, const PLMath::Vector2i &vSize);
		PLGUI_API static GuiMessage OnWindowState(Widget *pWidget, EWindowState nWindowState);
		PLGUI_API static GuiMessage OnEnterFullscreen(Widget *pWidget);
		PLGUI_API static GuiMessage OnLeaveFullscreen(Widget *pWidget);
		PLGUI_API static GuiMessage OnPreferredSize(Widget *pWidget, const PLMath::Vector2i &vSize);
		PLGUI_API static GuiMessage OnAdjustContent(Widget *pWidget);
		PLGUI_API static GuiMessage OnMouseEnter(Widget *pWidget);
		PLGUI_API static GuiMessage OnMouseLeave(Widget *pWidget);
		PLGUI_API static GuiMessage OnMouseOver(Widget *pWidget, bool bMouseOver);
		PLGUI_API static GuiMessage OnMouseMove(Widget *pWidget, const PLMath::Vector2i &vPos);
		PLGUI_API static GuiMessage OnMouseHover(Widget *pWidget);
		PLGUI_API static GuiMessage OnMousePosUpdate(Widget *pWidget, const PLMath::Vector2i &vPos);
		PLGUI_API static GuiMessage OnMouseButtonDown(Widget *pWidget, EMouseButton nButton, const PLMath::Vector2i &vPos);
		PLGUI_API static GuiMessage OnMouseButtonUp(Widget *pWidget, EMouseButton nButton, const PLMath::Vector2i &vPos);
		PLGUI_API static GuiMessage OnMouseButtonClick(Widget *pWidget, EMouseButton nButton, const PLMath::Vector2i &vPos);
		PLGUI_API static GuiMessage OnMouseButtonDoubleClick(Widget *pWidget, EMouseButton nButton, const PLMath::Vector2i &vPos);
		PLGUI_API static GuiMessage OnMouseWheel(Widget *pWidget, int nDelta);
		PLGUI_API static GuiMessage OnKeyDown(Widget *pWidget, PLGeneral::uint32 nKey, PLGeneral::uint32 nModifiers);
		PLGUI_API static GuiMessage OnKeyUp(Widget *pWidget, PLGeneral::uint32 nKey, PLGeneral::uint32 nModifiers);
		PLGUI_API static GuiMessage OnHotkey(Widget *pWidget, PLGeneral::uint32 nHotkey);
		PLGUI_API static GuiMessage OnDrop(Widget *pWidget, DataObject *pDataObject);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pWidget
		*    Message target
		*  @param[in] nType
		*    Message type
		*/
		PLGUI_API GuiMessage(Widget *pWidget = nullptr, EMessageType nType = MessageOnUnknown);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cOther
		*    GUI message
		*/
		PLGUI_API GuiMessage(const GuiMessage &cOther);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API ~GuiMessage();

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cOther
		*    GUI message
		*
		*  @return
		*    'true' if equal, else 'false'
		*/
		PLGUI_API bool operator ==(const GuiMessage &cOther) const;

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cOther
		*    GUI message
		*
		*  @return
		*    Reference to this object
		*/
		PLGUI_API GuiMessage &operator =(const GuiMessage &cOther);

		/**
		*  @brief
		*    Get message representation as string
		*
		*  @return
		*    Message as string
		*/
		PLGUI_API PLGeneral::String ToString() const;

		/**
		*  @brief
		*    Get message target
		*
		*  @return
		*    Widget
		*/
		inline Widget *GetWidget() const {
			return m_pWidget;
		}

		/**
		*  @brief
		*    Get message type
		*
		*  @return
		*    Message type
		*/
		inline EMessageType GetType() const {
			return m_nType;
		}

		/**
		*  @brief
		*    Get message data
		*
		*  @return
		*    Message data
		*/
		inline PLGeneral::uint32 GetData() const {
			return m_nData;
		}

		/**
		*  @brief
		*    Get delta
		*
		*  @return
		*    Delta value
		*/
		inline int GetDelta() const {
			return m_nDelta;
		}

		/**
		*  @brief
		*    Get window state
		*
		*  @return
		*    Window state
		*/
		inline EWindowState GetWindowState() const {
			return m_nWindowState;
		}

		/**
		*  @brief
		*    Get mouse button
		*
		*  @return
		*    Mouse button
		*/
		inline EMouseButton GetMouseButton() const {
			return m_nMouseButton;
		}

		/**
		*  @brief
		*    Get key
		*
		*  @return
		*    Key
		*/
		inline PLGeneral::uint32 GetKey() const {
			return m_nKey;
		}

		/**
		*  @brief
		*    Get boolean state
		*
		*  @return
		*    State
		*/
		inline bool GetState() const {
			return m_bState;
		}

		/**
		*  @brief
		*    Get data pointer
		*
		*  @return
		*    Data pointer
		*/
		inline void *GetDataPointer() const {
			return m_pDataPtr;
		}

		/**
		*  @brief
		*    Get secondary data
		*
		*  @return
		*    Message data
		*/
		inline PLGeneral::uint32 GetExtData() const {
			return m_nExtData;
		}

		/**
		*  @brief
		*    Get data object
		*
		*  @return
		*    Data pointer
		*/
		inline DataObject *GetDataObject() const {
			return m_pDataObject;
		}

		/**
		*  @brief
		*    Get child widget
		*
		*  @return
		*    Widget
		*/
		inline Widget *GetChildWidget() const {
			return m_pChildWidget;
		}

		/**
		*  @brief
		*    Get graphics object
		*
		*  @return
		*    Graphics object
		*/
		inline Graphics *GetGraphics() const {
			return m_pGraphics;
		}

		/**
		*  @brief
		*    Get timer object
		*
		*  @return
		*    Timer object
		*/
		inline Timer *GetTimer() const {
			return m_pTimer;
		}

		/**
		*  @brief
		*    Get modifier keys
		*
		*  @return
		*    Modifiers
		*/
		inline const PLGeneral::uint32 GetModifiers() const {
			return m_nModifiers;
		}

		/**
		*  @brief
		*    Get position or size
		*
		*  @return
		*    Vector
		*/
		inline const PLMath::Vector2i &GetPosSize() const {
			return m_vPosSize;
		}


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Message target
		Widget					*m_pWidget;			/**< Widget */

		// Message type
		EMessageType			 m_nType;			/**< Message type */

		// First message data
		union {
			PLGeneral::uint32	 m_nData;			/**< Message data */
			int					 m_nDelta;			/**< Movement delta */
			EWindowState		 m_nWindowState;	/**< Window state */
			EMouseButton		 m_nMouseButton;	/**< Mouse button */
			PLGeneral::uint32	 m_nKey;			/**< Key code */
			bool				 m_bState;			/**< Boolean state */
		};

		// Second message data
		union {
			void				*m_pDataPtr;		/**< Message data pointer */
			PLGeneral::uint32	 m_nExtData;		/**< Secondary data */
			DataObject			*m_pDataObject;		/**< Data object */
			Widget				*m_pChildWidget;	/**< Child widget */
			Graphics			*m_pGraphics;		/**< Graphics object */
			Timer				*m_pTimer;			/**< Timer object */
			PLGeneral::uint32	 m_nModifiers;		/**< Key modifiers */
		};

		// Position or size data
		PLMath::Vector2i		 m_vPosSize;		/**< Position or size */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_GUIMESSAGE_H__
