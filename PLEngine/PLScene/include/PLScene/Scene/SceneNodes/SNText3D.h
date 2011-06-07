/*********************************************************\
 *  File: SNText3D.h                                     *
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


#ifndef __PLSCENE_SCENENODE_TEXT3D_H__
#define __PLSCENE_SCENENODE_TEXT3D_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Material/MaterialHandler.h>
#include "PLScene/Scene/SceneNodes/SNText.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    3D ("flat") text scene node
*
*  @note
*    - The text is drawn on the x/y plane and 'looks' into the positive z axis
*    - The 3D placed text has always a height of 1 to be independent of the actual 'font size'
*    - The 'font size' can be seen as the 'font quality'
*/
class SNText3D : public SNText {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoBackfaceCulling = 1<<11	/**< No backface culling so 'both' sides of the text can be seen */
		};
		pl_enum(EFlags)
			pl_enum_base(SNText::EFlags)
			pl_enum_value(NoBackfaceCulling, "No backface culling so 'both' sides of the text can be seen")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNText3D, "PLScene", PLScene::SNText, "3D (\"flat\") text scene node")
		// Attributes
		pl_attribute(BackgroundMaterial,	PLGeneral::String,		"",	ReadWrite,	GetSet,	"Background material to use",	"Type='Material Effect Image TextureAni'")
			// Overwritten SceneNode attributes
		pl_attribute(Flags,					pl_flag_type(EFlags),	0,	ReadWrite,	GetSet,	"Flags",						"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetBackgroundMaterial() const;
		PLS_API void SetBackgroundMaterial(const PLGeneral::String &sValue);
		PLS_API virtual void SetText(const PLGeneral::String &sValue);
		PLS_API virtual void SetFont(const PLGeneral::String &sValue);
		PLS_API virtual void SetFontSize(PLGeneral::uint32 nValue);
		PLS_API virtual void SetFlags(PLGeneral::uint32 nValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNText3D();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNText3D();

		/**
		*  @brief
		*    Returns the handler of the background material
		*
		*  @return
		*    Handler of the background material
		*/
		PLS_API const PLRenderer::MaterialHandler &GetBackgroundMaterialHandler();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String			m_sBackgroundMaterial;	/**< Background material */
		bool						m_bBackgroundMaterial;	/**< Background material loaded? */
		PLRenderer::MaterialHandler m_cBackgroundMaterial;	/**< Background material */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawTransparent(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode);


	//[-------------------------------------------------------]
	//[ Private virtual SceneNode functions                   ]
	//[-------------------------------------------------------]
	private:
		virtual void UpdateAABoundingBox();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_TEXT3D_H__
