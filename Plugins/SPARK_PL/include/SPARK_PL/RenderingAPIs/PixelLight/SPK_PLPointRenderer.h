/*********************************************************\
 *  File: SPK_PLPointRenderer.h                          *
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


#ifndef __SPARK_PL_POINTRENDERER_H__
#define __SPARK_PL_POINTRENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	#include <Extensions/Renderers/SPK_PointRendererInterface.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLRenderer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Texture;
	class TextureHandler;
}
namespace SPARK_PL {
	class SPK_PLBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    An abstract Renderer drawing drawing particles as PixelLight points
*
*  @remarks
*    PixelLight points can be configured to render them in 3 different ways :
*    <ul>
*    <li>SPK::POINT_SQUARE : standard PixelLight points</li>
*    <li>SPK::POINT_CIRCLE : antialiased PixelLight points</li>
*    <li>SPK::POINT_SPRITE : PixelLight point sprites (must be supported by the hardware)</li>
*    </ul>
*    Moreover, points size can either be defined in screen space (in pixels) or in the universe space (must be supported by the hardware).
*    The advantage of the universe space is that points size on the screen will be dependant to their distance to the camera, whereas in screen space
*    all points will have the same size on the screen no matter their distance to the camera.
*    <br>
*    Below are the parameters of Particle that are used in this Renderer (others have no effects) :
*    <ul>
*    <li>SPK::PARAM_RED</li>
*    <li>SPK::PARAM_GREEN</li>
*    <li>SPK::PARAM_BLUE</li>
*    <li>SPK::PARAM_ALPHA (only if blending is enabled)</li>
*    </ul>
*
*  @note
*    - Basing on "SPK::GL::GLPointRenderer" (this includes most of the comments)
*/
class SPK_PLPointRenderer : public SPK_PLRenderer, public SPK::PointRendererInterface {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor of SPK_PLPointRenderer
		*/
		SPARK_PL_API virtual ~SPK_PLPointRenderer();

		/**
		*  @brief
		*    Tells whether world size is enabled or not in this SPK_PLPointRenderer
		*
		*  @return
		*    'true' if world size is enabled, 'false' if not
		*/
		SPARK_PL_API bool IsWorldSizeEnabled() const;

		/**
		*  @brief
		*   Sets the way size of points is computed in this SPK_PLPointRenderer
		*
		*  @param[in] bWorldSizeEnabled
		*    'true' to enable universe size, 'false' to use screen size
		*
		*  @return
		*    'true' the type of size can be set, 'false' otherwise
		*
		*  @remarks
		*    If universe size is used (true), the renderer capability is checked.<br>
		*    If universe size is not supported by the hardware, false is returned and nothing happens.<br>
		*    <br>
		*    If world size is enabled, the method SetPixelPerUnit(float, int) must be called to set the conversion between pixels and world units.
		*/
		SPARK_PL_API bool EnableWorldSize(bool bWorldSizeEnabled);

		/**
		*  @brief
		*    Computes a conversion ratio between pixels and universe units
		*
		*  @param[in] fFovY
		*    The field of view in the y axis in radians
		*  @param[in] nScreenHeight
		*    The height of the viewport in pixels
		*
		*  @remarks
		*    This method must be called when using SPK_PLPointRenderer with world size enabled.<br>
		*    It allows to well transpose world size to pixel size by setting the right PixelLight parameters.<br>
		*    <br>
		*    Note that fFovY can be replaced by fFovX if nScreenHeight is replaced by nScreenWidth.
		*
		*  @note
		*    - If fFovY or nScreenHeight is negative, the required data is calculated on the fly (default)
		*/
		SPARK_PL_API void SetPixelPerUnit(float fFovY, int nScreenHeight);

		/**
		*  @brief
		*    Gets the texture of this SPK_PLPointRenderer
		*
		*  @return
		*    The texture of this SPK_PLPointRenderer, can be a null pointer
		*/
		SPARK_PL_API PLRenderer::Texture *GetTexture() const;

		/**
		*  @brief
		*    Sets the texture of this SPK_PLPointRenderer
		*
		*  @param[in] pTexture
		*    The index of the PixelLight texture of this SPK_PLPointRenderer, can be a null pointer
		*
		*  @remarks
		*    Note that the texture is only used if point sprites are used (type is set to SPK::POINT_SPRITE).
		*/
		SPARK_PL_API void SetTexture(PLRenderer::Texture *pTexture);


	//[-------------------------------------------------------]
	//[ Public virtual SPK::PointRendererInterface functions  ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual bool setType(SPK::PointType type);


	//[-------------------------------------------------------]
	//[ Public virtual SPK::BufferHandler functions           ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void createBuffers(const SPK::Group &group);
		SPARK_PL_API virtual void destroyBuffers(const SPK::Group &group);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/** 
		*  @brief
		*    Constructor of SPK_PLPointRenderer
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fSize
		*    The size of the points
		*/
		SPK_PLPointRenderer(PLRenderer::Renderer &cRenderer, float fSize = 1.0f);

		/**
		*  @brief
		*    Enables the use of point parameters
		*
		*  @param[in] fSize
		*    The size of the point
		*  @param[in] bDistance
		*    'true' to enable the modification of the size function of the distance, 'false' not to.
		*
		*  @remarks
		*    This method will set the right point parameters to get the desired point size.<br>
		*    <br>
		*    It can either be used to have points size function of the distance to the camera (is distance is true)
		*    or only to allow bigger range for point sizes (if distance is false).
		*    <br>
		*    Note that if distance is set to true SetPixelPerUnit(float, int) must be call once before.
		*    <br>
		*    Note that before calling this method, the user must ensure that the renderer is capable of point parameters.
		*/
		void EnablePointParameter(float fSize, bool bDistance) const;

		/**
		*  @brief
		*    Setup common render states
		*
		*  @param[in] group
		*    SPK::Group instance provided by SPARK
		*/
		void SetupCommonRenderStates(const SPK::Group &group);


	//[-------------------------------------------------------]
	//[ Protected definitions                                 ]
	//[-------------------------------------------------------]
	protected:
		static const float		 PointSizeCurrent;
		static const float		 PointSizeMin;
		static const float		 PointSizeMax;
		static const std::string PLBufferName;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		SPK_PLBuffer				*m_pSPK_PLBuffer;	/**< Used SPK_PLBuffer instance, can be a null pointer */
		PLRenderer::TextureHandler	*m_pTextureHandler;	/**< Texture handler, always valid! */
		bool						 m_bWorldSize;		/**< 'true' to enable universe size, 'false' to use screen size */
		float						 m_fPixelPerUnit;	/**< Conversion ratio between pixels and universe units, if negative, the required data is calculated on the fly (default) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_POINTRENDERER_H__
