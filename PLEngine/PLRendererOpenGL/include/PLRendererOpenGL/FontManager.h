/*********************************************************\
 *  File: FontManager.h                                  *
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


#ifndef __PLRENDEREROPENGL_FONTMANAGER_H__
#define __PLRENDEREROPENGL_FONTMANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
typedef struct FT_LibraryRec_ *FT_Library;
namespace PLRenderer {
	class VertexBuffer;
	class ProgramUniform;
	class ProgramAttribute;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL renderer font manager
*/
class FontManager : public PLRenderer::FontManager {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			// Vertex shader uniforms
			PLRenderer::ProgramUniform *pGlyphSizePenPosition;
			PLRenderer::ProgramUniform *pTextureCoordinateMinMax;
			PLRenderer::ProgramUniform *pObjectSpaceToClipSpaceMatrix;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pGlyphMap;
			PLRenderer::ProgramUniform *pColor;
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*/
		FontManager(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~FontManager();

		/**
		*  @brief
		*    Returns the FreeType library object
		*
		*  @return
		*    The FreeType library object, NULL on error (in case of an terrible error), do not delete the instance!
		*/
		FT_Library *GetFTLibrary() const;

		/**
		*  @brief
		*    Returns the program for font rendering
		*
		*  @param[in] ppGeneratedProgramUserData
		*    If not NULL, this receives a pointer to an GeneratedProgramUserData instance for fast direct uniform access
		*
		*  @return
		*    The program for font rendering, can be NULL
		*
		*  @note
		*    - The program is using the default shader language of the renderer
		*    - The program has already proper vertex attributes set
		*/
		PLRenderer::Program *GetProgram(GeneratedProgramUserData **ppGeneratedProgramUserData = NULL);


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::FontManager functions      ]
	//[-------------------------------------------------------]
	public:
		virtual PLRenderer::Font *CreateFontTexture(PLGeneral::File &cFile, PLGeneral::uint32 nSize = 12, PLGeneral::uint32 nResolution = 96);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the vertex buffer used for font rendering
		*
		*  @return
		*    The vertex buffer used for font rendering, NULL on error
		*/
		PLRenderer::VertexBuffer *GetVertexBuffer();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		FT_Library							*m_pFTLibrary;			/**< FreeType library object, NULL on error (in case of an terrible error) */
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;	/**< Program generator, can be NULL */
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;		/**< Program flags as class member to reduce dynamic memory allocations */
		PLRenderer::VertexBuffer			*m_pVertexBuffer;		/**< Vertex buffer used for font rendering, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_FONTMANAGER_H__
