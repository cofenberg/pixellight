/*********************************************************\
 *  File: SRPPostProcessing.cpp                          *
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
#include <PLGeneral/Tools/Profiling.h>
#include <PLGeneral/Tools/Stopwatch.h>
#include <PLCore/Base/Class.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLScene/Scene/SNCamera.h>
#include "PLCompositing/SRPBegin.h"
#include "PLCompositing/SceneNodeModifiers/SNMPostProcess.h"
#include "PLCompositing/Shaders/PostProcessing/PostProcessor.h"
#include "PLCompositing/Shaders/PostProcessing/PostProcessManager.h"
#include "PLCompositing/SRPPostProcessing.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
using namespace PLScene;
namespace PLCompositing {


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
	m_pPostProcessor(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
SRPPostProcessing::~SRPPostProcessing()
{
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
	uint32		    nModifier = 0;
	SNMPostProcess *pModifier = static_cast<SNMPostProcess*>(cCamera.GetModifier("PLCompositing::SNMPostProcess", nModifier));
	while (pModifier) {
		// Is this modifier active and the effect weight greater than zero?
		if (pModifier->IsActive() && pModifier->EffectWeight.GetFloat() > 0.0f) {


			// [TODO] If there's an "PLCompositing::SRPDeferredDOF" instance, "PLCompositing::SNMPostProcessDepthOfField" has already been processed -> Find a way to deal with build in post process effects!
			if (GetFirstInstanceOfSceneRendererPassClass("PLCompositing::SRPDeferredDOF") && pModifier->GetClass()->GetClassName() == "PLCompositing::SNMPostProcessDepthOfField") {
				pModifier = static_cast<SNMPostProcess*>(cCamera.GetModifier("PLCompositing::SNMPostProcess", ++nModifier));
				continue;
			}


			// Get the post process manager
			PostProcessManager &cPPM = static_cast<SNMPostProcess*>(pModifier)->GetPostProcessManager();

			// Loop through all post processes
			for (uint32 nPostProcess=0; nPostProcess<cPPM.GetNumOfElements(); nPostProcess++) {
				PostProcess *pPostProcess = cPPM.GetByIndex(nPostProcess);
				if (pPostProcess->IsActive()) {
					// Create post processor if there's currently no one
					if (!m_pPostProcessor)
						m_pPostProcessor = new PostProcessor();

					// Setup the texture format
					m_pPostProcessor->SetTextureFormat(static_cast<SNMPostProcess*>(pModifier)->GetPostProcessManager().GetTextureFormat());

					// Done, we need post processing
					return true;
				}
			}
		}

		// Next modifier, please
		pModifier = static_cast<SNMPostProcess*>(cCamera.GetModifier("PLCompositing::SNMPostProcess", ++nModifier));
	}

	// Done, we need not need post processing
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRPPostProcessing::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Perform post processing?
	if (SNCamera::GetCamera() && IsPostProcessingRequired(*SNCamera::GetCamera()) && m_pPostProcessor) {
		// Get the "PLCompositing::SRPBegin" instance
		SRPBegin *pSRPBegin = static_cast<SRPBegin*>(GetFirstInstanceOfSceneRendererPassClass("PLCompositing::SRPBegin"));
		if (pSRPBegin) {
			// We need up-to-date front render target content, so swap the render targets
			pSRPBegin->SwapRenderTargets();

			// Get the front render target of SRPBegin, this holds the current content
			SurfaceTextureBuffer *pFrontSurfaceTextureBuffer = pSRPBegin->GetFrontRenderTarget();
			if (pFrontSurfaceTextureBuffer && pFrontSurfaceTextureBuffer->GetTextureBuffer()) {
				// Backup the current render target
				Surface *pSurfaceBackup = cRenderer.GetRenderTarget();

				// Ensure alpha is used
				cRenderer.SetColorMask(true, true, true, true);

				// Start stopwatch
				Stopwatch cStopwatch(true);

				// Begin the processing
				if (m_pPostProcessor->BeginProcessing(cRenderer, *pFrontSurfaceTextureBuffer)) {
					// Perform all active post processes in order
					SNCamera *pCamera = SNCamera::GetCamera();
					if (pCamera) {
						// Loop through all modifiers of the camera scene node
						uint32		    nModifier = 0;
						SNMPostProcess *pModifier = static_cast<SNMPostProcess*>(pCamera->GetModifier("PLCompositing::SNMPostProcess", nModifier));
						while (pModifier) {
							// Is this modifier active and the effect weight greater than zero?
							if (pModifier->IsActive() && pModifier->EffectWeight.GetFloat() > 0.0f) {


								// [TODO] If there's an "PLCompositing::SRPDeferredDOF" instance, "PLCompositing::SNMPostProcessDepthOfField" has already been processed -> Find a way to deal with build in post process effects!
								if (GetFirstInstanceOfSceneRendererPassClass("PLCompositing::SRPDeferredDOF") && pModifier->GetClass()->GetClassName() == "PLCompositing::SNMPostProcessDepthOfField") {
									pModifier = static_cast<SNMPostProcess*>(pCamera->GetModifier("PLCompositing::SNMPostProcess", ++nModifier));
									continue;
								}


								SNMPostProcess *pPostProcessModifier = static_cast<SNMPostProcess*>(pModifier);

								// Get the post process manager
								PostProcessManager &cPPM = pPostProcessModifier->GetPostProcessManager();

								// Loop through all post processes
								bool bSetParameters = true;
								for (uint32 nPostProcess=0; nPostProcess<cPPM.GetNumOfElements(); nPostProcess++) {
									PostProcess *pPostProcess = cPPM.GetByIndex(nPostProcess);
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
							pModifier = static_cast<SNMPostProcess*>(pCamera->GetModifier("PLCompositing::SNMPostProcess", ++nModifier));
						}
					}

					// End the processing
					m_pPostProcessor->EndProcessing();

					// Reset current render target
					if (cRenderer.SetRenderTarget(pSurfaceBackup)) {
						// Draw the result on screen
						m_pPostProcessor->DrawResult(cRenderer);
					}
				}

				// Update profiling information
				Profiling::GetInstance()->Set(GetClass()->GetClassName(), "PostProcessTime", String::Format("%.3f ms", cStopwatch.GetMilliseconds()));
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing
