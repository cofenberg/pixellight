/*********************************************************\
 *  File: SceneRendererTool.h                            *
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


#ifndef __PLENGINE_SCENERENDERERTOOL_H__
#define __PLENGINE_SCENERENDERERTOOL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Object.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class SurfacePainter;
}
namespace PLScene {
	class SceneRenderer;
	class SceneContainer;
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
class SceneRendererTool : public PLCore::Object {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SceneRendererTool, "PLEngine", PLCore::Object, "Class offering scene renderer tool functionality")
		// Methods
		pl_method_3(SetSceneRenderer,	pl_ret_type(bool),							PLScene::SceneContainer*,	const PLGeneral::String&,	const PLGeneral::String&,	"Sets the used scene renderer, scene container to render as first parameter, filename of the scene renderer to use as second parameter, optional filename of a fallback scene renderer to use in case the desired scene renderer can't be used as third parameter. Returns 'true' if all went fine, else 'false'.",									"")
		pl_method_0(GetNumOfPasses,		pl_ret_type(PLGeneral::uint32),																									"Returns the number of scene renderer passes",																																																																										"")
		pl_method_1(GetPassByIndex,		pl_ret_type(PLScene::SceneRendererPass*),	PLGeneral::uint32,																	"Gets a scene renderer pass by index. Index of the scene renderer pass to return as first parameter. The requested scene renderer pass as result, a null pointer on error.",																																										"")
		pl_method_1(GetPassByName,		pl_ret_type(PLScene::SceneRendererPass*),	const PLGeneral::String&,															"Gets a scene renderer pass by name. Name of the scene renderer pass to return as first parameter. The requested scene renderer pass as result, a null pointer on error.",																																											"")
		pl_method_3(SetPassAttribute,	pl_ret_type(bool),							const PLGeneral::String&,	const PLGeneral::String&,	const PLGeneral::String&,	"Sets a scene renderer pass attribute value using a string, name of the scene renderer pass as first parameter, name of the scene renderer pass attribute as second parameter and value to set as third parameter",																																	"")
		pl_method_2(SetAttribute,		pl_ret_type(PLGeneral::uint32),				const PLGeneral::String&,	const PLGeneral::String&,								"Sets scene renderer pass attribute values using a string. Name of the scene renderer pass attribute (e.g. \"AmbientColor\") as first parameter, value to set (e.g. \"0.2 0.2 0.2\") as second parameter. Unlike \"SetPassAttribute()\", \"SetAttribute()\" sets the <AttributeName>-attribute from all scene renderer passes to the given value.",	"")
		pl_method_1(SetValues,			pl_ret_type(void),							const PLGeneral::String&,															"Values to set (e.g.: \"ColorClear=\"0 0 0 0\" AmbientColor=\"0.2 0.2 0.2\"\") as first parameter. Unlike \"SetPassAttribute()\" and \"SetAttribute()\", \"SetValues()\" sets multiple attributes from all scene renderer passes to the given value at once.",																						"")
		pl_method_0(SetDefaultValues,	pl_ret_type(void),																												"Sets all scene renderer pass attribute values to their default value",																																																																				"")
	pl_class_end


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
		PL_API SceneRendererTool(PLRenderer::SurfacePainter *pPainter = nullptr);

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
		*    Surface painter used to access scene renderer functionality, can be a null pointer
		*/
		PL_API PLRenderer::SurfacePainter *GetPainter() const;

		/**
		*  @brief
		*    Set surface painter
		*
		*  @param[in] pSurfacePainter
		*    Surface painter used to access scene renderer functionality, can be a null pointer
		*/
		PL_API void SetPainter(PLRenderer::SurfacePainter *pSurfacePainter);

		/**
		*  @brief
		*    Returns the used scene renderer instance
		*
		*  @return
		*    The used scene renderer instance, can be a null pointer
		*
		*  @note
		*    - Same as "SceneRenderer *pSceneRenderer = ((SPScene*)GetPainter())->GetDefaultSceneRenderer()" (with security checks!)
		*/
		PL_API PLScene::SceneRenderer *GetSceneRenderer() const;

		/**
		*  @brief
		*    Sets the used scene renderer
		*
		*  @param[in] pSceneContainer
		*    Scene container to render, if null, this method will return an error
		*  @param[in] sFilename
		*    Filename of the scene renderer to use
		*  @param[in] sFallbackFilename
		*    Optional filename of a fallback scene renderer to use in case the desired scene renderer can't be used
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PL_API bool SetSceneRenderer(PLScene::SceneContainer *pSceneContainer, const PLGeneral::String &sFilename, const PLGeneral::String &sFallbackFilename = "");

		/**
		*  @brief
		*    Returns the number of scene renderer passes
		*
		*  @return
		*    The number of scene renderer passes
		*/
		PL_API PLGeneral::uint32 GetNumOfPasses() const;

		/**
		*  @brief
		*    Gets a scene renderer pass by index
		*
		*  @param[in] nIndex
		*    Index of the scene renderer pass to return
		*
		*  @return
		*    The requested scene renderer pass, a null pointer on error
		*/
		PL_API PLScene::SceneRendererPass *GetPassByIndex(PLGeneral::uint32 nIndex) const;

		/**
		*  @brief
		*    Gets a scene renderer pass by name
		*
		*  @param[in] sName
		*    Name of the scene renderer pass to return
		*
		*  @return
		*    The requested scene renderer pass, a null pointer on error
		*/
		PL_API PLScene::SceneRendererPass *GetPassByName(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Gets a scene renderer pass attribute
		*
		*  @param[in] sSceneRendererPassName
		*    Name of the scene renderer pass
		*  @param[in] sAttributeName
		*    Name of the scene renderer pass attribute
		*
		*  @return
		*    The requested scene renderer pass attribute, a null pointer on error
		*/
		PL_API PLCore::DynVar *GetPassAttribute(const PLGeneral::String &sSceneRendererPassName, const PLGeneral::String &sAttributeName) const;

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

		/**
		*  @brief
		*    Sets scene renderer pass attribute values using a string
		*
		*  @param[in] sAttributeName
		*    Name of the scene renderer pass attribute (e.g. "AmbientColor")
		*  @param[in] sValue
		*    Value to set (e.g. "0.2 0.2 0.2")
		*
		*  @return
		*    Number of set scene renderer pass attribute values
		*
		*  @remarks
		*    Unlike "SetPassAttribute()", "SetAttribute()" sets the "sAttributeName"-attribute from all
		*    scene renderer passes to the given value.
		*/
		PL_API PLGeneral::uint32 SetAttribute(const PLGeneral::String &sAttributeName, const PLGeneral::String &sValue) const;

		/**
		*  @brief
		*    Sets scene renderer pass attribute values using a string
		*
		*  @param[in] sValues
		*    Values to set (e.g.: "ColorClear=\"0 0 0 0\" AmbientColor=\"0.2 0.2 0.2\"")
		*
		*  @remarks
		*    Unlike "SetPassAttribute()" and "SetAttribute()", "SetValues()" sets multiple attributes from all
		*    scene renderer passes to the given value at once.
		*/
		PL_API void SetValues(const PLGeneral::String &sValues) const;

		/**
		*  @brief
		*    Sets all scene renderer pass attribute values to their default value
		*/
		PL_API void SetDefaultValues() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::SurfacePainter	*m_pSurfacePainter;	/**< Used surface painter, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCENERENDERERTOOL_H__
