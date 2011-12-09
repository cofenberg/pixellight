/*********************************************************\
 *  File: TextureHandler.inl                             *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ TextureHandler::AnimationState                        ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the texture animation
*/
inline Animation &TextureHandler::AnimationState::GetTextureAnimation()
{
	return *m_pTextureAnimation;
}

/**
*  @brief
*    Returns the matrix animation
*/
inline Animation &TextureHandler::AnimationState::GetMatrixAnimation()
{
	return *m_pMatrixAnimation;
}

/**
*  @brief
*    Returns the current texture transformation matrix
*/
inline PLMath::Matrix4x4 &TextureHandler::AnimationState::GetMatrix()
{
	return m_mTrans;
}

/**
*  @brief
*    Returns the color animation
*/
inline Animation &TextureHandler::AnimationState::GetColorAnimation()
{
	return *m_pColorAnimation;
}

/**
*  @brief
*    Returns the current texture color
*/
inline const PLGraphics::Color4 &TextureHandler::AnimationState::GetColor() const
{
	return m_cColor;
}




//[-------------------------------------------------------]
//[ TextureHandler                                        ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the texture animation state object (if there's one :)
*/
inline TextureHandler::AnimationState *TextureHandler::GetAnimationState() const
{
	return m_pAnimationState;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
