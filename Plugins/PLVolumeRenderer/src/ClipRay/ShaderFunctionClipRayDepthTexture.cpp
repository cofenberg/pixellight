/*********************************************************\
 *  File: ShaderFunctionClipRayDepthTexture.cpp          *
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
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/ProgramWrapper.h>
#include <PLScene/Visibility/VisNode.h>
#include <PLCompositing/SRPBegin.h>
#include "PLVolumeRenderer/SRPVolume.h"
#include "PLVolumeRenderer/ClipRay/ShaderFunctionClipRayDepthTexture.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLRenderer;
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShaderFunctionClipRayDepthTexture)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShaderFunctionClipRayDepthTexture::ShaderFunctionClipRayDepthTexture()
{
}

/**
*  @brief
*    Destructor
*/
ShaderFunctionClipRayDepthTexture::~ShaderFunctionClipRayDepthTexture()
{
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunction functions               ]
//[-------------------------------------------------------]
String ShaderFunctionClipRayDepthTexture::GetSourceCode(const String &sShaderLanguage, ESourceCodeType nSourceCodeType)
{
	// Check requested shader language
	if (sShaderLanguage == GLSL) {
		#include "DepthTexture_GLSL.h"

		// Return the requested source code
		switch (nSourceCodeType) {
			case FragmentShaderBody:
				return sSourceCode_Fragment;

			case FragmentShaderTemplate:
				return sSourceCode_Fragment_Template;
		}
	} else if (sShaderLanguage == Cg) {
		#include "DepthTexture_Cg.h"

		// Return the requested source code
		switch (nSourceCodeType) {
			case FragmentShaderBody:
				return sSourceCode_Fragment;

			case FragmentShaderTemplate:
				return sSourceCode_Fragment_Template;
		}
	}

	// Error!
	return "";
}

void ShaderFunctionClipRayDepthTexture::SetProgram(Program &cProgram, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, SRPVolume &cSRPVolume)
{
	// Get used renderer instance
	Renderer &cRenderer = cProgram.GetRenderer();

	// Get simplified GPU program wrapper interface
	ProgramWrapper &cProgramWrapper = static_cast<ProgramWrapper&>(cProgram);

	{ // Set depth texture
		// Get the "PLCompositing::SRPBegin" instance
		PLCompositing::SRPBegin *pSRPBegin = static_cast<PLCompositing::SRPBegin*>(cSRPVolume.GetFirstInstanceOfSceneRendererPassClass("PLCompositing::SRPBegin"));
		if (pSRPBegin) {
			// Set depth texture
			const int nTextureUnit = cProgramWrapper.Set("DepthTexture_x_", reinterpret_cast<TextureBuffer*>(pSRPBegin->GetTextureBufferDepth()));
			if (nTextureUnit >= 0) {
				// Setup texture addressing by using clamp
				// -> Clamp: Last valid value is reused for out-of-bound access
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Clamp);
				cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Clamp);

				// No need to perform any texture filtering setup in here
				// -> Within the shader we're performing an unfiltered texture lookup in our sampler by using the texel fetch instruction
			}
		}
	}

	{ // Set clip space to object space matrix
		// Get object space to clip space matrix, and invert it
		Matrix4x4 mClipSpaceToObjectSpace = cVisNode.GetWorldViewProjectionMatrix();
		mClipSpaceToObjectSpace.Invert();

		// Set clip space to object space matrix
		cProgramWrapper.Set("ClipSpaceToObjectSpace_x_", mClipSpaceToObjectSpace);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer
