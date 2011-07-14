/*********************************************************\
 *  File: PreviewWidget.h                                *
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


#ifndef __PLENGINE_PREVIEWWIDGET_H__
#define __PLENGINE_PREVIEWWIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/Gui/RenderWidget.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GUI renderer preview widget
*
*  @note
*    - Hold down the left mouse button to pan
*    - Hold down the right mouse button to zoom
*/
class PreviewWidget : public RenderWidget {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, PreviewWidget, "PLEngine", PLEngine::RenderWidget, "GUI renderer preview widget")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] pParent
		*    Parent widget, can be a null pointer
		*/
		PL_API PreviewWidget(PLRenderer::Renderer &cRenderer, PLGui::Widget *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~PreviewWidget();

		/**
		*  @brief
		*    Resets the view
		*/
		PL_API void ResetView();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PreviewWidget(const PreviewWidget &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PreviewWidget &operator =(const PreviewWidget &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool			  m_bLeftMouseButtonPressed;	/**< The left mouse button is currently pressed */
		bool			  m_bRightMouseButtonPressed;	/**< The right mouse button is currently pressed */
		PLMath::Vector2i  m_vPreviousMousePosition;		/**< Previous mouse position */


	//[-------------------------------------------------------]
	//[ Public virtual PLGui::Widget functions                ]
	//[-------------------------------------------------------]
	public:
		virtual void OnMouseMove(const PLMath::Vector2i &vPos);
		virtual void OnMouseButtonDown(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);
		virtual void OnMouseButtonUp(PLGeneral::uint32 nButton, const PLMath::Vector2i &vPos);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_PREVIEWWIDGET_H__
