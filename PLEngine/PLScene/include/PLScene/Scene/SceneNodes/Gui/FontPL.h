/*********************************************************\
 *  File: FontPL.h                                       *
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


#ifndef __PLSCENE_SCENENODE_GUI_FONT_H__
#define __PLSCENE_SCENENODE_GUI_FONT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/PLGuiDefinitions.h>
#include <PLGui/Backend/FontImpl.h>
#include <PLRenderer/Renderer/ResourceHandler.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Font;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight ingame GUI font implementation
*/
class FontPL : public PLGui::FontImpl {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFont
		*    Reference to platform independent font
		*/
		PLS_API FontPL(PLGui::Font &cFont);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~FontPL();

		/**
		*  @brief
		*    Returns the renderer font
		*
		*  @return
		*    Renderer font, can be a null pointer
		*/
		PLS_API PLRenderer::Font *GetRendererFont();


	//[-------------------------------------------------------]
	//[ Public virtual PLGui::FontImpl functions              ]
	//[-------------------------------------------------------]
	public:
		virtual bool LoadFont(const PLGeneral::String &sFamily, PLGeneral::uint32 nHeight, PLGeneral::uint32 nWeight, PLGui::EFontStyle nStyle);
		virtual bool LoadFont(const PLGeneral::String &sFilename, PLGeneral::uint32 nHeight);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::Font					*m_pFont;			/**< Pointer to the platform independent font object */
		PLRenderer::ResourceHandler  m_cRendererFont;	/**< Renderer font resource handler */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_GUI_FONT_H__
