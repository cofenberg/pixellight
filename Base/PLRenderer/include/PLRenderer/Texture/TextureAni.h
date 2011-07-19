/*********************************************************\
 *  File: TextureAni.h                                   *
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


#ifndef __PLRENDERER_TEXTUREANI_H__
#define __PLRENDERER_TEXTUREANI_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include <PLGraphics/Color/Color4.h>
#include "PLRenderer/Texture/Texture.h"
#include "PLRenderer/Texture/AniInfoManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class TextureHandler;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Texture animation resource class
*/
class TextureAni : public Texture {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class TextureHandler;


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Texture animation
		*/
		struct TextureFrame {
			TextureHandler *pTextureHandler;	/**< Texture handler for this frame (always valid!) */
		};

		/**
		*  @brief
		*    Matrix animation
		*/
		struct MatrixFrame {
			PLMath::Vector3 vTranslation;	/**< Translation */
			PLMath::Vector3 vRotation;		/**< Rotation */
			PLMath::Vector3 vScale;			/**< Scale */
		};

		/**
		*  @brief
		*    Color animation
		*/
		struct ColorFrame {
			PLGraphics::Color4 vColor;	/**< Color */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~TextureAni();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This instance
		*/
		PLRENDERER_API TextureAni &operator =(const TextureAni &cSource);

		//[-------------------------------------------------------]
		//[ Texture animation                                     ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the texture animation manager
		*
		*  @return
		*    The texture handlers texture animation manager
		*/
		PLRENDERER_API AniInfoManager &GetTextureAnimationManager();
		PLRENDERER_API const AniInfoManager &GetTextureAnimationManager() const;

		/**
		*  @brief
		*    Create standard texture animation
		*
		*  @note
		*    - A standard animation in only added if there are at the moment no animations at all
		*/
		PLRENDERER_API void CreateStandardTextureAnimation();

		/**
		*  @brief
		*    Returns the texture frames array
		*
		*  @return
		*    The texture frames array
		*/
		PLRENDERER_API PLCore::Array<TextureFrame*> &GetTextureFrames();
		PLRENDERER_API const PLCore::Array<TextureFrame*> &GetTextureFrames() const;

		//[-------------------------------------------------------]
		//[ Matrix animation                                      ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the matrix animation manager
		*
		*  @return
		*    The texture handlers matrix animation manager
		*/
		PLRENDERER_API AniInfoManager &GetMatrixAnimationManager();
		PLRENDERER_API const AniInfoManager &GetMatrixAnimationManager() const;

		/**
		*  @brief
		*    Create standard matrix animation
		*
		*  @note
		*    - A standard animation in only added if there are at the moment no animations at all
		*/
		PLRENDERER_API void CreateStandardMatrixAnimation();

		/**
		*  @brief
		*    Returns the matrix frames array
		*
		*  @return
		*    The matrix frames array
		*/
		PLRENDERER_API PLCore::Array<MatrixFrame*> &GetMatrixFrames();
		PLRENDERER_API const PLCore::Array<MatrixFrame*> &GetMatrixFrames() const;

		//[-------------------------------------------------------]
		//[ Color animation                                       ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the color animation manager
		*
		*  @return
		*    The texture handlers color animation manager
		*/
		PLRENDERER_API AniInfoManager &GetColorAnimationManager();
		PLRENDERER_API const AniInfoManager &GetColorAnimationManager() const;

		/**
		*  @brief
		*    Create standard color animation
		*
		*  @note
		*    - A standard animation in only added if there are at the moment no animations at all
		*/
		PLRENDERER_API void CreateStandardColorAnimation();

		/**
		*  @brief
		*    Returns the color frames array
		*
		*  @return
		*    The color frames array
		*/
		PLRENDERER_API PLCore::Array<ColorFrame*> &GetColorFrames();
		PLRENDERER_API const PLCore::Array<ColorFrame*> &GetColorFrames() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cManager
		*    Texture manager using this resource
		*  @param[in] sName
		*    Resource name to set
		*/
		TextureAni(TextureManager &cManager, const PLCore::String &sName);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Texture animation
		AniInfoManager				 m_cTextureAnimationManager;	/**< Texture animation manager */
		PLCore::Array<TextureFrame*> m_lstTextureFrames;			/**< Texture animation frames */
		// Matrix animation
		AniInfoManager				 m_cMatrixAnimationManager;		/**< Matrix animation manager */
		PLCore::Array<MatrixFrame*>	 m_lstMatrixFrames;				/**< Matrix animation frames */
		// Color animation
		AniInfoManager				 m_cColorAnimationManager;		/**< Color animation manager */
		PLCore::Array<ColorFrame*>	 m_lstColorFrames;				/**< Color animation frames */


	//[-------------------------------------------------------]
	//[ Public virtual Texture functions                      ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual bool IsAnimated() const;


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual bool Load(const PLCore::String &sFilename, const PLCore::String &sParams = "", const PLCore::String &sMethod = "");
		PLRENDERER_API virtual bool Save(const PLCore::String &sFilename, const PLCore::String &sParams = "", const PLCore::String &sMethod = "");
		PLRENDERER_API virtual bool Save(PLCore::File &cFile, const PLCore::String &sParams = "", const PLCore::String &sMethod = "");
		PLRENDERER_API virtual bool Unload();
		PLRENDERER_API virtual PLCore::String GetLoadableTypeName() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_TEXTUREANI_H__
