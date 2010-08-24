/*********************************************************\
 *  File: GMMSurfaceLevel.h                              *
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


#ifndef __PLSCENE_SCENENODE_GMMSURFACELEVEL_H__
#define __PLSCENE_SCENENODE_GMMSURFACELEVEL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/PLScene.h"


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
namespace PLScene {


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
			PLGeneral::uint32		*pnIndexBuffer;			/**< Can be NULL */
			PLGeneral::uint32		 nIndexBufferSize;
			PLRenderer::IndexBuffer *pIndexBuffer;			/**< Can be NULL */

			PLGeneral::uint32		*pnCornerIndexBuffer;	/**< Can be NULL */
			PLGeneral::uint32		 nCornerIndexSize;
			PLRenderer::IndexBuffer *pCornerIndexBuffer;	/**< Can be NULL */
		};

		/**
		*  @brief
		*    GMM surface level linking piece
		**/
		struct LinkingPiece {
			PLGeneral::uint32		*pnIndexBuffer[4];		/**< Can be NULL */
			PLGeneral::uint32		 nIndexBufferSize[4];
			PLRenderer::IndexBuffer *pIndexBuffer[4];		/**< Can be NULL */
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
		PLS_API GMMSurfaceLevel(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API ~GMMSurfaceLevel();

		/**
		*  @brief
		*    Builds the bodies
		*
		*  @param[in] nLevel
		*    Number of geo mip map levels
		*  @param[in] nPatchSize
		*    Patch size
		*/
		PLS_API void BuildBodies(PLGeneral::uint32 nLevel, PLGeneral::uint32 nPatchSize);

		/**
		*  @brief
		*    Builds the linkers
		*
		*  @param[in] nLevel
		*    Number of geo mip map levels
		*  @param[in] nPatchSize
		*    Patch size
		*/
		PLS_API void BuildLinkers(PLGeneral::uint32 nLevel, PLGeneral::uint32 nPatchSize);


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
		PLGeneral::uint32	  m_nLevels;	/**< Number of levels */
		BodyPiece			 *m_pBodies;	/**< Bodies, can be NULL */
		LinkingPiece		 *m_pLinkers;	/**< Linkers, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_GMMSURFACELEVEL_H__
