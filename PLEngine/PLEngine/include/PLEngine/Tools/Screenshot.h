/*********************************************************\
 *  File: Screenshot.h                                   *
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


#ifndef __PLENGINE_SCREENSHOT_H__
#define __PLENGINE_SCREENSHOT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class RendererContext;
	class SurfacePainter;
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
*    Class offering screenshot functionality
*/
class Screenshot {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pRendererContext
		*    Renderer context from which to create screenshots, can be NULL
		*  @param[in] pPainter
		*    Surface painter, can be NULL (only needed for extended screenshot functionality)
		*/
		PL_API Screenshot(PLRenderer::RendererContext *pRendererContext = NULL, PLRenderer::SurfacePainter *pPainter = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PL_API ~Screenshot();

		/**
		*  @brief
		*    Get renderer context
		*
		*  @return
		*    Renderer context from which to create screenshots, can be NULL
		*/
		PL_API PLRenderer::RendererContext *GetRendererContext() const;

		/**
		*  @brief
		*    Set renderer context
		*
		*  @param[in] pRendererContext
		*    Renderer context from which to create screenshots, can be NULL
		*/
		PL_API void SetRendererContext(PLRenderer::RendererContext *pRendererContext);

		/**
		*  @brief
		*    Get surface painter
		*
		*  @return
		*    Surface painter used to create screenshots, can be NULL
		*/
		PL_API PLRenderer::SurfacePainter *GetPainter() const;

		/**
		*  @brief
		*    Set surface painter
		*
		*  @param[in] pSurfacePainter
		*    Surface painter used to create screenshots, can be NULL
		*/
		PL_API void SetPainter(PLRenderer::SurfacePainter *pSurfacePainter);

		/**
		*  @brief
		*    Get screenshot directory
		*
		*  @return
		*    Directory in which the screenshots are saved
		*/
		PL_API PLGeneral::String GetScreenshotDirectory() const;

		/**
		*  @brief
		*    Set screenshot directory
		*
		*  @param[in] sPath
		*    Directory in which the screenshots are saved
		*
		*  @note
		*    - If set to "", the current directory will be used
		*/
		PL_API void SetScreenshotDirectory(const PLGeneral::String &sPath);

		/**
		*  @brief
		*    Save screenshot from current render target
		*
		*  @param[in] sFilename
		*    Screenshot filename (e.g. "Screenshot.png"), if string is empty, GetScreenshotFilename() will be used
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Uses the dimension of the current render target
		*/
		PL_API bool SaveScreenshot(const PLGeneral::String &sFilename = "") const;

		/**
		*  @brief
		*    Save screenshot by using the surface painter of the current render target surface
		*
		*  @param[in] sFilename
		*    Screenshot filename (e.g. "Screenshot.png"), if string is empty, GetScreenshotFilename() will be used
		*  @param[in] nWidth
		*    Width of the screenshot (1..<hardware limitation>)
		*  @param[in] nHeight
		*    Height of screenshot (1..<hardware limitation>)
		*  @param[in] nFormat
		*    Texture buffer pixel format for creating the screenshot (example: 'TextureBuffer::R8G8B8')
		*  @param[in] nFlags
		*    Texture buffer surface flags (see PLRenderer::SurfaceTextureBuffer::EFlags) for creating the screenshot
		*    (example: 'SurfaceTextureBuffer::Depth')
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @remarks
		*    Unlike the simple 'SaveScreenshot()'-function from above, this function is rendering again by
		*    using an own render target allowing a more or less 'free choice' of the screenshot dimension.
		*    This dimension is only limited by the 'render to texture' capabilities of the hardware - most
		*    'current' hardware supports dimensions up to 8192x8192. Use the renderer capabilities to figure
		*    out the maximum supported rectangle texture dimension.
		*/
		PL_API bool SaveScreenshot(const PLGeneral::String &sFilename, PLGeneral::uint16 nWidth, PLGeneral::uint16 nHeight,
								   PLRenderer::TextureBuffer::EPixelFormat nFormat, PLGeneral::uint32 nFlags) const;

		/**
		*  @brief
		*    Get a screenshot filename recommendation
		*
		*  @param[in] sExtension
		*    File name extension (for example "png")
		*
		*  @remarks
		*    The screenshot filename is automatically generated:
		*    "/_Screenshots/Screenshot_0.png", "/_Screenshots/Screenshot_1.png" and so on...
		*
		*  @return
		*    The recommended screenshot filename, empty string on error
		*/
		PL_API PLGeneral::String GetScreenshotFilename(const PLGeneral::String &sExtension = "png") const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::RendererContext *m_pRendererContext;		/**< Used renderer context, can be NULL */
		PLRenderer::SurfacePainter	*m_pSurfacePainter;			/**< Used surface painter, can be NULL */
		PLGeneral::String			 m_sScreenshotDirectory;	/**< Screenshot directory */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_SCREENSHOT_H__
