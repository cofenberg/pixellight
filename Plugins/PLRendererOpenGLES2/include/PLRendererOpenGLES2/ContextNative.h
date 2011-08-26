/*********************************************************\
 *  File: ContextNative.h                                *
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


#ifndef __PLRENDEREROPENGLES2_CONTEXTNATIVE_H__
#define __PLRENDEREROPENGLES2_CONTEXTNATIVE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRendererOpenGLES2/Context.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES native context
*
*  @remarks
*    Implementation for OpenGL ES 2.0 on mobile devices.
*/
class ContextNative : public Context {


	//[-------------------------------------------------------]
	//[ Public methods                                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    The owner renderer
		*/
		ContextNative(Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ContextNative();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_CONTEXTNATIVE_H__
