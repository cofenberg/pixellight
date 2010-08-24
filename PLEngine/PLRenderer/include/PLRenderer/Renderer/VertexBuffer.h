/*********************************************************\
 *  File: VertexBuffer.h                                 *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDERER_VERTEXBUFFER_H__
#define __PLRENDERER_VERTEXBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include <PLGraphics/Color/Color4.h>
#include "PLRenderer/Renderer/Buffer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector3;
}
namespace PLRenderer {
	class IndexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Renderer vertex buffer resource
*
*  @note
*    - If for instance fog coordinates (Capabilities::bVertexBufferFogCoord) are not supported by the
*      GPU, this data is ignored for rendering but can still be used inside your vertex buffer
*/
class VertexBuffer : public Buffer {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Vertex attribute semantic
		*
		*  @note
		*    - Defines input vertex data to the pipeline, on legacy hardware, this should be defined in this order (performance)
		*/
		enum ESemantic {
			Position     =  0,	/**< Position data (1 channel) */
			BlendWeight  =  1,	/**< Blend weight data (1 channel) */
			Normal       =  2,	/**< Normal data (1 channel, only Float3 allowed!) */
			Color        =  3,	/**< Color data (2 channels, only RGBA allowed, second channel requires Capabilities::bVertexBufferSecondaryColor) */
			FogCoord     =  4,	/**< Fog coordinate data (1 channel, only Float1 allowed, requires FixedFunctions::Capabilities::bVertexBufferFogCoord) */
			PSize        =  5,	/**< Point sprite size data (1 channel, only Float1 allowed!) */
			BlendIndices =  6,	/**< Blend indices data (1 channel) */
			TexCoord     =  7,	/**< Texture coordinate data (n channels) */
			Tangent      =  8,	/**< Tangent data (1 channel, only Float3 allowed!) */
			Binormal     =  9	/**< Binormal (also refered to as bitangent) data (1 channel, only Float3 allowed!) */
		};
		static const PLGeneral::uint8 NumOfSemantics      = 10;	/**< Numer of vertex attribute semantics */
		static const PLGeneral::uint8 MaxPipelineChannels = 16;	/**< Maximum possible number of channels */

		/**
		*  @brief
		*    Vertex attribute types
		*/
		enum EType {
			RGBA   = 0,	/**< Color (API dependent storage, do always use GetColor() and SetColor()!) */
			Float1 = 1,	/**< Float 1 */
			Float2 = 2,	/**< Float 2 */
			Float3 = 3,	/**< Float 3 */
			Float4 = 4,	/**< Float 4 */
			Short2 = 5,	/**< Short 2 */
			Short4 = 6	/**< Short 4 */
		};


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Defines input vertex attribute to the pipeline
		*/
		struct Attribute {
			ESemantic		  nSemantic;		/**< Any member of the vertex attribute semantic enumeration type */
			PLGeneral::uint32 nChannel;			/**< Pipeline channel (see ESemantic) */
			EType			  nType;			/**< Any member of the EType enumeration type */
			PLGeneral::uint32 nOffset;			/**< Offset of the vertex attribute */
			// API dependent
			PLGeneral::uint32 nSizeAPI;			/**< Size of the vertex attribute */
			PLGeneral::uint32 nTypeAPI;			/**< API dependent vertex type */
			PLGeneral::uint32 nComponentsAPI;	/**< Number of vertex type components */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~VertexBuffer();

		/**
		*  @brief
		*    Returns the number of vertex attributes
		*
		*  @return
		*    Number of vertex attributes
		*/
		PLRENDERER_API PLGeneral::uint32 GetNumOfVertexAttributes() const;

		/**
		*  @brief
		*    Clears the vertex attributes
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - This is only possible if the vertex buffer is not allocated (see Allocate())
		*    - The virtual buffer function Clear() only clears the buffer itself,
		*      ClearVertexAttributes() clears the vertex attributes definition
		*/
		PLRENDERER_API bool ClearVertexAttributes();

		/**
		*  @brief
		*    Adds vertex attribute
		*
		*  @param[in] nSemantic
		*    Any member of the vertex attribute semantic enumeration type
		*  @param[in] nChannel
		*    Pipeline channel (see ESemantic, maximum see MaxPipelineChannels)
		*  @param[in] nType
		*    Any member of the EType enumeration type
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe this vertex attribute is already there)
		*
		*  @note
		*    - You shouldn't change the vertex attribute after the vertex buffer was
		*      allocated using the Allocate()-function! (performance!)
		*    - It the buffer is still locked, it's forced to be unlocked immediately if all went fine
		*/
		PLRENDERER_API bool AddVertexAttribute(ESemantic nSemantic, PLGeneral::uint32 nChannel, EType nType);

