/*********************************************************\
 *  File: Dialog.h                                       *
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


#ifndef __PLGUI_DIALOG_H__
#define __PLGUI_DIALOG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/Event.h>
#include "PLGui/Widgets/Windows/Window.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Base class for dialog windows
*/
class Dialog : public Window {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PLGUI_RTTI_EXPORT, Dialog, "PLGui", PLGui::Widget, "Base class for dialog windows")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public events                                         ]
	//[-------------------------------------------------------]
	public:
		PLCore::Event<>		EventShowDialog;	/**< Dialog is shown */
		PLCore::Event<int>	EventCloseDialog;	/**< Dialog is closed */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Pointer to parent widget
		*/
		PLGUI_API Dialog(Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API virtual ~Dialog();

		/**
		*  @brief
		*    Show dialog
		*/
		PLGUI_API void ShowDialog();

		/**
		*  @brief
		*    Close dialog
		*
		*  @param[in] nResult
		*    Result value
		*/
		PLGUI_API void CloseDialog(int nResult = 0);

		/**
		*  @brief
		*    Get result value
		*
		*  @return
		*    Result value
		*/
		PLGUI_API int GetResult() const;


	//[-------------------------------------------------------]
	//[ Protected virtual Widget functions                    ]
	//[-------------------------------------------------------]
	protected:
		PLGUI_API virtual void OnClose();


	//[-------------------------------------------------------]
	//[ Public virtual Dialog functions                       ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Called when dialog has been closed
		*
		*  @param[in] nResult
		*    Result value
		*/
		PLGUI_API virtual void OnCloseDialog(int nResult);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int m_nResult;	/**< Result value */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_DIALOG_H__
