/*********************************************************\
 *  File: SNTerrain.h                                    *
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


#ifndef __PLNATURE_SCENENODE_TERRAIN_H__
#define __PLNATURE_SCENENODE_TERRAIN_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Tools/Loadable.h>
#include <PLScene/Scene/SceneNode.h>
#include "PLNature/PLNature.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Image;
}
namespace PLNature {
	class GMMSurface;
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
*    Terrain scene node
*/
class SNTerrain : public PLScene::SceneNode, public PLCore::Loadable {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	// [TODO] Add additional functions to the interface and remove this
	friend class TerrainLoaderPL;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLNATURE_RTTI_EXPORT, SNTerrain, "PLNature", PLScene::SceneNode, "Terrain scene node")
		// Attributes
		pl_attribute(Filename,	PLCore::String, "",	ReadWrite,	GetSet,	"Terrain filename",	"Type='Terrain'")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLNATURE_API PLCore::String GetFilename() const;
		PLNATURE_API void SetFilename(const PLCore::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLNATURE_API SNTerrain();

		/**
		*  @brief
		*    Destructor
		*/
		PLNATURE_API virtual ~SNTerrain();

		/**
		*  @brief
		*    Returns the GMM surface
		*
		*  @return
		*    The terrain GMM surface, can be a null pointer
		*/
		PLNATURE_API GMMSurface *GetGMMSurface() const;


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
		float		   *m_pfHeightMap;	/**< Height map, can be a null pointer */
		GMMSurface	   *m_pGMMSurface;	/**< Terrain GMM surface, can be a null pointer */


	//[-------------------------------------------------------]
	//[ Public virtual PLScene::SceneNode functions           ]
	//[-------------------------------------------------------]
	public:
		PLNATURE_API virtual void DrawSolid(PLRenderer::Renderer &cRenderer, const PLScene::VisNode *pVisNode = nullptr) override;


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction() override;


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLNATURE_API virtual bool Unload() override;
		PLNATURE_API virtual PLCore::String GetLoadableTypeName() const override;


	//[-------------------------------------------------------]
	//[ Private virtual PLCore::Loadable functions            ]
	//[-------------------------------------------------------]
	private:
		virtual bool CallLoadable(PLCore::File &cFile, PLCore::Loader &cLoader, const PLCore::String &sMethod, const PLCore::String &sParams) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLNature


#endif // __PLNATURE_SCENENODE_TERRAIN_H__
