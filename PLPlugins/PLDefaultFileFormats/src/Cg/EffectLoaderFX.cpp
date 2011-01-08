/*********************************************************\
 *  File: EffectLoaderFX.cpp                             *
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


// [TODO] Under construction


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/File/File.h>
#include <PLGeneral/String/Tokenizer.h>
#include <PLGeneral/Container/HashMap.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Material/Parameter.h>
#include <PLRenderer/Material/ParameterManager.h>
#include <PLRenderer/Effect/EffectPass.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Effect/EffectTechnique.h>
#include "PLDefaultFileFormats/Cg/EffectLoaderFX.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLRenderer;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(EffectLoaderFX)


//[-------------------------------------------------------]
//[ Global callback functions                             ]
//[-------------------------------------------------------]
typedef void (*FXStringCallback)(EffectLoaderFX::SInstance &sInstance, Tokenizer &cTokenizer);
HashMap<String, FXStringCallback> g_mapFXMisc;				/**< ONLY used within Load() */
HashMap<String, FXStringCallback> g_mapFXStateAssignment;	/**< ONLY used within Technique_Callback() */

// Misc
void Parameter_Callback(EffectLoaderFX::SInstance &sInstance, Tokenizer &cTokenizer)
{
	// Get parameter type - first character of type MUST be uppercase!
	String sTypeT = cTokenizer.GetToken();
	String sType  = sTypeT.GetSubstring(0, 1).ToUpper() + sTypeT.GetSubstring(1, 0);

	// Get parameter name
	String sName = cTokenizer.GetNextToken();

	// Create the parameter
	Parameter *pParamter = sInstance.pFX->GetParameterManager().CreateParameter(PLRenderer::Parameters::DataTypeFromString(sType), sName);
	if (pParamter) {
		String sToken = cTokenizer.GetNextToken();

		/* [TODO] No longer supported
		// Known semantic?
		if (sToken == ':') {
			// Get semantic (note: SemanticFromString IS case sensitive!)
			String sSemantic = cTokenizer.GetNextToken();
			PLRenderer::Parameters::ESemantic nSemantic = PLRenderer::Parameters::SemanticFromString(sSemantic);

			// Hm, check some other semantic names (no case sensitivity for sure)
			if (nSemantic == PLRenderer::Parameters::Unknown) {
				// World
				if (sSemantic.CompareNoCase("World"))
					nSemantic = PLRenderer::Parameters::World;

				// View
				else if (sSemantic.CompareNoCase("View"))
					nSemantic = PLRenderer::Parameters::View;

				// ViewI
				else if (sSemantic.CompareNoCase("ViewInverse"))
					nSemantic = PLRenderer::Parameters::ViewI;

				// ViewIT
				else if (sSemantic.CompareNoCase("ViewIT"))
					nSemantic = PLRenderer::Parameters::ViewIT;

				// Projection
				else if (sSemantic.CompareNoCase("Projection"))
					nSemantic = PLRenderer::Parameters::Projection;

				// WorldView
				else if (sSemantic.CompareNoCase("WorldView"))
					nSemantic = PLRenderer::Parameters::WorldView;

				// WorldViewProjection
				else if (sSemantic.CompareNoCase("WorldViewProj") || sSemantic.CompareNoCase("ModelViewProjection"))
					nSemantic = PLRenderer::Parameters::WorldViewProjection;

				// WorldIT
				else if (sSemantic.CompareNoCase("WorldInverseTranspose"))
					nSemantic = PLRenderer::Parameters::WorldIT;
			}

			// Set known semantic
			if (nSemantic != PLRenderer::Parameters::Unknown)
				sInstance.pFX->GetParameterManager().SetParameterSemantic(sName, nSemantic);
		}
*/
		// Annotation?
		if (sToken == '<') {
			// Skip the annotation
			while (cTokenizer.GetNextToken().GetLength() &&	cTokenizer.GetToken() != '>');
			sToken = cTokenizer.GetNextToken(); // Skip '>'
		}

		// Value?
		if (sToken == '=') {
			String sValue = cTokenizer.GetNextToken();
			if (sValue == '{') {
				// We do NOT allow ',' within parameter values!
				sValue = "";
				while (cTokenizer.GetNextToken().GetLength()) {
					sToken = cTokenizer.GetToken();
					if (sToken == '}') break;
					if (sToken != ',')
						sValue += sToken + " ";
				}
			}
			pParamter->SetParameterString(sValue);
		}

		// Eat the ';' at the end
		cTokenizer.GetNextToken();
	} else {
		// Skip the rest
		while (cTokenizer.GetNextToken().GetLength() && cTokenizer.GetToken() != ';');
	}

}
void Technique_Callback(EffectLoaderFX::SInstance &sInstance, Tokenizer &cTokenizer)
{
	// Is someone fooling us?
	if (sInstance.nTechnique == -1) {
		// Add the techique to the effect
		Effect *pFX = sInstance.pFX;
		EffectTechnique *pTechnique = pFX->AddTechnique();
		sInstance.nTechnique = pFX->GetNumOfTechniques()-1;

		// Get the name of the technique
		String sToken = cTokenizer.GetNextToken();
		if (sToken != '{') {
			pTechnique->SetName(cTokenizer.GetToken());
			cTokenizer.GetNextToken();
		}

		// Read 'technique'
		while (cTokenizer.GetNextToken().GetLength()) {
			// Check for '}'
			sToken = cTokenizer.GetToken();
			if (sToken == '}') break;

			// ONLY 'pass' allowed within a technique!
			if (sToken == "pass") {
				// Add the pass to the techique
				EffectPass *pFXPass = sInstance.pFXPass = pTechnique->AddPass();
				if (pFXPass) {
					// Get the name of the pass
					sToken = cTokenizer.GetNextToken();
					if (sToken != '{') {
						pFXPass->SetName(sToken);
						cTokenizer.GetNextToken();
					}

					// Read 'pass'
					while (cTokenizer.GetNextToken().GetLength()) {
						// Check for '}'
						sToken = cTokenizer.GetToken();
						if (sToken == '}') break;

						// Get string callback function
						const FXStringCallback &cCallback = g_mapFXStateAssignment.Get(sToken);
						if (&cCallback != &HashMap<String, FXStringCallback>::Null) {
							// Call the callback function
							cCallback(sInstance, cTokenizer);
						} else {
							// Check for '(' and '{'
							sToken = cTokenizer.GetToken();
							if (sToken == '{' || sToken == '(') {
								// Ignore the stuff within it!
								uint32 nDepth = 1;
								while (cTokenizer.GetNextToken().GetLength()) {
									// Check for '(', ')', '{', and '}'
									sToken = cTokenizer.GetToken();
									if (sToken == '{' || sToken == '(') {
										nDepth++;
									} else {
										if (sToken == '}' || sToken == ')') {
											nDepth--;
											if (!nDepth) break;
										}
									}
								}
							}
						}
					}
				}
			}
			sInstance.pFXPass = nullptr;
		}
		sInstance.nTechnique = -1;

		// Select default effect technique
		pFX->SelectTechnique(0);
	}
}
// State assignments
	// Render states
