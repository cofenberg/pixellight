/*********************************************************\
 *  File: DrawHelpersBackendFixedFunctions.h             *
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


#ifndef __PLRENDERERBACKEND_DRAWHELPERSBACKENDFIXEDFUNCTIONS_H__
#define __PLRENDERERBACKEND_DRAWHELPERSBACKENDFIXEDFUNCTIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Matrix4x4.h>
#include "PLRenderer/Renderer/Backend/DrawHelpersBackend.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Fixed functions based draw helpers interface implementation
*/
class DrawHelpersBackendFixedFunctions : public DrawHelpersBackend {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer instance to use
		*/
		PLRENDERER_API DrawHelpersBackendFixedFunctions(Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~DrawHelpersBackendFixedFunctions();


	//[-------------------------------------------------------]
	//[ Public virtual DrawHelpers functions                  ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual void Begin2DMode(float fX1 = 0.0f, float fY1 = 0.0f, float fX2 = 1.0f, float fY2 = 1.0f) override;
		PLRENDERER_API virtual void End2DMode() override;
		PLRENDERER_API virtual void DrawImage(TextureBuffer &cTextureBuffer, SamplerStates &cSamplerStates, const PLMath::Vector2 &vPos, const PLMath::Vector2 &vSize = PLMath::Vector2::Zero, const PLGraphics::Color4 &cColor = PLGraphics::Color4::White,
											  float fAlphaReference = 1.0f, const PLMath::Vector2 &vTextureCoordinate = PLMath::Vector2::Zero, const PLMath::Vector2 &vTextureCoordinateSize = PLMath::Vector2::One, const PLMath::Matrix4x4 &mTexture = PLMath::Matrix4x4::Identity) override;
		PLRENDERER_API virtual void DrawImage(TextureBuffer &cTextureBuffer, SamplerStates &cSamplerStates, const PLMath::Vector3 &vPos, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, const PLMath::Vector2 &vSize = PLMath::Vector2::Zero, const PLGraphics::Color4 &cColor = PLGraphics::Color4::White,
											  float fAlphaReference = 1.0f, const PLMath::Vector2 &vTextureCoordinate = PLMath::Vector2::Zero, const PLMath::Vector2 &vTextureCoordinateSize = PLMath::Vector2::One, const PLMath::Matrix4x4 &mTexture = PLMath::Matrix4x4::Identity) override;
		PLRENDERER_API virtual void DrawPoint(const PLGraphics::Color4 &cColor, const PLMath::Vector2 &vPosition, float fSize = 1.0f) override;
		PLRENDERER_API virtual void DrawPoint(const PLGraphics::Color4 &cColor, const PLMath::Vector3 &vPosition, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, float fSize = 1.0f) override;
		PLRENDERER_API virtual void DrawLine(const PLGraphics::Color4 &cColor, const PLMath::Vector2 &vStartPosition, const PLMath::Vector2 &vEndPosition, float fWidth = 1.0f) override;
		PLRENDERER_API virtual void DrawLine(const PLGraphics::Color4 &cColor, const PLMath::Vector3 &vStartPosition, const PLMath::Vector3 &vEndPosition, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, float fWidth = 1.0f) override;
		PLRENDERER_API virtual void DrawTriangle(const PLGraphics::Color4 &cColor, const PLMath::Vector3 &vV1, const PLMath::Vector3 &vV2, const PLMath::Vector3 &vV3, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, float fWidth = 0.0f) override;
		PLRENDERER_API virtual void DrawQuad(const PLGraphics::Color4 &cColor, const PLMath::Vector2 &vPos, const PLMath::Vector2 &vSize, float fWidth = 0.0f) override;
		PLRENDERER_API virtual void DrawQuad(const PLGraphics::Color4 &cColor, const PLMath::Vector3 &vV1, const PLMath::Vector3 &vV2, const PLMath::Vector3 &vV3, const PLMath::Vector3 &vV4, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, float fWidth = 0.0f) override;
		PLRENDERER_API virtual void DrawGradientQuad(const PLGraphics::Color4 &cColor1, const PLGraphics::Color4 &cColor2, float fAngle, const PLMath::Vector2 &vPos, const PLMath::Vector2 &vSize) override;
		PLRENDERER_API virtual void DrawGradientQuad(const PLGraphics::Color4 &cColor1, const PLGraphics::Color4 &cColor2, float fAngle, const PLMath::Vector3 &vV1, const PLMath::Vector3 &vV2, const PLMath::Vector3 &vV3, const PLMath::Vector3 &vV4, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Matrix4x4 m_m2DModeProjBackup;	/**< Projection matrix backup */
		PLMath::Matrix4x4 m_m2DModeViewBackup;	/**< View matrix backup */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERERBACKEND_DRAWHELPERSBACKENDFIXEDFUNCTIONS_H__
