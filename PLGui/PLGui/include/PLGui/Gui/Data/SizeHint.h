/*********************************************************\
 *  File: SizeHint.h                                     *
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


#ifndef __PLGUI_SIZEHINT_H__
#define __PLGUI_SIZEHINT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2i.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector2i;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Size hint
*/
class SizeHint {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Size policy
		*/
		enum EPolicy {
			Pixel,		/**< The element will have a specific size specified in pixels */
			Percent,	/**< The element will have a specific size specified in percent of available space */
			Preferred,	/**< The element will try to take exactly the preferred size */
			Floating	/**< The element will take as much place as it can get */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nPolicy
		*    Size policy
		*  @param[in] nSize
		*    Size
		*/
		PLGUI_API SizeHint(EPolicy nPolicy = Floating, PLGeneral::uint32 nSize = 0);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSizeHint
		*    Source to copy from
		*/
		PLGUI_API SizeHint(const SizeHint &cSizeHint);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API ~SizeHint();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSizeHint
		*    Source to copy from
		*
		*  @return
		*    Reference to this object
		*/
		PLGUI_API SizeHint &operator =(const SizeHint &cSizeHint);

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cSizeHint
		*    Object to compare with
		*
		*  @return
		*    'true' if both objects are equal, else 'false'
		*/
		PLGUI_API bool operator ==(const SizeHint &cSizeHint) const;

		/**
		*  @brief
		*    Get size policy
		*
		*  @return
		*    Size policy
		*/
		PLGUI_API EPolicy GetPolicy() const;

		/**
		*  @brief
		*    Set size policy
		*
		*  @param[in] nPolicy
		*    Size policy
		*/
		PLGUI_API void SetPolicy(EPolicy nPolicy);

		/**
		*  @brief
		*    Get size
		*
		*  @return
		*    Size
		*/
		PLGUI_API PLGeneral::uint32 GetSize() const;

		/**
		*  @brief
		*    Get size in float
		*
		*  @return
		*    Size
		*/
		PLGUI_API float GetSizeFloat() const;

		/**
		*  @brief
		*    Set size
		*
		*  @param[in] nSize
		*    Size
		*/
		PLGUI_API void SetSize(PLGeneral::uint32 nSize);

		/**
		*  @brief
		*    Set size in float
		*
		*  @param[in] fSize
		*    Size
		*/
		PLGUI_API void SetSizeFloat(float fSize);

		/**
		*  @brief
		*    Set policy and size
		*
		*  @param[in] nPolicy
		*    Size policy
		*  @param[in] nSize
		*    Size
		*/
		PLGUI_API void Set(EPolicy nPolicy, PLGeneral::uint32 nSize);

		/**
		*  @brief
		*    Set policy and size in float
		*
		*  @param[in] nPolicy
		*    Size policy
		*  @param[in] fSize
		*    Size
		*/
		PLGUI_API void SetFloat(EPolicy nPolicy, float fSize);

		/**
		*  @brief
		*    Calculate actual size specified by this size hint
		*
		*  @param[in] nParentSize
		*    Size of the parent element, needed to calculate sizes specified in percentages
		*  @param[in] nPreferredSize
		*    Preferred size of the element, can be -1 if no preferred size is specified
		*
		*  @return
		*    Size, or -1 of policy is Floating
		*/
		PLGUI_API int CalculateSize(PLGeneral::uint32 nParentSize, int nPreferredSize) const;

		/**
		*  @brief
		*    To string
		*
		*  @return
		*    String representation
		*/
		PLGUI_API PLGeneral::String ToString() const;

		/**
		*  @brief
		*    From string
		*
		*  @param[in] sString
		*    String representation
		*
		*  @return
		*    'true' on success, else 'false'
		*/
		PLGUI_API bool FromString(const PLGeneral::String &sString);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		EPolicy	m_nPolicy;	/**< Size policy */
		float	m_fSize;	/**< Size */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGui/Gui/Data/TypeSizeHint.inl"


#endif // __PLGUI_SIZEHINT_H__
