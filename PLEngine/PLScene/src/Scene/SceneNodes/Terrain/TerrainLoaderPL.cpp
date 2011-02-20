/*********************************************************\
 *  File: TerrainLoaderPL.cpp                            *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Xml/Xml.h>
#include <PLGeneral/Log/Log.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Material/MaterialHandler.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodes/Terrain/GMMSurface.h"
#include "PLScene/Scene/SceneNodes/Terrain/SNTerrain.h"
#include "PLScene/Scene/SceneNodes/Terrain/TerrainLoaderPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(TerrainLoaderPL)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool TerrainLoaderPL::Load(SNTerrain &cSNTerrain, File &cFile)
{
	// Load XML document
	XmlDocument cDocument;
	if (cDocument.Load(cFile)) {
		// Get terrain element
		const XmlElement *pTerrainElement = cDocument.GetFirstChildElement("Terrain");
		if (pTerrainElement) {
			// Get the format version
			int nVersion = pTerrainElement->GetAttribute("Version").GetInt();

			// Unkown
			if (nVersion > 1) {
				PL_LOG(Error, cDocument.GetValue() + ": " + UnknownFormatVersion)

			// 1 (current)
			} else if (nVersion == 1) {
				return LoadV1(cSNTerrain, *pTerrainElement);

			// ""/0 (same format as 1)
			} else if (nVersion == 0) {
				// [DEPRECATED]
				PL_LOG(Warning, cDocument.GetValue() + ": " + DeprecatedFormatVersion)
				return LoadV1(cSNTerrain, *pTerrainElement);

			// No longer supported format version
			} else if (nVersion >= 0) {
				PL_LOG(Warning, cDocument.GetValue() + ": " + NoLongerSupportedFormatVersion)

			// Invalid format version (negative!)
			} else {
				PL_LOG(Error, cDocument.GetValue() + ": " + InvalidFormatVersion)
			}
		} else PL_LOG(Error, "Can't find 'Terrain' element")
	} else PL_LOG(Error, cDocument.GetValue() + ": " + cDocument.GetErrorDesc())

	// Error!
	return false;
}

bool TerrainLoaderPL::Save(SNTerrain &cSNTerrain, File &cFile)
{
	// [TODO] Implement me!
	return false; // Error!
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
TerrainLoaderPL::TerrainLoaderPL() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
TerrainLoaderPL::~TerrainLoaderPL()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader implementation for format version 1
*/
bool TerrainLoaderPL::LoadV1(SNTerrain &cSNTerrain, const XmlElement &cTerrainElement) const
{
	// HeightMap
	String sHeightMap;
	const XmlNode *pNode = cTerrainElement.GetFirstChild("HeightMap");
	if (pNode) {
		pNode = pNode->GetFirstChild();
		if (pNode && pNode->GetType() == XmlNode::Text && pNode->GetValue().GetLength())
			sHeightMap = pNode->GetValue();
	}

	// Material
	String sMaterial;
	pNode = cTerrainElement.GetFirstChild("Material");
	if (pNode) {
		pNode = pNode->GetFirstChild();
		if (pNode && pNode->GetType() == XmlNode::Text && pNode->GetValue().GetLength())
			sMaterial = pNode->GetValue();
	}

	// Scale
	Vector3 vScale(1.0f, 1.0f, 1.0f);
	pNode = cTerrainElement.GetFirstChild("Scale");
	if (pNode) {
		pNode = pNode->GetFirstChild();
		if (pNode && pNode->GetType() == XmlNode::Text && pNode->GetValue().GetLength())
			vScale.FromString(pNode->GetValue());
	}

	// Load the height map and create the terrain
	Image cHeightMap;
	if (cSNTerrain.LoadHeightMap(sHeightMap, cHeightMap)) {
		// Destroy the old heigh field
		if (cSNTerrain.m_pfHeightMap) {
			delete [] cSNTerrain.m_pfHeightMap;
			cSNTerrain.m_pfHeightMap = nullptr;
		}

		// Get the image buffer
		ImageBuffer *pImageBuffer = cHeightMap.GetBuffer();
		if (pImageBuffer) {
			// Create the heigh field using the read image
			uint32 nWidth  = pImageBuffer->GetSize().x;
			uint32 nHeight = pImageBuffer->GetSize().y;
			uint32 nSize   = nWidth*nHeight;
			cSNTerrain.m_pfHeightMap = new float[nSize];
			const uint8 *pData = pImageBuffer->GetData();
			float *pHeighField = cSNTerrain.m_pfHeightMap;
			float fYScale      = vScale.y;

			// Initialize min/max
			*pHeighField = (*pData)*fYScale;
			float fYMin = *pHeighField;
			float fYMax = fYMin;
			pData++;
			pHeighField++;

			// Loop through the data
			for (uint32 i=1; i<nSize; i++) {
				// Set heigh field data
				*pHeighField = static_cast<float>((*pData))*fYScale;

				// Check min/max
				if (fYMin > *pHeighField)
					fYMin = *pHeighField;
				if (fYMax < *pHeighField)
					fYMax = *pHeighField;

				// Next, please
				pData++;
				pHeighField++;
			}

			// Set general standard values
			uint32 nPatchSize = 32;
			uint32 nLevels     = 6;

			// Create the GMM surface
			cSNTerrain.m_pGMMSurface->Create(nWidth, cSNTerrain.m_pfHeightMap, nPatchSize, nLevels);
			cSNTerrain.m_pGMMSurface->GetMaterialHandler().SetResource(cSNTerrain.GetSceneContext()->GetRendererContext().GetMaterialManager().LoadResource(sMaterial));

			// Setup the bounding box
			cSNTerrain.SetAABoundingBox(AABoundingBox(0.0f, fYMin, 0.0f, static_cast<float>(nWidth), fYMax, static_cast<float>(nHeight)));
		}
	} else {
		// Setup the bounding box
		cSNTerrain.SetAABoundingBox(AABoundingBox(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f));
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
