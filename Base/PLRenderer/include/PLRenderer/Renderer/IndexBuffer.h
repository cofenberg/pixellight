/*********************************************************\
 *  File: IndexBuffer.h                                  *
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


#ifndef __PLRENDERER_INDEXBUFFER_H__
#define __PLRENDERER_INDEXBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/Buffer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract renderer index buffer (IBO) resource
*/
class IndexBuffer : public Buffer {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Vertex index types
		*/
		enum EType {
			UInt   = 0,	/**< Unsigned int (may not be supported by each API) */
			UShort = 1,	/**< Unsigned short (default) */
			UByte  = 2	/**< Unsigned byte (may not be supported by each API) */
		};

		/** Maximum vertex index which can be used if UShort is used as index buffer type */
		static const PLCore::uint32 MaxVertexIndexUShort = 65535;

		/** Maximum vertex index which can be used if UByte is used as index buffer type */
		static const PLCore::uint32 MaxVertexIndexUByte = 255;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDERER_API virtual ~IndexBuffer();

		/**
		*  @brief
		*    Returns the type of the buffer elements
		*
		*  @return
		*    The type of the buffer elements
		*/
		inline EType GetElementType() const;

		/**
		*  @brief
		*    Sets the type of the buffer elements
		*
		*  @param[in] nType
		*    The type of the buffer elements
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the buffer is already allocated)
		*
		*  @note
		*    - It's only possible to change the element type if the buffer isn't allocated
		*    - Try to avoid UInt whenever possible for more performance and better compatibility to for example mobile graphics API's
		*/
		inline bool SetElementType(EType nType = UShort);

		/**
		*  @brief
		*    Sets the type of the buffer elements automatically by using a given maximum vertex index
		*
		*  @param[in] nMaximumIndex
		*    Maximum vertex index
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the buffer is already allocated)
		*
		*  @remarks
		*    If the given maximum vertex index is <= 'MaxVertexIndexUByte' the type
		*    'EByte' is chosen. If the given maximum vertex index is <= 'MaxVertexIndexUShort'
		*    the type 'EShort' is chosen, else 'UInt'. Please don't oversight the '='.
		*    If you have n vertices, the last one has the index n-1 because we start
		*    counting at zero.
		*
		*  @see
		*    - SetElementType()
		*/
		inline bool SetElementTypeByMaximumIndex(PLCore::uint32 nMaximumIndex);

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
		PLRENDERER_API IndexBuffer &operator =(const IndexBuffer &cSource);

		/**
		*  @brief
		*    Copies data from a given buffer into this index buffer
		*
		*  @param[in] pData
		*    Data to copy into this index buffer, must be valid and must have at least "GetSize()" bytes
		*
		*  @remarks
		*    This ease of use method locks the index buffer, copies the
		*    given data into it and unlocks the index buffer when done.
		*/
		inline void CopyDataFrom(const void *pData);

		/**
		*  @brief
		*    Copies data from this index buffer into a given buffer
		*
		*  @param[out] pData
		*    Buffer to copy into, must be valid and must have at least "GetSize()" bytes
		*
		*  @remarks
		*    This ease of use method locks the index buffer, copies the index buffer
		*    data into the given buffer and unlocks the index buffer when done.
		*/
		inline void CopyDataTo(void *pData);

		/**
		*  @brief
		*    Returns the data of the index buffer
		*
		*  @param[in] nIndex
		*    Index index
		*
		*  @return
		*    Index data
		*
		*  @note
		*    - This function will give you the correct data of the requested
		*      index, therefore you should always use this function to be not forced
		*      to worry about the internal index data type. (see EType)
		*
		*  @see
		*    - Buffer::GetData()
		*/
		PLRENDERER_API PLCore::uint32 GetData(PLCore::uint32 nIndex);

		/**
		*  @brief
		*    Sets the data of the index buffer
		*
		*  @param[in] nIndex
		*    Index index
		*  @param[in] nData
		*    Data to set
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - GetData()
		*/
		PLRENDERER_API bool SetData(PLCore::uint32 nIndex, PLCore::uint32 nData);


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
		PLRENDERER_API IndexBuffer(Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		EType m_nElementType;	/**< Element type */


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
		IndexBuffer(const IndexBuffer &cSource);


	//[-------------------------------------------------------]
	//[ Public virtual Buffer functions                       ]
	//[-------------------------------------------------------]
	public:
		PLRENDERER_API virtual void *GetData() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLRenderer/Renderer/IndexBuffer.inl"


#endif // __PLRENDERER_INDEXBUFFER_H__
