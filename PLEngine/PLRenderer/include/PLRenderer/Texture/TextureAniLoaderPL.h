/*********************************************************\
 *  File: TextureAniLoaderPL.h                           *
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


#ifndef __PLRENDERER_MATERIALLOADER_PL_H__
#define __PLRENDERER_MATERIALLOADER_PL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Texture/TextureAniLoader.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class XmlElement;
}
namespace PLRenderer {
	class AniInfoManager;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Texture animation loader implementation for the PixelLight texture animation XML file format
*/
class TextureAniLoaderPL : public TextureAniLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLRENDERER_RTTI_EXPORT, TextureAniLoaderPL, "PLRenderer", PLRenderer::TextureAniLoader, "Texture animation loader implementation for the PixelLight texture animation XML file format")
		pl_properties
			pl_property("Formats",	"tani,TANI")
			pl_property("Load",		"1")
			pl_property("Save",		"1")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, TextureAni&, PLGeneral::File&, "Load method", "")
		pl_method_2(Save, bool, const TextureAni&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API bool Load(TextureAni &cTextureAni, PLGeneral::File &cFile);
		PLRENDERER_API bool Save(const TextureAni &cTextureAni, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLRENDERER_API TextureAniLoaderPL();

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureAniLoaderPL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loader implementation for format version 1
		*
		*  @param[in] cTextureAni
		*    Texture animation to load into
		*  @param[in] cTextureAniElement
		*    Texture animation XML element to read the data from
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV1(TextureAni &cTextureAni, const PLGeneral::XmlElement &cTextureAniElement) const;

		/**
		*  @brief
		*    Adds an animation information manager to the given XML element
		*
		*  @param[out] cElement
		*    XML element to add to
		*  @param[in]  cAniInfoManager
		*    Animation information manager to use
		*  @param[in]  sType
		*    Type of animation
		*/
		void AddAniInfoManager(PLGeneral::XmlElement &cElement, const AniInfoManager &cAniInfoManager, const PLGeneral::String &sType) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_MATERIALLOADER_PL_H__