void AlphaFunc_Callback(EffectLoaderFX::SInstance &sInstance, Tokenizer &cTokenizer)
{
	// [TODO]
//			sInstance.pFXPass->GetRenderStates().Set(RenderState::AlphaFunc, cTokenizer.GetNextToken().GetBool());
}
void BlendFunc_Callback(EffectLoaderFX::SInstance &sInstance, Tokenizer &cTokenizer)
{
	// [TODO]
//			sInstance.pFXPass->GetRenderStates().Set(RenderState::BlendFunc, cTokenizer.GetNextToken().GetBool());
}
	// Misc
void Program_Callback(EffectLoaderFX::SInstance &sInstance, Tokenizer &cTokenizer)
{
	String sProgramType = cTokenizer.GetToken();
	cTokenizer.GetNextToken(); // There MUST follow a '='
	if (cTokenizer.GetToken() == '=') {
		String sToken = cTokenizer.GetNextToken();

		// compile
		if (sToken == "compile") {
			// Get the target profile
			String sProfile = cTokenizer.GetNextToken();

			// Get the entry point to the program
			String sEntry = cTokenizer.GetNextToken();

			// [TODO] Support function parameters
			// Check for '('
			sToken = cTokenizer.GetNextToken();
			if (sToken == '(') {
				// Ignore the stuff within it!
				uint32 nDepth = 1;
				while (cTokenizer.GetNextToken().GetLength()) {
					// Check for '(' and ')'
					sToken = cTokenizer.GetToken();
					if (sToken == '(') {
						nDepth++;
					} else {
						if (sToken == ')') {
							nDepth--;
							if (!nDepth) break;
						}
					}
				}
			}

			// Get the renderer context and renderer
			/* [TODO] New shader interface
			RendererContext &cRendererContext = sInstance.pFX->GetEffectManager().GetRendererContext();
			Renderer        &cRenderer        = cRendererContext.GetRenderer();

			// Create the program if the profile is supported
			if (!cRenderer.IsShaderProgramProfileSupported(sProfile))
				sProfile = "";
			String sShaderName = sEntry + "_" + sProfile + "_" + sInstance.pFX->GetName();
			Shader *pShader = cRendererContext.GetShaderManager().Get(sShaderName);
			if (!pShader) {
				pShader = cRendererContext.GetShaderManager().Create(sShaderName);
				if (pShader) {
					ShaderProgram *pShaderProgram = nullptr;
					if (sProgramType == "VertexProgram" || sProgramType == "VertexShader") {
						pShaderProgram = cRenderer.CreateVertexShaderProgram(sInstance.pFileData, sProfile, "", sEntry);
						sInstance.pFXPass->SetVertexShader(pShader);
					} else {
						pShaderProgram = cRenderer.CreateFragmentShaderProgram(sInstance.pFileData, sProfile, "", sEntry);
						sInstance.pFXPass->SetFragmentShader(pShader);
					}
					pShader->SetShaderProgram(pShaderProgram);
				}
			}*/

		// asm
		} else if (sToken == "asm") {
			// [TODO]
		}
		
	/*
			  compile fp40 C8E4f_specSurf(Ambient,
									  float4(DiffuseMaterial  * LightColor, 1),
									  float4(SpecularMaterial * LightColor, 1),
									  normalMap,
									  normalizeCube,
									  normalizeCube);
	*/
	}
}
void FragmentProgram_Callback(EffectLoaderFX::SInstance &sInstance, Tokenizer &cTokenizer)
{
}


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool EffectLoaderFX::Load(Effect &cEffect, File &cFile)
{
	// Already initialized?
	if (!g_mapFXMisc.GetNumOfElements()) {
		// Data types
		g_mapFXMisc.Add("float",     &Parameter_Callback);
		g_mapFXMisc.Add("float2",    &Parameter_Callback);
		g_mapFXMisc.Add("float3",    &Parameter_Callback);
		g_mapFXMisc.Add("float4",    &Parameter_Callback);
		g_mapFXMisc.Add("double",    &Parameter_Callback);
		g_mapFXMisc.Add("double2",   &Parameter_Callback);
		g_mapFXMisc.Add("double3",   &Parameter_Callback);
		g_mapFXMisc.Add("double4",   &Parameter_Callback);
		g_mapFXMisc.Add("float3x4",  &Parameter_Callback);
		g_mapFXMisc.Add("float4x4",  &Parameter_Callback);
		g_mapFXMisc.Add("double4x4", &Parameter_Callback);
		g_mapFXMisc.Add("texture",   &Parameter_Callback);

		// Misc
		g_mapFXMisc.Add("technique", &Technique_Callback);
	}

	// Already initialized?
	if (!g_mapFXStateAssignment.GetNumOfElements()) {
		// Render states
		g_mapFXStateAssignment.Add("AlphaFunc", &AlphaFunc_Callback);
		g_mapFXStateAssignment.Add("BlendFunc", &BlendFunc_Callback);
		// Misc
		g_mapFXStateAssignment.Add("VertexProgram",   &Program_Callback);
		g_mapFXStateAssignment.Add("VertexShader",    &Program_Callback);
		g_mapFXStateAssignment.Add("FragmentProgram", &Program_Callback);
		g_mapFXStateAssignment.Add("PixelShader",     &Program_Callback);
	}

	// Setup per instance data
	SInstance sInstance;
	sInstance.pFX        = &cEffect;
	sInstance.nTechnique = -1;
	sInstance.pFXPass    = nullptr;
	sInstance.pFileData  = nullptr;

	// Load the file into memory because we need to give this data also to the
	// shader compiler...
	uint32 nFileSize = cFile.GetSize();
	sInstance.pFileData = new char[nFileSize+1];
	cFile.Read(sInstance.pFileData, 1, nFileSize);
	sInstance.pFileData[nFileSize] = '\0';

	// Create the tokenizer
	Tokenizer cTokenizer;

	// Do not copy the string, please. The string class takes over the control of the buffer.
	cTokenizer.Start(String(sInstance.pFileData, false, nFileSize));

	// Read
	String sToken;
	while (cTokenizer.GetNextToken().GetLength()) {
		// Check for '(' and '{'
		sToken = cTokenizer.GetToken();
		if (sToken == '{' || sToken == '(') {
			// Ignore the stuff within it!
			uint32 nDepth = 1;
			while (cTokenizer.GetNextToken().GetLength()) {
				// Check for '(', ')', '{', and '}'
				sToken = cTokenizer.GetToken();
				if (sToken == '{' || sToken == '(') {
					nDepth++;
				} else {
					if (sToken == '}' || sToken == ')') {
						nDepth--;
						if (!nDepth) break;
					}
				}
			}

		// The interesting stuff :)
		} else {
			// Get string callback function
			const FXStringCallback &cCallback = g_mapFXMisc.Get(sToken);
			if (&cCallback != &HashMap<String, FXStringCallback>::Null)
				cCallback(sInstance, cTokenizer);
		}
	}

	// Stop the tokenizer
	cTokenizer.Stop();

	// Done
	return true;
}

bool EffectLoaderFX::Save(Effect &cEffect, File &cFile)
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
EffectLoaderFX::EffectLoaderFX() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
EffectLoaderFX::~EffectLoaderFX()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
