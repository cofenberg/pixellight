/*********************************************************\
 *  File: Quadtree.h                                     *
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


#ifndef __PLMATH_QUADTREE_H__
#define __PLMATH_QUADTREE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLMath/Vector3.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PlaneSet;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Quadtree patch
*/
class QuadtreePatch {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLMATH_API QuadtreePatch();

		/**
		*  @brief
		*    Destructor
		*/
		PLMATH_API virtual ~QuadtreePatch();

		/**
		*  @brief
		*    Returns whether the patch is currently visible or not
		*
		*  @return
		*    'true' if the patch is visible, else 'false'
		*/
		PLMATH_API bool IsVisible() const;

		/**
		*  @brief
		*    Sets whether the patch is currently visible or not
		*
		*  @param[in] bVisible
		*    Should the patch be visible?
		*/
		PLMATH_API void SetVisible(bool bVisible = true);

		/**
		*  @brief
		*    Returns the bounding box minimum coordinate
		*
		*  @return
		*    Bounding box minimum coordinate
		*/
		PLMATH_API Vector3 &GetBBMin();

		/**
		*  @brief
		*    Returns the bounding box maximum coordinate
		*
		*  @return
		*    Bounding box maximum coordinate
		*/
		PLMATH_API Vector3 &GetBBMax();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	public:
		bool	m_bVisible;			/**< Is the quadtree visible? */
		Vector3 m_vBoundingBox[2];	/**< Quadtree bounding box (min/max) */


};

/**
*  @brief
*    Quadtree
*/
class Quadtree {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLMATH_API Quadtree();

		/**
		*  @brief
		*    Destructor
		*/
		PLMATH_API virtual ~Quadtree();

		/**
		*  @brief
		*    Initializes the quadtree
		*
		*  @param[in] nXOffset
		*    Quadtree x offset
		*  @param[in] nYOffset
		*    Quadtree y offset
		*  @param[in] nXSize
		*    Quadtree x dimension
		*  @param[in] nYSize
		*    Quadtree y dimension
		*  @param[in] pParent
		*    Parent quadtree, can be NULL
		*
		*  @note
		*    - You should destroy the old quadtree before you initialize the new one!
		*/
		PLMATH_API void Init(PLGeneral::uint32 nXOffset = 0, PLGeneral::uint32 nYOffset = 0, PLGeneral::uint32 nXSize = 0,
							 PLGeneral::uint32 nYSize = 0, Quadtree *pParent = NULL);

		/**
		*  @brief
		*    Builds the quadtree
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - The quadtree must be initialized first!
		*/
		PLMATH_API bool Build();

		/**
		*  @brief
		*    Destroy the quadtree
		*/
		PLMATH_API void Destroy();

		/**
		*  @brief
		*    Updates the bounding boxes of the quadtree
		*
		*  @param[out] ppPatch
		*    Pointer to the quadtree patches, can be NULL (in that case this function is quite useless...)
		*
		*  @note
		*    - There must be x size * y size patches in the array!
		*    - The quadtree patches must have correct bounding boxes
		*    - If the bounding box of a patch is changed you have to recall this
		*      function!
		*/
		PLMATH_API void UpdateBoundingBoxes(QuadtreePatch **ppPatch);

		/**
		*  @brief
		*    Updates the visibility information of the quadtree patches
		*
		*  @param[in]  cPlaneSet
		*    Plane set to check
		*  @param[out] ppPatch
		*    Patches to be updated, can be NULL (in that case this function is quite useless...)
		*
		*  @note
		*    - The quadtree bounding boxes must being inititialized with this patches!
		*
		*  @see
		*    - UpdateBoundingBoxes()
		*/
		PLMATH_API void UpdateVisibility(const PlaneSet &cPlaneSet, QuadtreePatch **ppPatch) const;

		/**
		*  @brief
		*    Returns the bounding box minimum/maximum values
		*
		*  @param[out] vMin
		*    Receives the bounding box minimum value
		*  @param[out] vMax
		*    Receives the bounding box maximum value
		*/
		PLMATH_API void GetBoundingBoxMinMax(Vector3 &vMin, Vector3 &vMax) const;

		/**
		*  @brief
		*    Returns the number of children
		*
		*  @return
		*    Number of children
		*/
		PLMATH_API PLGeneral::uint32 GetNumOfChildren() const;

		/**
		*  @brief
		*    Returns a child
		*
		*  @param[in] nChild
		*    Child to return
		*
		*  @return
		*    The requested child, NULL on error
		*/
		PLMATH_API Quadtree *GetChild(PLGeneral::uint32 nChild) const;


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
		Quadtree(const Quadtree &cSource);

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
		Quadtree &operator =(const Quadtree &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint32  m_nXOffset;			/**< X offset */
		PLGeneral::uint32  m_nYOffset;			/**< Y offset */
		PLGeneral::uint32  m_nXSize;			/**< X size */
		PLGeneral::uint32  m_nYSize;			/**< Y size */
		Quadtree		  *m_pTopmost;			/**< Topmost quadtree (always valid!) */
		Quadtree		  *m_pParent;			/**< Quadtree parent, can be NULL */
		PLGeneral::uint32  m_nNumOfChildren;	/**< Number of children */
		Quadtree		  *m_pChild;			/**< The children, can be NULL */
		Vector3			   m_vBoundingBox[2];	/**< Quadtree bounding box (min/max) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


#endif // __PLMATH_QUADTREE_H__
