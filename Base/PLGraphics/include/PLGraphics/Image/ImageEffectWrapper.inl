/*********************************************************\
 *  File: ImageEffectWrapper.inl                         *
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
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
inline ImageEffectWrapper::ImageEffectWrapper(const PLCore::String &sEffect, const PLCore::String &sParameters) :
	m_pImageEffect(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
inline ImageEffectWrapper::~ImageEffectWrapper()
{
	// Destroy wrapper image effect
	if (m_pImageEffect)
		delete m_pImageEffect;
}

/**
*  @brief
*    Get wrapped image effect
*/
inline ImageEffect *ImageEffectWrapper::GetImageEffect() const
{
	// Return image effect
	return m_pImageEffect;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
