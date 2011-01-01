/*********************************************************\
 *  File: ImagePL.h                                      *
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


#ifndef __PLSCENE_SCENENODE_GUI_IMAGE_H__
#define __PLSCENE_SCENENODE_GUI_IMAGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Backend/ImageImpl.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class TextureBuffer;
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
*    PixelLight ingame GUI image implementation
*/
class ImagePL : public PLGui::ImageImpl {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cImage
		*    Reference to platform independent image
		*/
		PLS_API ImagePL(PLGui::Image &cImage);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~ImagePL();

		/**
		*  @brief
		*    Unload image
		*/
		PLS_API void Unload();

		/**
		*  @brief
		*    Returns the texture buffer
		*
		*  @return
		*    The texture buffer, NULL on error
		*/
		PLS_API PLRenderer::TextureBuffer *GetTextureBuffer();


	//[-------------------------------------------------------]
	//[ Public virtual PLGui::ImageImpl functions             ]
	//[-------------------------------------------------------]
	public:
		virtual bool Load(const PLGeneral::String &sFilename);
		virtual bool LoadWithColorKey(const PLGeneral::String &sFilename, const PLGraphics::Color3 &cColor);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGui::Image			  *m_pImage;			/**< Pointer to the platform independent image object */
		PLRenderer::TextureBuffer *m_pTextureBuffer;	/**< The texture buffer, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_GUI_IMAGE_H__
