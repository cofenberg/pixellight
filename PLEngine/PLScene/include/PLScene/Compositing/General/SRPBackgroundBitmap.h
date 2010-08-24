/*********************************************************\
 *  File: SRPBackgroundBitmap.h                          *
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


#ifndef __PLSCENE_COMPOSITING_GENERAL_BACKGROUNDBITMAP_H__
#define __PLSCENE_COMPOSITING_GENERAL_BACKGROUNDBITMAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLGraphics/Color/Color4.h>
#include <PLRenderer/Material/MaterialHandler.h>
#include "PLScene/Compositing/General/SRPBackground.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Bitmap background scene renderer pass
*/
class SRPBackgroundBitmap : public SRPBackground {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			IgnoreColor = 1<<1	/**< Ignore the color variable of the bitmap */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPBackground::EFlags)
			pl_enum_value(IgnoreColor, "Ignore the color variable of the bitmap")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SRPBackgroundBitmap, "PLScene", PLScene::SRPBackground, "Abstract bitmap background scene renderer pass")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(Material,		PLGeneral::String,		"Data/Effects/DefaultBitmap.plfx",			ReadWrite,	GetSet,			"Material to use",											"Type='Material Effect Image TextureAni'")
		pl_attribute(Color,			PLGraphics::Color4,		PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Bitmap color",												"")
		pl_attribute(Position,		PLMath::Vector2,		PLMath::Vector2(0.0f, 0.0f),				ReadWrite,	DirectValue,	"Bitmap position (0..1), (0, 0)=left top",					"")
		pl_attribute(Size,			PLMath::Vector2,		PLMath::Vector2(1.0f, 1.0f),				ReadWrite,	DirectValue,	"Bitmap size (0..1)",										"")
		pl_attribute(TexelStart,	PLMath::Vector2,		PLMath::Vector2(0.0f, 0.0f),				ReadWrite,	DirectValue,	"Bitmap texture source rectangle (0..1) start coordinate",	"")
		pl_attribute(TexelEnd,		PLMath::Vector2,		PLMath::Vector2(1.0f, 1.0f),				ReadWrite,	DirectValue,	"Bitmap texture source rectangle (0..1) end coordinate",	"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,			pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,			"Flags",													"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetMaterial() const;
		PLS_API void SetMaterial(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SRPBackgroundBitmap();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SRPBackgroundBitmap();

		/**
		*  @brief
		*    Returns the handler of the material
		*
		*  @return
		*    Handler of the material
		*/
		PLS_API const PLRenderer::MaterialHandler &GetMaterialHandler();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Loads the material
		*/
		PLS_API void LoadMaterial();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String			m_sMaterial;	/**< Material name */
		PLRenderer::MaterialHandler m_cMaterial;	/**< Material */
		bool						m_bLoaded;		/**< Material already loaded? */


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const SQCull &cCullQuery);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_COMPOSITING_GENERAL_BACKGROUNDBITMAP_H__
