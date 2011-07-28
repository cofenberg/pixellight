/*********************************************************\
 *  File: RenderInterfacePL.h                            *
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


#ifndef __LIBROCKET_PL_RENDERINTERFACE_H__
#define __LIBROCKET_PL_RENDERINTERFACE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Rocket/Core/RenderInterface.h>
#include <PLMath/Rectangle.h>
#include "libRocket_PL/libRocket_PL.h"


//[-------------------------------------------------------]
//[ Forward declaration                                   ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class IndexBuffer;
	class VertexBuffer;
	class TextureHandler;
	class RendererContext;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract render interface for Rocket into PixelLight
*/
class RenderInterfacePL : public Rocket::Core::RenderInterface {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		LIBROCKET_PL_API virtual ~RenderInterfacePL();

		/**
		*  @brief
		*    Returns the used renderer context
		*
		*  @return
		*    The used renderer context
		*/
		LIBROCKET_PL_API PLRenderer::RendererContext &GetRendererContext() const;


	//[-------------------------------------------------------]
	//[ Public virtual RenderInterfacePL functions            ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Configures PixelLight's rendering system for rendering Rocket
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		LIBROCKET_PL_API virtual bool ConfigureRenderSystem();


	//[-------------------------------------------------------]
	//[ Public virtual Rocket::Core::RenderInterface functions ]
	//[-------------------------------------------------------]
	public:
		LIBROCKET_PL_API virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation) override;
		LIBROCKET_PL_API virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture) override;
		LIBROCKET_PL_API virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry) override;
		LIBROCKET_PL_API virtual void EnableScissorRegion(bool enable) override;
		LIBROCKET_PL_API virtual void SetScissorRegion(int x, int y, int width, int height) override;
		LIBROCKET_PL_API virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source) override;
		LIBROCKET_PL_API virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions) override;
		LIBROCKET_PL_API virtual void ReleaseTexture(Rocket::Core::TextureHandle texture) override;
		LIBROCKET_PL_API virtual float GetHorizontalTexelOffset() override;
		LIBROCKET_PL_API virtual float GetVerticalTexelOffset() override;


	//[-------------------------------------------------------]
	//[ Protected structures                                  ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Compiled geometry instance
		*
		*  @remarks
		*    The structure created for each set of geometry that Rocket compiles. It stores the vertex
		*    and index buffers and the texture associated with the geometry, if one was specified.
		*/
		struct RocketPLCompiledGeometry {
			PLRenderer::VertexBuffer   *pVertexBuffer;		/**< Vertex buffer, always valid! */
			PLRenderer::IndexBuffer	   *pIndexBuffer;		/**< Index buffer, always valid! */
			PLRenderer::TextureHandler *pTextureHandler;	/**< Texture handler, can be a null pointer */
		};


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		LIBROCKET_PL_API RenderInterfacePL();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		LIBROCKET_PL_API RenderInterfacePL(const RenderInterfacePL &cSource);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRendererContext
		*    The used renderer context
		*/
		LIBROCKET_PL_API RenderInterfacePL(PLRenderer::RendererContext &cRendererContext);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		LIBROCKET_PL_API RenderInterfacePL &operator =(const RenderInterfacePL &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::RendererContext *m_pRendererContext;			/**< Render context, always valid! */
		bool						 m_bScissorRegionInitialized;	/**< Scissor region initialized? */
		bool						 m_bScissorRegion;				/**< Scissor region enabled? */
		PLMath::Rectangle			 m_cScissorRegion;				/**< Scissor region, only used if 'm_bScissorRegion' is 'true' */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL


#endif // __LIBROCKET_PL_RENDERINTERFACE_H__
