/*********************************************************\
 *  File: ShaderLoaderCg.cpp                             *
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
#include <PLGeneral/File/File.h>
#include <PLGeneral/Log/Log.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Renderer/ShaderProgram.h"
#include "PLRenderer/Shader/ShaderManager.h"
#include "PLRenderer/Shader/ShaderLoaderCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(ShaderLoaderCg)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool ShaderLoaderCg::Load(Shader &cShader, File &cFile)
{
	static const String Vertex = "Vertex";
	static const String Main   = "main";
	return LoadParams(cShader, cFile, Vertex, "", "", Main);
}

bool ShaderLoaderCg::LoadParams(Shader &cShader, File &cFile, String sType, String sProfile, String sDefines, String sEntry)
{
	// Some static strings for better performance
	static const String Vertex   = "Vertex";
	static const String Fragment = "Fragment";

	// Get renderer
	Renderer &cRenderer = cShader.GetShaderManager().GetRendererContext().GetRenderer();

	// Is the profile available?
	if (cRenderer.IsShaderProgramProfileSupported(sProfile)) {
		// Load shader, we also take care of the terminating NULL (\0)
		uint32  nFileSize = cFile.GetSize();
		uint8  *pData     = NULL;
		bool    bBuffered = true;

		// Is the file already within the memory and is there a terminating NULL (\0)?
		if (cFile.IsMemoryBuffered() && cFile.GetMemoryBuffer()[nFileSize-1] == '\0') {
			// We can use directly the existing memory
			pData     = (uint8*)cFile.GetMemoryBuffer();
			bBuffered = false;
		} else {
			// We need to 'cache' the file within the memory
			pData = new uint8[nFileSize+1];
			cFile.Read(pData, nFileSize, 1);
			pData[nFileSize] = '\0';
		}

		// Log message
		PL_LOG(Debug, "Create shader: " + cFile.GetUrl().GetNativePath() + " (Profile: '" + sProfile + "', Defines: '" + sDefines + "', Entry: '" + sEntry + "')")

		// Create and load shader program
		ShaderProgram *pShaderProgram = NULL;
		if (sType == Fragment) { // Fragment shader program
			pShaderProgram = cRenderer.CreateFragmentShaderProgram(pData, sProfile, sDefines, sEntry);
		} else if (sType == Vertex) { // Vertex shader program
			pShaderProgram = cRenderer.CreateVertexShaderProgram(pData, sProfile, sDefines, sEntry);
		}

		// Cleanup data if required
		if (bBuffered)
			delete [] pData;

		// Any problems occurred?
		if (pShaderProgram) {
			// Assign the shader program to the shader
			cShader.SetShaderProgram(pShaderProgram);

			// Done
			return true;
		}
	}

	// Error!
	return false;
}

bool ShaderLoaderCg::Save(const Shader &cShader, File &cFile)
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
ShaderLoaderCg::ShaderLoaderCg() :
	MethodLoad(this),
	MethodLoadParams(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
ShaderLoaderCg::~ShaderLoaderCg()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
