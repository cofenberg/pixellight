/*********************************************************\
 *  File: ShaderFunctionJitterPositionStochastic.cpp     *
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
#include <PLMath/Math.h>
#include <PLMath/Vector3i.h>
#include <PLGraphics/Image/Image.h>
#include <PLGraphics/Image/ImageBuffer.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/ProgramWrapper.h>
#include "PLVolumeRenderer/SRPVolume.h"
#include "PLVolumeRenderer/JitterPosition/ShaderFunctionJitterPositionStochastic.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
namespace PLVolumeRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShaderFunctionJitterPositionStochastic)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
ShaderFunctionJitterPositionStochastic::ShaderFunctionJitterPositionStochastic() :
	m_pRandomTextureBuffer(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
ShaderFunctionJitterPositionStochastic::~ShaderFunctionJitterPositionStochastic()
{
	// Destroy our renderer texture buffer holding the random 2D texel data
	if (m_pRandomTextureBuffer)
		delete m_pRandomTextureBuffer;
}


//[-------------------------------------------------------]
//[ Public virtual ShaderFunction functions               ]
//[-------------------------------------------------------]
String ShaderFunctionJitterPositionStochastic::GetSourceCode(const String &sShaderLanguage, ESourceCodeType nSourceCodeType)
{
	// Check requested shader language
	if (sShaderLanguage == GLSL) {
		#include "Stochastic_GLSL.h"

		// Return the requested source code
		if (nSourceCodeType == FragmentShaderBody)
			return sSourceCode_Fragment;
	} else if (sShaderLanguage == Cg) {
		#include "Stochastic_Cg.h"

		// Return the requested source code
		if (nSourceCodeType == FragmentShaderBody)
			return sSourceCode_Fragment;
	}

	// Error!
	return "";
}

void ShaderFunctionJitterPositionStochastic::SetProgram(Program &cProgram, const PLScene::SQCull &cCullQuery, const PLScene::VisNode &cVisNode, SRPVolume &cSRPVolume)
{
	// Get used renderer instance
	Renderer &cRenderer = cProgram.GetRenderer();

	// Get simplified GPU program wrapper interface
	ProgramWrapper &cProgramWrapper = static_cast<ProgramWrapper&>(cProgram);

	// Set dither ray
	cProgramWrapper.Set("DitherRay", cSRPVolume.DitherRay.Get());

	// Create our renderer texture buffer holding the random 2D texel data right now?
	static const uint32 RandomTextureSize = 32;
	if (!m_pRandomTextureBuffer) {
		// Create the image we want to use as texture
		Image cImage = Image::CreateImage(DataByte, ColorGrayscale, Vector3i(RandomTextureSize, RandomTextureSize, 1));

		// Fill the image
		ImageBuffer *pImageBuffer = cImage.GetBuffer();
		if (pImageBuffer) {
			// Get a pointer to the raw data of the image
			uint8 *pData = pImageBuffer->GetData();
			const uint8 *pDataEnd = pData + pImageBuffer->GetDataSize();

			// Set all pixels
			for (; pData<pDataEnd; pData++)
				*pData = static_cast<uint8>(Math::GetRandFloat()*255);
		}

		// Create the texture buffer instance by using our image data
		m_pRandomTextureBuffer = reinterpret_cast<TextureBuffer*>(cRenderer.CreateTextureBuffer2D(cImage));
	}

	{ // Random texture
		const int nTextureUnit = cProgramWrapper.Set("RandomTexture", m_pRandomTextureBuffer);
		if (nTextureUnit >= 0) {
			// Setup texture filtering by using wrapping
			cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressU, TextureAddressing::Wrap);
			cRenderer.SetSamplerState(nTextureUnit, Sampler::AddressV, TextureAddressing::Wrap);

			// Setup nearest texture filtering without mipmapping
			cRenderer.SetSamplerState(nTextureUnit, Sampler::MagFilter, TextureFiltering::Point);
			cRenderer.SetSamplerState(nTextureUnit, Sampler::MinFilter, TextureFiltering::Point);
			cRenderer.SetSamplerState(nTextureUnit, Sampler::MipFilter, TextureFiltering::None);
		}
	}

	// Set 1/<tile size> (avoid expensive division within the fragment shader)
	cProgramWrapper.Set("InvTileSize", 1.0f/RandomTextureSize, 1.0f/RandomTextureSize);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolumeRenderer
