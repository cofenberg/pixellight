/*********************************************************\
 *  File: SPK_PLQuadRenderer.h                           *
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


#ifndef __SPARK_PL_QUADRENDERER_H__
#define __SPARK_PL_QUADRENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	// [HACK] There are missing forward declarations within the SPARK headers...
	namespace SPK {
		class Group;
	}
	#include <Extensions/Renderers/SPK_QuadRendererInterface.h>
	#include <Extensions/Renderers/SPK_Oriented3DRendererInterface.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLRenderer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace SPK {
	class Group;
	class Particle;
}
namespace PLRenderer {
	class Texture;
	class VertexBuffer;
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
*    An abstract Renderer drawing particles as PixelLight quads
*
*  @remarks
*    The orientation of the quads depends on the orientation parameters set.
*    This orientation is computed during rendering by the CPU (further improvement of SPARK will allow to make the computation on GPU side).<br>
*    <br>
*    Below are the parameters of Particle that are used in this Renderer (others have no effects) :
*    <ul>
*    <li>SPK::PARAM_SIZE</li>
*    <li>SPK::PARAM_RED</li>
*    <li>SPK::PARAM_GREEN</li>
*    <li>SPK::PARAM_BLUE</li>
*    <li>SPK::PARAM_ALPHA (only if blending is enabled)</li>
*    <li>SPK::PARAM_ANGLE</li>
*    <li>SPK::PARAM_TEXTURE_INDEX (only if not in TEXTURE_NONE mode)</li>
*    </ul>
*
*  @note
*    - Basing on "SPK::GL::GLQuadRenderer" (this includes most of the comments)
*/
class SPK_PLQuadRenderer : public SPK_PLRenderer, public SPK::QuadRendererInterface, public SPK::Oriented3DRendererInterface {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor of SPK_PLQuadRenderer
		*/
		SPARK_PL_API virtual ~SPK_PLQuadRenderer();

		/**
		*  @brief
		*    Gets the texture of this SPK_PLQuadRenderer
		*
		*  @return
		*    The texture of this SPK_PLQuadRenderer, can be a null pointer
		*/
		SPARK_PL_API PLRenderer::Texture *GetTexture() const;

		/**
		*  @brief
		*    Sets the texture of this SPK_PLQuadRenderer
		*
		*  @param[in] pTexture
		*    The texture of this SPK_PLQuadRenderer, can be a null pointer
		*/
		SPARK_PL_API void SetTexture(PLRenderer::Texture *pTexture);


	//[-------------------------------------------------------]
	//[ Public virtual SPK::QuadRendererInterface functions   ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual bool setTexturingMode(SPK::TexturingMode mode);


	//[-------------------------------------------------------]
	//[ Public virtual SPK::BufferHandler functions           ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void createBuffers(const SPK::Group &group);
		SPARK_PL_API virtual void destroyBuffers(const SPK::Group &group);


	//[-------------------------------------------------------]
	//[ Protected definitions                                 ]
	//[-------------------------------------------------------]
	protected:
		static const PLCore::uint32 NumOfVerticesPerParticle;	/**< Number of vertices per particle */
		static const PLCore::uint32 NumOfIndicesPerParticle;	/**< Number of indices per particle */
		static const std::string	PLBufferName;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor of SPK_PLQuadRenderer
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*  @param[in] fScaleX
		*    The scale of the width of the quad
		*  @param[in] fScaleY
		*    The scale of the height of the quad
		*/
		SPK_PLQuadRenderer(PLRenderer::Renderer &cRenderer, float fScaleX = 1.0f, float fScaleY = 1.0f);

		// Some internal helpers
		void UpdateVertexBuffer(const SPK::Group &group);
		inline void CallColorAndVertex(const SPK::Particle &cParticle);	// PixelLight calls for color and position
		inline void CallTexture2DAtlas(const SPK::Particle &cParticle);	// PixelLight calls for 2D atlas texturing 
		inline void CallTexture3D(const SPK::Particle &cParticle);		// PixelLight calls for 3D texturing
		void Render2D(const SPK::Particle &cParticle);					// Rendering for particles with texture 2D or no texture
		void Render2DRot(const SPK::Particle &cParticle);				// Rendering for particles with texture 2D or no texture and rotation
		void Render3D(const SPK::Particle &cParticle);					// Rendering for particles with texture 3D
		void Render3DRot(const SPK::Particle &cParticle);				// Rendering for particles with texture 3D and rotation
		void Render2DAtlas(const SPK::Particle &cParticle);				// Rendering for particles with texture 2D atlas
		void Render2DAtlasRot(const SPK::Particle &cParticle);			// Rendering for particles with texture 2D atlas and rotation


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		SPK_PLBuffer				*m_pSPK_PLBuffer;	/**< Used SPK_PLBuffer instance, can be a null pointer */
		PLRenderer::TextureHandler	*m_pTextureHandler;	/**< Texture handler, always valid! */

		// Curent vertex buffer data - not nice, but more performant as passing them around all over the place
		PLCore::uint32		  	  m_nCurrentVertexSize;
		float					 *m_pfCurrentPosition;
		float					 *m_pfCurrentTexCoord;
		PLRenderer::VertexBuffer *m_pCurrentVertexBuffer;
		PLCore::uint32		  	  m_nCurrentVertex;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_QUADRENDERER_H__