		/**
		*  @brief
		*    Returns a vertex attribute
		*
		*  @param[in] nIndex
		*    Index of the vertex attribute which should be returned
		*
		*  @return
		*    The requested vertex attribute, NULL on error
		*/
		PLRENDERER_API const Attribute *GetVertexAttribute(PLGeneral::uint32 nIndex = 0) const;

		/**
		*  @brief
		*    Returns the first found vertex attribute with the requested semantic
		*
		*  @param[in] nSemantic
		*    Vertex attribute semantic
		*  @param[in] nChannel
		*    Pipeline channel (see ESemantic, maximum see MaxPipelineChannels)
		*
		*  @return
		*    The first found vertex attribute with the requested semantic, NULL on error
		*/
		PLRENDERER_API const Attribute *GetVertexAttribute(ESemantic nSemantic, PLGeneral::uint32 nChannel = 0) const;

		/**
		*  @brief
		*    Returns the vertex size (in bytes)
		*
		*  @return
		*    Vertex size (in bytes)
		*/
		PLRENDERER_API PLGeneral::uint32 GetVertexSize() const;

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this object
		*/
		PLRENDERER_API VertexBuffer &operator =(const VertexBuffer &cSource);

		/**
		*  @brief
		*    Returns the vertex buffer bounding box
		*
		*  @param[out] vMinPos
		*    Will receive the minimum bounding box position
		*  @param[out] vMaxPos
		*    Will receive the maximum bounding box position
		*  @param[in]  pIndexBuffer
		*    Optional index buffer to take only a set of vertices into account, set to NULL if not used
		*/
		PLRENDERER_API void CalculateBoundingBox(PLMath::Vector3 &vMinPos, PLMath::Vector3 &vMaxPos, PLRenderer::IndexBuffer *pIndexBuffer = NULL);

		/**
		*  @brief
		*    Returns the vertex buffer bounding sphere
		*
		*  @param[out] vPos
		*    Will receive the bounding sphere position
		*  @param[out] fRadius
		*    Will receive the bounding sphere radius
		*  @param[in]  pIndexBuffer
		*    Optional index buffer to take only a set of vertices into account, set to NULL if not used
		*/
		PLRENDERER_API void CalculateBoundingSphere(PLMath::Vector3 &vPos, float &fRadius, PLRenderer::IndexBuffer *pIndexBuffer = NULL);


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the data of a vertex buffer attribute
		*
		*  @param[in] nIndex
		*    Vertex index
		*  @param[in] nSemantic
		*    Any member of the vertex attribute semantic enumeration type
		*  @param[in] nChannel
		*    Pipeline channel (see ESemantic)
		*
		*  @return
		*    The data of the locked vertex buffer, NULL on error
		*
		*  @note
		*    - See GetData() in Buffer
		*    - This function will give you the correct offset of the requested
		*      vertex attribute
		*    - When manipulating color data you should use GetColor() and SetColor()!
		*/
		virtual void *GetData(PLGeneral::uint32 nIndex, PLGeneral::uint32 nSemantic, PLGeneral::uint32 nChannel = 0) = 0;

		/**
		*  @brief
		*    Returns the RGBA color of a vertex
		*
		*  @param[in] nIndex
		*    Vertex index
		*  @param[in] nChannel
		*    Pipeline channel (see ESemantic)
		*
		*  @return
		*    The RGBA color of a vertex
		*
		*  @note
		*    - Because the different APIs will store the colors in different formats
		*      you should always use this offered color functions which are API
		*      independent!
		*/
		virtual PLGraphics::Color4 GetColor(PLGeneral::uint32 nIndex, PLGeneral::uint32 nChannel = 0) = 0;

		/**
		*  @brief
		*    Set the RGBA color of a vertex
		*
		*  @param[in] nIndex
		*    Vertex index
		*  @param[in] cColor
		*    Color to set
		*  @param[in] nChannel
		*    Pipeline channel (see ESemantic)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - GetColor()
		*/
		virtual bool SetColor(PLGeneral::uint32 nIndex, const PLGraphics::Color4 &cColor, PLGeneral::uint32 nChannel = 0) = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*/
		PLRENDERER_API VertexBuffer(Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::Array<Attribute*> m_lstVertexAttributes;	/**< The vertex attributes */
		PLGeneral::uint32			 m_nVertexSize;			/**< Size in bytes of the vertex buffer (in bytes) */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		VertexBuffer(const VertexBuffer &cSource);


	//[-------------------------------------------------------]
	//[ Private virtual functions                             ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Is called after a vertex attribute was added to setup some API dependent stuff
		*
		*  @param[in] cAttribute
		*    The added vertex attribute
		*
		*  @note
		*    - This function will setup the API dependent vertex attribute data
		*    - It will also update the current vertex size
		*/
		virtual void VertexAttributeAdded(Attribute &cAttribute) = 0;


	//[-------------------------------------------------------]
	//[ Public virtual Buffer functions                       ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual void *GetData();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_VERTEXBUFFER_H__
