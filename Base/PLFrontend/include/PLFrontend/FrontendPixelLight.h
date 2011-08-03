/*********************************************************\
 *  File: FrontendPixelLight.h                           *
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


#ifndef __PLFRONTEND_FRONTEND_PIXELLIGHT_H__
#define __PLFRONTEND_FRONTEND_PIXELLIGHT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontend/Frontend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontend {


//[-------------------------------------------------------]
//[ Forward declaration                                   ]
//[-------------------------------------------------------]
class FrontendApplication;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight frontend
*/
class FrontendPixelLight : public Frontend {


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
		PLFRONTEND_API FrontendPixelLight(FrontendImpl &cImpl);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTEND_API virtual ~FrontendPixelLight();


	//[-------------------------------------------------------]
	//[ Public virtual FrontendFrontend functions             ]
	//[-------------------------------------------------------]
	public:
		PLFRONTEND_API virtual bool IsRunning() const override;


	//[-------------------------------------------------------]
	//[ Private virtual FrontendFrontend functions            ]
	//[-------------------------------------------------------]
	private:
		PLFRONTEND_API virtual void OnDraw() override;
		PLFRONTEND_API virtual void OnSize() override;


	//[-------------------------------------------------------]
	//[ Protected virtual AbstractFrontendLifecycle functions ]
	//[-------------------------------------------------------]
	protected:
		PLFRONTEND_API virtual void OnCreate() override;
		PLFRONTEND_API virtual void OnRestart() override;
		PLFRONTEND_API virtual void OnStart() override;
		PLFRONTEND_API virtual void OnResume() override;
		PLFRONTEND_API virtual void OnPause() override;
		PLFRONTEND_API virtual void OnStop() override;
		PLFRONTEND_API virtual void OnDestroy() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FrontendApplication *m_pFrontendApplication;			/**< Frontend application instance, can be a null pointer */
		bool				 m_bFrontendApplicationInitialized;	/**< Frontend application successfully initialized? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontend


#endif // __PLFRONTEND_FRONTEND_PIXELLIGHT_H__
