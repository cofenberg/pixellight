/*********************************************************\
 *  File: SRPPostProcessing.cpp                          *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Tools/Timing.h>
#include <PLGeneral/Tools/Profiling.h>
#include <PLGeneral/Tools/Stopwatch.h>
#include <PLGeneral/System/System.h>
#include <PLRenderer/Renderer/Renderer.h>
#include "PLScene/Scene/SNCamera.h"
#include "PLScene/Scene/SceneNodeModifier.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMPostProcess.h"
#include "PLScene/Compositing/PostProcessing/PostProcessor.h"
#include "PLScene/Compositing/PostProcessing/PostProcessManager.h"
#include "PLScene/Compositing/General/SRPPostProcessing.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRPPostProcessing)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRPPostProcessing::SRPPostProcessing() :
	m_pColorMap(NULL),
	m_pPostProcessor(NULL),
	m_pSurfaceT(NULL)
{
}

/**
*  @brief
*    Destructor
*/
SRPPostProcessing::~SRPPostProcessing()
{
	if (m_pColorMap)
		delete m_pColorMap;
	if (m_pPostProcessor)
		delete m_pPostProcessor;
}

/**
*  @brief
*    Returns the post processor
*/
PostProcessor *SRPPostProcessing::GetPostProcessor()
{
	if (!m_pPostProcessor)
		m_pPostProcessor = new PostProcessor();
	return m_pPostProcessor;
}

/**
*  @brief
*    Sets another render target if required
*/
bool SRPPostProcessing::SetRenderTarget(Renderer &cRenderer)
{
	// Do we really perform post processing?
	if (SNCamera::GetCamera() && IsPostProcessingRequired(*SNCamera::GetCamera())) {
		if (m_pPostProcessor) {
			// Get the size of the current render target
			const Vector2i vRTSize = cRenderer.GetRenderTarget()->GetSize();
			if (vRTSize.x != 0 && vRTSize.y != 0) {
				// Create/update the color map
				if (m_pColorMap) {
					// Do we need to recreate the color map?
					if (m_pColorMap->GetSize()   != vRTSize ||
						m_pColorMap->GetFormat() != m_pPostProcessor->GetTextureFormat()) {
						// Yes! Recreate it!
						delete m_pColorMap;
						m_pColorMap = cRenderer.CreateSurfaceTextureBufferRectangle(vRTSize, m_pPostProcessor->GetTextureFormat());
					}
				} else {
					m_pColorMap = cRenderer.CreateSurfaceTextureBufferRectangle(vRTSize, m_pPostProcessor->GetTextureFormat());
				}
			} else {
				// Invalid render target dimension, so no color map, please
				if (m_pColorMap) {
					delete m_pColorMap;
					m_pColorMap = NULL;
				}
			}

			// Is there a valid color map we can render in?
			if (m_pColorMap) {
				// Backup current render target and set a new one
				m_pSurfaceT = cRenderer.GetRenderTarget();
				return cRenderer.SetRenderTarget(m_pColorMap);
			} else {
				// Error!
				return false;
			}
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether or not post processing is required
*/
bool SRPPostProcessing::IsPostProcessingRequired(SNCamera &cCamera)
{
	// Loop through all modifiers of the camera scene node
	uint32			   nModifier = 0;
	SceneNodeModifier *pModifier = cCamera.GetModifier("PLScene::SNMPostProcess", nModifier);
	while (pModifier) {
		// Is this modifier active?
		if (pModifier->IsActive()) {
			// Get the post process manager
			PostProcessManager &cPPM = ((SNMPostProcess*)pModifier)->GetPostProcessManager();

			// Loop through all post processes
			for (uint32 nPostProcess=0; nPostProcess<cPPM.GetNumOfElements(); nPostProcess++) {
				PostProcess *pPostProcess = cPPM.Get(nPostProcess);
				if (pPostProcess->IsActive()) {
					// Create post processor if there's currently no one
					if (!m_pPostProcessor)
						m_pPostProcessor = new PostProcessor();

					// Setup the texture format
					m_pPostProcessor->SetTextureFormat(((SNMPostProcess*)pModifier)->GetPostProcessManager().GetTextureFormat());

					// Done, we need post processing
					return true;
				}
			}
		}

		// Next modifier, please
		pModifier = cCamera.GetModifier("PLScene::SNMPostProcess", ++nModifier);
	}

	// Done, we need not need post processing
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual SceneRendererPass functions           ]
//[-------------------------------------------------------]
void SRPPostProcessing::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Perform post process
	if (m_pColorMap && m_pPostProcessor && SNCamera::GetCamera() && IsPostProcessingRequired(*SNCamera::GetCamera())) {
		// Ensure alpha is used
		cRenderer.SetColorMask(true, true, true, true);

		// Start stopwatch
		Stopwatch cStopwatch;
		cStopwatch.Start();

		// Begin the processing
		if (m_pPostProcessor->BeginProcessing(cRenderer, *m_pColorMap)) {
			// Perform all active post processes in order
			SNCamera *pCamera = SNCamera::GetCamera();
			if (pCamera) {
				// Loop through all modifiers of the camera scene node
				uint32			   nModifier = 0;
				SceneNodeModifier *pModifier = pCamera->GetModifier("PLScene::SNMPostProcess", nModifier);
				while (pModifier) {
					// Is this modifier active?
					if (pModifier->IsActive()) {
						SNMPostProcess *pPostProcessModifier = (SNMPostProcess*)pModifier;

						// Get the post process manager
						PostProcessManager &cPPM = pPostProcessModifier->GetPostProcessManager();

						// Loop through all post processes
						bool bSetParameters = true;
						for (uint32 nPostProcess=0; nPostProcess<cPPM.GetNumOfElements(); nPostProcess++) {
							PostProcess *pPostProcess = cPPM.Get(nPostProcess);
							if (pPostProcess->IsActive()) {
								// Set post process settings now?
								if (bSetParameters) {
									pPostProcessModifier->SetParameters();
									bSetParameters = false;
								}

								// Process this post process
								m_pPostProcessor->Process(*pPostProcess);
							}
						}
					}

					// Next modifier, please
					pModifier = pCamera->GetModifier("PLScene::SNMPostProcess", ++nModifier);
				}
			}

			// End the processing
			m_pPostProcessor->EndProcessing();

			// Reset current render target
			if (cRenderer.SetRenderTarget(m_pSurfaceT)) {
				// Draw the result on screen
				m_pPostProcessor->DrawResult(cRenderer);
			}
		}

		// Stop stopwatch
		cStopwatch.Stop();

		// Update profiling information
		Profiling::GetInstance()->Set(GetClass()->GetClassName(), "PostProcessTime", String::Format("%.3f ms", cStopwatch.GetMilliseconds()));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
