/*********************************************************\
 *  File: RenderInterfacePL.h                            *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLLIBROCKET_RENDERINTERFACE_H__
#define __PLLIBROCKET_RENDERINTERFACE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Rocket/Core/RenderInterface.h>
#include <PLMath/Rectangle.h>
#include "PLlibRocket/PLlibRocket.h"


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
namespace PLlibRocket {


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
		PLLIBROCKET_API virtual ~RenderInterfacePL();

		/**
		*  @brief
		*    Returns the used renderer context
		*
		*  @return
		*    The used renderer context
		*/
		PLLIBROCKET_API PLRenderer::RendererContext &GetRendererContext() const;


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
		PLLIBROCKET_API virtual bool ConfigureRenderSystem();


	//[-------------------------------------------------------]
	//[ Public virtual Rocket::Core::RenderInterface functions ]
	//[-------------------------------------------------------]
	public:
		PLLIBROCKET_API virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation) override;
		PLLIBROCKET_API virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture) override;
		PLLIBROCKET_API virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry) override;
		PLLIBROCKET_API virtual void EnableScissorRegion(bool enable) override;
		PLLIBROCKET_API virtual void SetScissorRegion(int x, int y, int width, int height) override;
		PLLIBROCKET_API virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source) override;
		PLLIBROCKET_API virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions) override;
		PLLIBROCKET_API virtual void ReleaseTexture(Rocket::Core::TextureHandle texture) override;
		PLLIBROCKET_API virtual float GetHorizontalTexelOffset() override;
		PLLIBROCKET_API virtual float GetVerticalTexelOffset() override;


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
		PLLIBROCKET_API RenderInterfacePL();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		PLLIBROCKET_API RenderInterfacePL(const RenderInterfacePL &cSource);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRendererContext
		*    The used renderer context
		*/
		PLLIBROCKET_API RenderInterfacePL(PLRenderer::RendererContext &cRendererContext);

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
		PLLIBROCKET_API RenderInterfacePL &operator =(const RenderInterfacePL &cSource);


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
} // PLlibRocket


#endif // __PLLIBROCKET_RENDERINTERFACE_H__
