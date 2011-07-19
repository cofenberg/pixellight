/*********************************************************\
 *  File: ImageEffectWrapper.cpp                         *
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
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGraphics/Image/ImageEffectWrapper.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ImageEffectWrapper)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ImageEffectWrapper::ImageEffectWrapper(const String &sEffect, const String &sParameters) :
	m_pImageEffect(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
ImageEffectWrapper::~ImageEffectWrapper()
{
	// Destroy wrapper image effect
	if (m_pImageEffect)
		delete m_pImageEffect;
}

/**
*  @brief
*    Get wrapped image effect
*/
ImageEffect *ImageEffectWrapper::GetImageEffect() const
{
	// Return image effect
	return m_pImageEffect;
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
bool ImageEffectWrapper::Apply(Image &cImage) const
{
	// Call wrapped image effect
	return m_pImageEffect ? m_pImageEffect->Apply(cImage) : false;
}

bool ImageEffectWrapper::Apply(ImagePart &cPart) const
{
	// Call wrapped image effect
	return m_pImageEffect ? m_pImageEffect->Apply(cPart) : false;
}

bool ImageEffectWrapper::Apply(ImageBuffer &cBuffer) const
{
	// Call wrapped image effect
	return m_pImageEffect ? m_pImageEffect->Apply(cBuffer) : false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
