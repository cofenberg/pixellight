/*********************************************************\
 *  File: RenderWidget.h                                 *
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


#ifndef __PLENGINE_RENDERWIDGET_H__
#define __PLENGINE_RENDERWIDGET_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Widgets/Widget.h>
#include "PLEngine/Gui/WindowConnection.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GUI widget with implements a renderer surface
*
*  @remarks
*    Use 'RenderWidget' to create a widget which automatically
*    implements a renderer surface handler and creates the window surface.
*/
class RenderWidget : public PLGui::Widget, public WindowConnection {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, RenderWidget, "PLEngine", PLGui::Widget, "GUI widget with implements a renderer surface")
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
		*  @param[in] pDisplayMode
		*    Display mode information, can be a null pointer
		*/
		PL_API RenderWidget(PLRenderer::Renderer &cRenderer, PLGui::Widget *pParent = nullptr, const PLRenderer::DisplayMode *pDisplayMode = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~RenderWidget();


	//[-------------------------------------------------------]
	//[ Protected virtual WindowConnection functions          ]
	//[-------------------------------------------------------]
	protected:
		PL_API virtual void OnDisplayMode() override;
		PL_API virtual void OnFullscreenMode() override;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PL_API RenderWidget(const RenderWidget &cSource);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
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
		RenderWidget &operator =(const RenderWidget &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool			 m_bBackupAvailable;
		PLMath::Vector2i m_vBackupPos;
		PLMath::Vector2i m_vBackupSize;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_RENDERWIDGET_H__
