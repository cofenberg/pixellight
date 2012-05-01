/*********************************************************\
 *  File: GMMSurfaceLevel.h                              *
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


#ifndef __PLNATURE_SCENENODE_GMMSURFACELEVEL_H__
#define __PLNATURE_SCENENODE_GMMSURFACELEVEL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLNature/PLNature.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
	class IndexBuffer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLNature {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    GMM surface geometrically mip mapping level
*/
class GMMSurfaceLevel {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class GMMSurface;


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    GMM surface level body piece
		**/
		struct BodyPiece {
			PLCore::uint32			*pnIndexBuffer;			/**< Can be a null pointer */
			PLCore::uint32			 nIndexBufferSize;
			PLRenderer::IndexBuffer *pIndexBuffer;			/**< Can be a null pointer */

			PLCore::uint32			*pnCornerIndexBuffer;	/**< Can be a null pointer */
			PLCore::uint32			 nCornerIndexSize;
			PLRenderer::IndexBuffer *pCornerIndexBuffer;	/**< Can be a null pointer */
		};

		/**
		*  @brief
		*    GMM surface level linking piece
		**/
		struct LinkingPiece {
			PLCore::uint32			*pnIndexBuffer[4];		/**< Can be a null pointer */
			PLCore::uint32			 nIndexBufferSize[4];
			PLRenderer::IndexBuffer *pIndexBuffer[4];		/**< Can be a null pointer */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Renderer to use
		*/
		PLNATURE_API GMMSurfaceLevel(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		PLNATURE_API ~GMMSurfaceLevel();

		/**
		*  @brief
		*    Builds the bodies
		*
		*  @param[in] nLevel
		*    Number of geo mip map levels
		*  @param[in] nPatchSize
		*    Patch size
		*/
		PLNATURE_API void BuildBodies(PLCore::uint32 nLevel, PLCore::uint32 nPatchSize);

		/**
		*  @brief
		*    Builds the linkers
		*
		*  @param[in] nLevel
		*    Number of geo mip map levels
		*  @param[in] nPatchSize
		*    Patch size
		*/
		PLNATURE_API void BuildLinkers(PLCore::uint32 nLevel, PLCore::uint32 nPatchSize);


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Side
		*/
		enum ESide {
			Right,	/**< Right side */
			Top,	/**< Top side */
			Left,	/**< Left side */
			Bottom	/**< Bottom side */
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::Renderer *m_pRenderer;	/**< Used renderer (always valid!) */
		PLCore::uint32		  m_nLevels;	/**< Number of levels */
		BodyPiece			 *m_pBodies;	/**< Bodies, can be a null pointer */
		LinkingPiece		 *m_pLinkers;	/**< Linkers, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLNature


#endif // __PLNATURE_SCENENODE_GMMSURFACELEVEL_H__
