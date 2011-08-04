/*********************************************************\
 *  File: FrontendOpenGL.h                               *
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


#ifndef __PLCORE_FRONTEND_OPENGL_H__
#define __PLCORE_FRONTEND_OPENGL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Frontend/Frontend.h"
#ifdef WIN32
	#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Simple test frontend that uses OpenGL
*
*  @remarks
*    This is a test frontend which uses OpenGL to display a spinning colored
*    rectangle. It can be used easily to test the frontend integration when
*    developing a new backend.
*/
class FrontendOpenGL : public Frontend {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cImpl
		*    Implementation object
		*/
		PLCORE_API FrontendOpenGL(FrontendImpl &cImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~FrontendOpenGL();


	//[-------------------------------------------------------]
	//[ Public virtual FrontendFrontend functions             ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API virtual bool IsRunning() const override;


	//[-------------------------------------------------------]
	//[ Private virtual FrontendFrontend functions            ]
	//[-------------------------------------------------------]
	private:
		PLCORE_API virtual void OnDraw() override;
		PLCORE_API virtual void OnSize() override;


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractLifecycle functions         ]
	//[-------------------------------------------------------]
	protected:
		PLCORE_API virtual void OnCreate() override;
		PLCORE_API virtual void OnRestart() override;
		PLCORE_API virtual void OnStart() override;
		PLCORE_API virtual void OnResume() override;
		PLCORE_API virtual void OnPause() override;
		PLCORE_API virtual void OnStop() override;
		PLCORE_API virtual void OnDestroy() override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Initialize OpenGL
		*/
		void InitGL();

		/**
		*  @brief
		*    Resize GL scene to fit the current window size
		*/
		void ResizeGL();

		/**
		*  @brief
		*    Draw scene
		*/
		void DrawGL();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Platform specific
		#ifdef WIN32
			HDC   m_hDC;	/**< Device context, can be a null pointer */
			HGLRC m_hRC;	/**< OpenGL rendering context, can be a null pointer */
		#endif

		// Platform independent
		float m_fAngle;	/**< Current rotation angle of the rectangle */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_FRONTEND_OPENGL_H__
