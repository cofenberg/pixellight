/*********************************************************\
 *  File: DrawHelpersBackend.h                           *
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


#ifndef __PLRENDERERBACKEND_DRAWHELPERSBACKEND_H__
#define __PLRENDERERBACKEND_DRAWHELPERSBACKEND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/DrawHelpers.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Renderer;
class VertexBuffer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract draw helpers interface implementation
*/
class DrawHelpersBackend : public DrawHelpers {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~DrawHelpersBackend();


	//[-------------------------------------------------------]
	//[ Public virtual DrawHelpers functions                  ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual bool Is2DMode() const;
		PLRENDERER_API virtual bool Get2DMode(float &fX1, float &fY1, float &fX2, float &fY2) const;
		PLRENDERER_API virtual float Get2DZValue() const;
		PLRENDERER_API virtual void Set2DZValue(float fZValue = 0.0f);
		PLRENDERER_API virtual const PLMath::Matrix4x4 &GetObjectSpaceToClipSpaceMatrix() const;
		PLRENDERER_API virtual void DrawText(Font &cFont, const PLCore::String &sText, const PLGraphics::Color4 &cColor, const PLMath::Vector2 &vPosition, PLCore::uint32 nFlags = 0, const PLMath::Vector2 &vScale = PLMath::Vector2::One, const PLMath::Vector2 &vBias = PLMath::Vector2::Zero);
		PLRENDERER_API virtual void DrawText(Font &cFont, const PLCore::String &sText, const PLGraphics::Color4 &cColor, const PLMath::Vector3 &vPosition, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, PLCore::uint32 nFlags = 0, const PLMath::Vector2 &vScale = PLMath::Vector2::One, const PLMath::Vector2 &vBias = PLMath::Vector2::Zero);
		PLRENDERER_API virtual float GetTextWidth(Font &cFont, const PLCore::String &sText) const;
		PLRENDERER_API virtual float GetTextHeight(Font &cFont) const;
		PLRENDERER_API virtual void DrawBox(const PLGraphics::Color4 &cColor, const PLMath::Vector3 &vMin, const PLMath::Vector3 &vMax, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, float fWidth = 1.0f);
		PLRENDERER_API virtual void DrawPlane(const PLGraphics::Color4 &cColor, const PLMath::Vector3 &vN, float fD, const PLMath::Matrix4x4 &mObjectSpaceToClipSpace, float fSize = 10000.0f, float fLineWidth = 1.0f);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer instance to use
		*/
		PLRENDERER_API DrawHelpersBackend(Renderer &cRenderer);

		/**
		*  @brief
		*    Creates the internally used vertex buffer if it's not created yet
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLRENDERER_API bool CreateTempBuffes();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Renderer	 *m_pRenderer;			/**< Renderer instance to use, always valid! */
		VertexBuffer *m_pTempVertexBuffer;	/**< Vertex buffer for drawing, can be a null pointer */
		// 2D mode variables
		bool			  m_b2DMode;					/**< Are we currently in the 2D mode? */
		float			  m_fVirtualScreen[4];			/**< The virtual screen size */
		float			  m_fZValue2D;					/**< Z-value for 2D mode */
		PLMath::Matrix4x4 m_mObjectSpaceToClipSpace;	/**< 2D mode object space to clip space matrix */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERERBACKEND_DRAWHELPERSBACKEND_H__
