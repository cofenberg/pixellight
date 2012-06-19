/*********************************************************\
 *  File: SNVolume.cpp                                   *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3i.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/RendererContext.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLVolume/VolumeHandler.h"
#include "PLVolume/VolumeManager.h"
#include "PLVolume/TransferFunctionControl/TransferFunctionChannel.h"
#include "PLVolume/TransferFunctionControl/TransferFunctionControl.h"
#include "PLVolume/Scene/SNVolume.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace PLVolume {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNVolume)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNVolume::GetVolumeFilename() const
{
	return m_sVolumeFilename;
}

void SNVolume::SetVolumeFilename(const String &sValue)
{
	if (m_sVolumeFilename != sValue) {
		m_sVolumeFilename = sValue;

		// Load/reload the volume
		Load();
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNVolume::SNVolume() :
	VolumeFilenameSave(this),
	LoaderParameters(this),
	VolumeFilename(this),
	SampleRateFactor(this),
	RayTraversal(this),
	Opacity(this),
	IsosurfaceValue(this),
	Reconstruction(this),
	VolumeTextureLOD(this),
	Shading(this),
	Classification(this),
	ScalarClassificationThreshold(this),
	Gradient(this),
	PostClassificationGradient(this),
	Illumination(this),
	Flags(this),
	AABBMin(this),
	AABBMax(this),
	m_pVolumeHandler(new VolumeHandler())
{
	// Overwritten SceneNode variables
	SetAABoundingBox(AABoundingBox(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f));
}

/**
*  @brief
*    Destructor
*/
SNVolume::~SNVolume()
{
	// Destroy the volume resource handler instance
	delete m_pVolumeHandler;
}

/**
*  @brief
*    Returns the used volume resource
*/
Volume *SNVolume::GetVolume() const
{
	return m_pVolumeHandler->GetResource();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads/reloads the sound
*/
void SNVolume::Load()
{
	// Get/create a new volume resource instance (if there was a previous one, it will be destroyed by the manager as soon as no longer referenced)
	bool bNewCreated = false;
	Volume *pVolume = VolumeManager::GetInstance()->GetByName(m_sVolumeFilename);
	if (!pVolume) {
		pVolume = VolumeManager::GetInstance()->Create(m_sVolumeFilename);
		bNewCreated = true;
	}

	// Give our volume resource handler the new resource (it's possible that the previous volume resource is now going to be destroyed)
	m_pVolumeHandler->SetResource(pVolume);

	// [TODO] Handle varying loader parameters
	if (pVolume && bNewCreated) {
		// Setup volume
		if (pVolume) {
			// Load in the volume data
			if (pVolume->LoadByFilename(m_sVolumeFilename, LoaderParameters.Get())) {
				// [TODO] Check this situation when the loader parameters do not match
				// Try again without parameters?
				if (!pVolume->GetVolumeImage().GetBuffer())
					pVolume->LoadByFilename(m_sVolumeFilename);

				// Create the texture buffer instance by using our image data
				SceneContext *pSceneContext = GetSceneContext();
				if (pSceneContext) {
					// Get the renderer and renderer capabilities instance
					Renderer &cRenderer = pSceneContext->GetRendererContext().GetRenderer();

					// [TODO] Just a test (volume image to texture buffer)
					TextureBuffer *pTextureBuffer = pVolume->GetVolumeTextureBuffer(cRenderer, !(GetFlags() & NoTextureCompression), !(GetFlags() & NoTextureMipmapping));

					{ // Save volume?
						const String sVolumeFilenameSave = VolumeFilenameSave.Get();
						if (sVolumeFilenameSave.GetLength())
							pVolume->SaveByFilename(sVolumeFilenameSave);
					}
				}
			}
		}
	}

	// [TODO] Just a test
	if (pVolume) {
		// Set the default transfer function configuration
		pVolume->GetTransferFunctionControl().SetDefaultConfiguration();
	}

	// Set the scale of the scene node?
	if (pVolume && !(GetFlags() & NoVolumeScale)) {
		// Get the size of one voxel (without metric, but usually one unit is equal to one meter)
		const Vector3 &vVoxelSize = pVolume->GetVoxelSize();

		// Get the image size aka the number of voxels along each diagonal
		const Vector3i &vImageSize = pVolume->GetVolumeImageSize();

		// Set the scale of the scene node
		SetScale(Vector3(vVoxelSize.x*vImageSize.x, vVoxelSize.y*vImageSize.y, vVoxelSize.z*vImageSize.z));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
