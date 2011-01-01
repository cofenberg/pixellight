/*********************************************************\
 *  File: SNBitmap.h                                     *
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


#ifndef __PLSCENE_SCENENODE_BITMAP_H__
#define __PLSCENE_SCENENODE_BITMAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLGraphics/Color/Color4.h>
#include <PLRenderer/Material/MaterialHandler.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract bitmap scene node
*
*  @remarks
*    If 'Material' is not a material or an effect, the effect of the default value of
*    'Material' is used together with the given texture.
*/
class SNBitmap : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			IgnoreColor = 1<<10	/**< Ignore the color variable of the bitmap */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(IgnoreColor, "Ignore the color variable of the bitmap")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNBitmap, "PLScene", PLScene::SceneNode, "Abstract bitmap scene node")
		pl_attribute(Material,		PLGeneral::String,		"Data/Effects/DefaultBitmap.plfx",			ReadWrite,	GetSet,	"Material to use",											"Type='Material Effect Image TextureAni'")
		pl_attribute(Color,			PLGraphics::Color4,		PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),	ReadWrite,	GetSet,	"Bitmap color",												"")
		pl_attribute(TexelStart,	PLMath::Vector2,		PLMath::Vector2(0.0f, 0.0f),				ReadWrite,	GetSet,	"Bitmap texture source rectangle (0..1) start coordinate",	"")
		pl_attribute(TexelEnd,		PLMath::Vector2,		PLMath::Vector2(1.0f, 1.0f),				ReadWrite,	GetSet,	"Bitmap texture source rectangle (0..1) end coordinate",	"")
		// Overwritten SceneNode variables
		pl_attribute(Flags,			pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,	"Flags",													"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetMaterial() const;
		PLS_API void SetMaterial(const PLGeneral::String &sValue);
		PLS_API virtual const PLGraphics::Color4 &GetColor() const;
		PLS_API virtual void SetColor(const PLGraphics::Color4 &cValue);
		PLS_API virtual const PLMath::Vector2 &GetTexelStart() const;
		PLS_API virtual void SetTexelStart(const PLMath::Vector2 &vValue);
		PLS_API virtual const PLMath::Vector2 &GetTexelEnd() const;
		PLS_API virtual void SetTexelEnd(const PLMath::Vector2 &vValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
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
		*    Default constructor
		*/
		PLS_API SNBitmap();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNBitmap();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String			m_sMaterial;	/**< Material */
		bool						m_bMaterial;	/**< Material loaded? */
		PLRenderer::MaterialHandler m_cMaterial;	/**< Material */
		PLGraphics::Color4			m_cColor;		/**< Bitmap color */
		PLMath::Vector2				m_vTexelStart;	/**< Bitmap texture source rectangle (0..1) start coordinate */
		PLMath::Vector2				m_vTexelEnd;	/**< Bitmap texture source rectangle (0..1) end coordinate */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_BITMAP_H__
