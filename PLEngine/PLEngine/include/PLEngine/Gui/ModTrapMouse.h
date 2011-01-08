/*********************************************************\
 *  File: ModTrapMouse.h                                 *
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


#ifndef __PLENGINE_MODTRAPMOUSE_H__
#define __PLENGINE_MODTRAPMOUSE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Modifiers/Modifier.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Modifier which traps the mouse within the widget as soon as it gets active
*/
class ModTrapMouse : public PLGui::Modifier {


	//[-------------------------------------------------------]
	//[ Class definition                                      ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, ModTrapMouse, "PLEngine", PLGui::Modifier, "Modifier which traps the mouse within the widget as soon as it gets active")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PL_API ModTrapMouse();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~ModTrapMouse();


	//[-------------------------------------------------------]
	//[ Protected virtual PLGui::Modifier functions           ]
	//[-------------------------------------------------------]
	protected:
		PL_API virtual void OnAttach(PLGui::Widget &cWidget);
		PL_API virtual void OnDetach(PLGui::Widget &cWidget);


	//[-------------------------------------------------------]
	//[ Protected virtual PLGui::WidgetFunctions functions    ]
	//[-------------------------------------------------------]
	protected:
		PL_API virtual void OnActivate(bool bActivate);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_MODTRAPMOUSE_H__
