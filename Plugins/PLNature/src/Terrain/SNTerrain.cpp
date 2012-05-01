/*********************************************************\
 *  File: SNTerrain.cpp                                  *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Log/Log.h>
#include <PLCore/Tools/Loader.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLGraphics/Image/ImageEffects.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLScene/Visibility/VisNode.h>
#include <PLScene/Scene/SNCamera.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLNature/Terrain/TerrainLoader.h"
#include "PLNature/Terrain/GMMSurface.h"
#include "PLNature/Terrain/SNTerrain.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace PLNature {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNTerrain)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNTerrain::GetFilename() const
{
	return m_sFilename;
}

void SNTerrain::SetFilename(const String &sValue)
{
	if (m_sFilename != sValue) {
		m_sFilename = sValue;
		if (IsInitialized())
			LoadByFilename(m_sFilename);
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNTerrain::SNTerrain() :
	Filename(this),
	m_pfHeightMap(nullptr),
	m_pGMMSurface(nullptr)
{
	// Set draw function flags
	SetDrawFunctionFlags(static_cast<uint8>(GetDrawFunctionFlags() | UseDrawSolid));
}

/**
*  @brief
*    Destructor
*/
SNTerrain::~SNTerrain()
{
	Unload();

	// Free GMM surface
	if (m_pGMMSurface)
		delete m_pGMMSurface;
}

/**
*  @brief
*    Returns the GMM surface
*/
GMMSurface *SNTerrain::GetGMMSurface() const
{
	return m_pGMMSurface;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads the height map
*/
bool SNTerrain::LoadHeightMap(const String &sHeightMap, Image &cHeightMap)
{
	// Check parameter
	if (sHeightMap.GetLength()) {
		// Load height map
		if (cHeightMap.LoadByFilename(sHeightMap)) {
			// Get the image buffer
			ImageBuffer *pImageBuffer = cHeightMap.GetBuffer();
			if (pImageBuffer) {
				// Get the current data and color format of the height map
				EDataFormat  nDataFormat  = pImageBuffer->GetDataFormat();
				EColorFormat nColorFormat = pImageBuffer->GetColorFormat();

				// Check data format - must be DataByte
				if (nDataFormat != DataByte) {
					// Write a warning into the log
					PL_LOG(Warning, "Height map '" + sHeightMap + "': Wrong type! Unsigned byte required! "
									"Image is converted automatically.")

					// Set the new data format
					nDataFormat = DataByte;
				}

				// Check color format - must be ColorGrayscale
				if (nColorFormat != ColorGrayscale) {
					// Is this image currently using a palette?
					if (nColorFormat == ColorPalette) {
						// Write a warning into the log
						PL_LOG(Warning, sHeightMap + String::Format(": Height map is using a palette. Image is converted automatically into none palette."))
					} else {
						// Write a warning into the log
						PL_LOG(Warning, sHeightMap + String::Format(": Height map number of color components is '%d' "
							"but 1 is required! Image is converted automatically.", pImageBuffer->GetComponentsPerPixel()))
					}

					// Set the new color format
					nColorFormat = ColorGrayscale;
				}

				// Do we need to convert the image right now?
				if (nDataFormat != pImageBuffer->GetDataFormat() || nColorFormat != pImageBuffer->GetColorFormat()) {
					// Convert the image buffer
					if (!ImageEffects::Convert(nDataFormat, nColorFormat).Apply(*pImageBuffer))
						return false; // Error!
				}

				// Done
				return true;
			}
		} else {
			PL_LOG(Error, "Can't load the height map: " + sHeightMap)
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNTerrain::DrawSolid(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SceneNode::DrawSolid(cRenderer, pVisNode);

	if (m_pGMMSurface && SNCamera::GetCamera()) {
		// Set world matrix
		if (pVisNode) {
			FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
			if (pFixedFunctions)
				pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, pVisNode->GetWorldMatrix());
		}

		// Set viewer position
		m_pGMMSurface->SetViewerPos(GetTransform().GetInverseMatrix()*SNCamera::GetCamera()->GetTransform().GetPosition());

		// Update GMM surface
		m_pGMMSurface->Update();

		// Draw GMM surface
		m_pGMMSurface->Draw();
	}
}


//[-------------------------------------------------------]
//[ Private virtual SceneNode functions                   ]
//[-------------------------------------------------------]
void SNTerrain::InitFunction()
{
	// Call base implementation
	SceneNode::InitFunction();

	// Create the terrain
	if (!m_pGMMSurface)
		m_pGMMSurface = new GMMSurface(GetSceneContext()->GetRendererContext().GetRenderer());

	// Load the terrain
	LoadByFilename(m_sFilename);
}


//[-------------------------------------------------------]
//[ Public virtual PLCore::Loadable functions             ]
//[-------------------------------------------------------]
bool SNTerrain::Unload()
{
	// Destroy the terrain
	if (m_pGMMSurface)
		m_pGMMSurface->Destroy();
	if (m_pfHeightMap) {
		delete [] m_pfHeightMap;
		m_pfHeightMap = nullptr;
	}

	// Call base implementation
	return Loadable::Unload();
}

String SNTerrain::GetLoadableTypeName() const
{
	static const String sString = "Terrain";
	return sString;
}


//[-------------------------------------------------------]
//[ Private virtual PLCore::Loadable functions            ]
//[-------------------------------------------------------]
bool SNTerrain::CallLoadable(File &cFile, Loader &cLoader, const String &sMethod, const String &sParams)
{
	// Get the loader implementation
	LoaderImpl *pLoaderImpl = cLoader.GetImpl();
	if (pLoaderImpl) {
		// Load
		if (sParams.GetLength()) {
			pLoaderImpl->CallMethod(sMethod, "Param0=\"" + Type<SNTerrain&>::ConvertToString(*this) + "\" Param1=\"" + Type<File&>::ConvertToString(cFile) + "\" " + sParams);
			return true;
		} else {
			Params<bool, SNTerrain&, File&> cParams(*this, cFile);
			pLoaderImpl->CallMethod(sMethod, cParams);
			return cParams.Return;
		}
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLNature
