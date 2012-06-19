/*********************************************************\
 *  File: ShaderFunctionIllumination.cpp                 *
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
#include <PLCore/Base/ClassManager.h>
#include <PLRenderer/Renderer/ProgramWrapper.h>
#include <PLScene/Scene/SNLight.h>
#include <PLScene/Visibility/VisNode.h>
#include <PLVolume/Volume.h>
#include <PLVolume/Scene/SNVolume.h>
#include "PLVolumeRenderer/SRPVolume.h"
#include "PLVolumeRenderer/Illumination/ShaderFunctionIllumination.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLGraphics;
using namespace PLMath;
using namespace PLScene;
using namespace PLRenderer;
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShaderFunctionIllumination)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShaderFunctionIllumination::ShaderFunctionIllumination()
{
}

/**
*  @brief
*    Destructor
*/
ShaderFunctionIllumination::~ShaderFunctionIllumination()
{
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunction functions               ]
//[-------------------------------------------------------]
void ShaderFunctionIllumination::SetProgram(Program &cProgram, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, SRPVolume &cSRPVolume)
{
	// Get simplified GPU program wrapper interface
	ProgramWrapper &cProgramWrapper = static_cast<ProgramWrapper&>(cProgram);

	// Get the volume scene node
	PLVolume::SNVolume *pSNVolume = static_cast<PLVolume::SNVolume*>(cVisNode.GetSceneNode());
	if (!pSNVolume)
		return;	// Early escape, there's no sense in continuing

	// Get the volume resource
	PLVolume::Volume *pVolume = pSNVolume->GetVolume();
	if (!pVolume)
		return;	// Early escape, there's no sense in continuing

	// Light
	Color3 cLightColor = Color3::Black;	// Light color
	{ // Get a list of all visible scene node instances intersecting with the given scene node
		const Class *pClass = ClassManager::GetInstance()->GetClass("PLScene::SNDirectionalLight");
		if (pClass) {
			Array<const VisNode*> lstIntersecting;
			cSRPVolume.GetIntersectingInstancesOf(cCullQuery, *pSNVolume, *pClass, lstIntersecting);
			if (lstIntersecting.GetNumOfElements()) {
				// Get the light color
				const VisNode &cLightVisNode = *lstIntersecting[0];
				cLightColor = static_cast<SNLight*>(cLightVisNode.GetSceneNode())->Color.Get();
			}
		}
	}

	// Set light color
	cProgramWrapper.Set("LightColor", cLightColor);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer
