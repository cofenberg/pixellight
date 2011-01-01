/*********************************************************\
 *  File: Chunk.h                                        *
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


#ifndef __PLCORE_CHUNK_H__
#define __PLCORE_CHUNK_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Tools/Loadable.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Chunk of data
*
*  @remarks
*    This class encapsulates a chunk of data in a quite primitive way. The semantic of the chunk data can be provided, but
*    it's no requirement. A chunk consists of a bunch of elements, were each element consists of at least one component and
*    all components of all elements have the same data type. A chunk can for example be used to store keyframed positions for
*    animation purposes. 
*/
class Chunk : public Loadable {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Semantic
		*/
		enum ESemantic {
			Unknown  = 0,	/**< Unknown */
			Position = 1,	/**< Position */
			Rotation = 2,	/**< Rotation */
			Scale    = 3	/**< Scale */
		};

		/**
		*  @brief
		*    Element type
		*/
		enum EElementType {
			Int8   = 0,	/**< Int8 */
			Int16  = 1,	/**< Int16 */
			Int32  = 2,	/**< Int32 */
			UInt8  = 3,	/**< UInt8 */
			UInt16 = 4,	/**< UInt16 */
			UInt32 = 5,	/**< UInt32 */
			Float  = 6,	/**< Float */
			Double = 7	/**< Double */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API Chunk();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~Chunk();

		/**
		*  @brief
		*    Returns the semantic
		*
		*  @return
		*    The semantic
		*/
		PLCORE_API ESemantic GetSemantic() const;

		/**
		*  @brief
		*    Sets the semantic
		*
		*  @param[in] nSemantic
		*    The semantic
		*/
		PLCORE_API void SetSemantic(ESemantic nSemantic);

		/**
		*  @brief
		*    Allocates the chunk
		*
		*  @param[in] nElementType
		*    The element type
		*  @param[in] nNumOfComponentsPerElement
		*    The number of components per element
		*  @param[in] nNumOfElements
		*    The number of elements
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool Allocate(EElementType nElementType, PLGeneral::uint32 nNumOfComponentsPerElement, PLGeneral::uint32 nNumOfElements);

		/**
		*  @brief
		*    Returns the chunk data
		*
		*  @return
		*    The chunk data, can be NULL - do NOT delete this memory!
		*/
		PLCORE_API PLGeneral::uint8 *GetData();

		/**
		*  @brief
		*    Returns the chunk data
		*
		*  @return
		*    The chunk data, can be NULL - do NOT delete this memory!
		*/
		PLCORE_API const PLGeneral::uint8 *GetData() const;

		/**
		*  @brief
		*    Returns the chunk element component data
		*
		*  @param[in] nElement
		*    Element index to return the component data from (0 - GetNumOfElements()-1), must be valid!
		*  @param[in] nComponent
		*    Index of the element component to data from (0 - GetNumOfComponentsPerElement()-1), must be valid!
		*
		*  @return
		*    The chunk element component data, can be NULL - do NOT delete this memory!
		*/
		PLCORE_API PLGeneral::uint8 *GetElementComponentData(PLGeneral::uint32 nElement, PLGeneral::uint32 nComponent);

		/**
		*  @brief
		*    Returns the chunk element component data
		*
		*  @param[in] nElement
		*    Element index to return the component data from (0 - GetNumOfElements()-1), must be valid!
		*  @param[in] nComponent
		*    Index of the element component to data from (0 - GetNumOfComponentsPerElement()-1), must be valid!
		*
		*  @return
		*    The chunk element component data, can be NULL - do NOT delete this memory!
		*/
		PLCORE_API const PLGeneral::uint8 *GetElementComponentData(PLGeneral::uint32 nElement, PLGeneral::uint32 nComponent) const;

		/**
		*  @brief
		*    Clears the chunk
		*/
		PLCORE_API void Clear();

		/**
		*  @brief
		*    Returns the element type
		*
		*  @return
		*    The element type
		*/
		PLCORE_API EElementType GetElementType() const;

		/**
		*  @brief
		*    Returns the number of components per element
		*
		*  @return
		*    The number of components per element
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfComponentsPerElement() const;

		/**
		*  @brief
		*    Returns the number of elements
		*
		*  @return
		*    The number of elements
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfElements() const;

		/**
		*  @brief
		*    Returns the number of bytes per component of an element
		*
		*  @return
		*    The number of bytes per component of an element
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfBytesPerElementComponent() const;

		/**
		*  @brief
		*    Returns the number of bytes per element
		*
		*  @return
		*    The number of bytes per element
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfBytesPerElement() const;

		/**
		*  @brief
		*    Returns the total number of bytes of the chunk data
		*
		*  @return
		*    The total number of bytes of the chunk data
		*/
		PLCORE_API PLGeneral::uint32 GetTotalNumOfBytes() const;

		/**
		*  @brief
		*    Returns the total number of components (all elements summed up) within the chunk
		*
		*  @return
		*    The total number of components within the chunk
		*/
		PLCORE_API PLGeneral::uint32 GetTotalNumOfComponents() const;


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
		Chunk(const Chunk &cSource);

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
		Chunk &operator =(const Chunk &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		ESemantic		   m_nSemantic;						/**< Semantic */
		EElementType	   m_nElementType;					/**< Element typ */
		PLGeneral::uint32  m_nNumOfComponentsPerElement;	/**< Number of components per element */
		PLGeneral::uint32  m_nNumOfElements;				/**< Number of elements */
		PLGeneral::uint8  *m_pData;							/**< The data, can be NULL */


	//[-------------------------------------------------------]
	//[ Public virtual Loadable functions                     ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API virtual bool Unload();
		PLCORE_API virtual PLGeneral::String GetLoadableTypeName() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CHUNK_H__
