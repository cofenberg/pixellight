/*********************************************************\
 *  File: GMMSurfacePatch.h                              *
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


#ifndef __PLSCENE_SCENENODE_GMMSURFACEPATCH_H__
#define __PLSCENE_SCENENODE_GMMSURFACEPATCH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Quadtree.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class GMMSurface;
class GMMSurfacePatch;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GMM surface patch
*/
class GMMSurfacePatch : public PLMath::QuadtreePatch {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class GMMSurface;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether the patch is active or not
		*
		*  @return
		*    'true' if the patch is active, else 'false'
		*/
		PLS_API bool IsActive() const;

		/**
		*  @brief
		*    Sets whether the patch is active or not
		*
		*  @param[in] bActive
		*    Should the patch be active?
		*/
		PLS_API void SetActive(bool bActive = true);

		/**
		*  @brief
		*    Computes the variance of each mip map level
		*
		*  @param[out] nOffset
		*    Will receive the offset
		*/
		PLS_API void ComputeVariance(PLCore::uint32 &nOffset);

		/**
		*  @brief
		*    Updates the patch bounding box
		*/
		PLS_API void UpdateBoundingBox();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cGMMSurface
		*    Owner GMM surface of this patch
		*/
		GMMSurfacePatch(GMMSurface &cGMMSurface);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GMMSurfacePatch();

		/**
		*  @brief
		*    Initializes the GMM surface patch
		*/
		void Init();

		/**
		*  @brief
		*    Creates the GMM surface patch
		*
		*  @param[in] nXOffset
		*    X offset of this patch in the height map
		*  @param[in] nYOffset
		*    Y offset of this patch in the height map
		*  @param[in] nOffset
		*    Current offset (is increased inside the function)
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Create(PLCore::uint32 nXOffset, PLCore::uint32 nYOffset, PLCore::uint32 &nOffset);

		/**
		*  @brief
		*    Kills the GMM surface patch
		*/
		void Destroy();

		/**
		*  @brief
		*    Updates the GMM surface patch
		*
		*  @note
		*    - Must be done before the GMM surface patch is drawn!!
		*/
		void Update();

	
	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool			 m_bActive;			/**< Is the patch active? */
		PLCore::uint32	 m_nLevel;			/**< Current geo mip map level */
		PLMath::Vector3	 m_vCenter;			/**< Patch center */
		PLCore::uint32	 m_nOffset;			/**< Surface vertex offset */
		PLCore::uint32	 m_nXOffset;		/**< X offset in the height map */
		PLCore::uint32	 m_nYOffset;		/**< Y offset in the height map */
		float			*m_pVariance;		/**< Height variance for each level, can be a null pointer */
		GMMSurface		*m_pGMMSurface;		/**< Owner GMM surface of this patch (always valid!) */
		GMMSurfacePatch	*m_pNeighbour[4];	/**< Neighbour patches, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_GMMSURFACEPATCH_H__
