/*********************************************************\
 *  File: TextureAni.inl                                 *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Texture animation                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the texture animation manager
*/
inline AniInfoManager &TextureAni::GetTextureAnimationManager()
{
	return m_cTextureAnimationManager;
}

inline const AniInfoManager &TextureAni::GetTextureAnimationManager() const
{
	return m_cTextureAnimationManager;
}

/**
*  @brief
*    Returns the texture frames array
*/
inline PLCore::Array<TextureAni::TextureFrame*> &TextureAni::GetTextureFrames()
{
	return m_lstTextureFrames;
}

inline const PLCore::Array<TextureAni::TextureFrame*> &TextureAni::GetTextureFrames() const
{
	return m_lstTextureFrames;
}


//[-------------------------------------------------------]
//[ Matrix animation                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the matrix animation manager
*/
inline AniInfoManager &TextureAni::GetMatrixAnimationManager()
{
	return m_cMatrixAnimationManager;
}

inline const AniInfoManager &TextureAni::GetMatrixAnimationManager() const
{
	return m_cMatrixAnimationManager;
}

/**
*  @brief
*    Returns the matrix frames array
*/
inline PLCore::Array<TextureAni::MatrixFrame*> &TextureAni::GetMatrixFrames()
{
	return m_lstMatrixFrames;
}

inline const PLCore::Array<TextureAni::MatrixFrame*> &TextureAni::GetMatrixFrames() const
{
	return m_lstMatrixFrames;
}


//[-------------------------------------------------------]
//[ Color animation                                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the color animation manager
*/
inline AniInfoManager &TextureAni::GetColorAnimationManager()
{
	return m_cColorAnimationManager;
}

inline const AniInfoManager &TextureAni::GetColorAnimationManager() const
{
	return m_cColorAnimationManager;
}

/**
*  @brief
*    Returns the color frames array
*/
inline PLCore::Array<TextureAni::ColorFrame*> &TextureAni::GetColorFrames()
{
	return m_lstColorFrames;
}

inline const PLCore::Array<TextureAni::ColorFrame*> &TextureAni::GetColorFrames() const
{
	return m_lstColorFrames;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
