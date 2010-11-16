/*********************************************************\
 *  File: SceneRendererTool.h                            *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLENGINE_SCENERENDERERTOOL_H__
#define __PLENGINE_SCENERENDERERTOOL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class SurfacePainter;
}
namespace PLScene {
	class SceneRendererPass;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class offering scene renderer tool functionality
*
*  @remarks
*    Use this class for a simplified interface to the scene renderer. By writing for example
*    "SetPassAttribute("BackgroundBitmap", "Material", "Data/Textures/Background.dds");"
*    one can usually (on standard scene renderer configurations) set directly a background bitmap.
*/
class SceneRendererTool {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pPainter
		*    Surface painter
		*/
		PL_API SceneRendererTool(PLRenderer::SurfacePainter *pPainter = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SceneRendererTool();

		/**
		*  @brief
		*    Get surface painter
		*
		*  @return
		*    Surface painter used to access scene renderer functionality, can be NULL
		*/
		PL_API PLRenderer::SurfacePainter *GetPainter() const;

		/**
		*  @brief
		*    Set surface painter
		*
		*  @param[in] pSurfacePainter
		*    Surface painter used to access scene renderer functionality, can be NULL
		*/
		PL_API void SetPainter(PLRenderer::SurfacePainter *pSurfacePainter);

		/**
		*  @brief
		*    Gets a scene renderer pass
		*
		*  @param[in] sName
		*    Name of the scene renderer pass to return
		*
		*  @return
		*    The requested scene renderer pass, NULL on error
		*/
		PL_API PLScene::SceneRendererPass *GetPass(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Gets a scene renderer pass attribute value as string
		*
		*  @param[in] sSceneRendererPassName
		*    Name of the scene renderer pass
		*  @param[in] sAttributeName
		*    Name of the scene renderer pass attribute
		*
		*  @return
		*    The requested scene renderer pass attribute as string
		*/
		PL_API PLGeneral::String GetPassAttribute(const PLGeneral::String &sSceneRendererPassName, const PLGeneral::String &sAttributeName) const;

		/**
		*  @brief
		*    Sets a scene renderer pass attribute value using a string
		*
		*  @param[in] sSceneRendererPassName
		*    Name of the scene renderer pass
		*  @param[in] sAttributeName
		*    Name of the scene renderer pass attribute
		*  @param[in] sValue
		*    Value to set
		*
		*  @return
		*    'true' if the attribute was set, else 'false'
		*/
		PL_API bool SetPassAttribute(const PLGeneral::String &sSceneRendererPassName, const PLGeneral::String &sAttributeName, const PLGeneral::String &sValue) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::SurfacePainter	*m_pSurfacePainter;	/**< Used surface painter, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCENERENDERERTOOL_H__
