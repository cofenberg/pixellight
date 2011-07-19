/*********************************************************\
 *  File: SRPBackgroundBitmap.h                          *
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


#ifndef __PLCOMPOSITING_BACKGROUNDBITMAP_H__
#define __PLCOMPOSITING_BACKGROUNDBITMAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLGraphics/Color/Color4.h>
#include <PLRenderer/Material/MaterialHandler.h>
#include "PLCompositing/SRPBackground.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


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
	pl_class(PLCOM_RTTI_EXPORT, SRPBackgroundBitmap, "PLCompositing", PLCompositing::SRPBackground, "Abstract bitmap background scene renderer pass")
		// Attributes
		pl_attribute(Material,		PLCore::String,			"",											ReadWrite,	GetSet,			"Material to use",											"Type='Material Effect Image TextureAni'")
		pl_attribute(Color,			PLGraphics::Color4,		PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Bitmap color",												"")
		pl_attribute(Position,		PLMath::Vector2,		PLMath::Vector2(0.0f, 0.0f),				ReadWrite,	DirectValue,	"Bitmap position (0..1), (0, 0)=left top",					"")
		pl_attribute(Size,			PLMath::Vector2,		PLMath::Vector2(1.0f, 1.0f),				ReadWrite,	DirectValue,	"Bitmap size (0..1)",										"")
		pl_attribute(TexelStart,	PLMath::Vector2,		PLMath::Vector2(0.0f, 0.0f),				ReadWrite,	DirectValue,	"Bitmap texture source rectangle (0..1) start coordinate",	"")
		pl_attribute(TexelEnd,		PLMath::Vector2,		PLMath::Vector2(1.0f, 1.0f),				ReadWrite,	DirectValue,	"Bitmap texture source rectangle (0..1) end coordinate",	"")
			// Overwritten PLScene::SceneRendererPass attributes
		pl_attribute(Flags,			pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,			"Flags",													"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API PLCore::String GetMaterial() const;
		PLCOM_API void SetMaterial(const PLCore::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPBackgroundBitmap();

		/**
		*  @brief
		*    Destructor
		*/
		PLCOM_API virtual ~SRPBackgroundBitmap();

		/**
		*  @brief
		*    Returns the handler of the material
		*
		*  @return
		*    Handler of the material
		*/
		PLCOM_API const PLRenderer::MaterialHandler &GetMaterialHandler();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Loads the material
		*/
		PLCOM_API void LoadMaterial();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String				m_sMaterial;	/**< Material name */
		PLRenderer::MaterialHandler m_cMaterial;	/**< Material */
		bool						m_bLoaded;		/**< Material already loaded? */


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_BACKGROUNDBITMAP_H__
