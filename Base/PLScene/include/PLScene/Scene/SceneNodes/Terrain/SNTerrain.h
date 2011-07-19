/*********************************************************\
 *  File: SNTerrain.h                                    *
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


#ifndef __PLSCENE_SCENENODE_TERRAIN_H__
#define __PLSCENE_SCENENODE_TERRAIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Loadable.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Image;
}
namespace PLScene {
	class GMMSurface;
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
*    Terrain scene node
*/
class SNTerrain : public SceneNode, public PLCore::Loadable {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	// [TODO] Add additional functions to the interface and remove this
	friend class TerrainLoaderPL;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNTerrain, "PLScene", PLScene::SceneNode, "Terrain scene node")
		// Attributes
		pl_attribute(Filename,	PLCore::String, "",	ReadWrite,	GetSet,	"Terrain filename",	"Type='Terrain'")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLCore::String GetFilename() const;
		PLS_API void SetFilename(const PLCore::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNTerrain();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNTerrain();

		/**
		*  @brief
		*    Returns the GMM surface
		*
		*  @return
		*    The terrain GMM surface, can be a null pointer
		*/
		PLS_API GMMSurface *GetGMMSurface() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Loads the height map
		*
		*  @param[in]  sHeightMap
		*    Filename of the height map to load
		*  @param[out] cHeightMap
		*    Receives the loaded height map
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadHeightMap(const PLCore::String &sHeightMap, PLGraphics::Image &cHeightMap);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String  m_sFilename;	/**< Terrain filename */
		float		   *m_pfHeightMap;	/**< Heightmap, can be a null pointer */
		GMMSurface	   *m_pGMMSurface;	/**< Terrain GMM surface, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawSolid(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);


	//[-------------------------------------------------------]
	//[ Private virtual SceneNode functions                   ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction();


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool Unload();
		PLS_API virtual PLCore::String GetLoadableTypeName() const;


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::Loadable functions            ]
	//[-------------------------------------------------------]
	private:
		virtual bool CallLoadable(PLCore::File &cFile, PLCore::Loader &cLoader, const PLCore::String &sMethod, const PLCore::String &sParams);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_TERRAIN_H__
