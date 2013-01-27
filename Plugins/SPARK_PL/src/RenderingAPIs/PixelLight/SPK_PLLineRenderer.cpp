/*********************************************************\
 *  File: SPK_PLLineRenderer.cpp                         *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Math.h>	// On Mac OS X I'am getting the compiler error "error: ‘isfinite’ was not declared in this scope" when not including this header, first... I'am not sure what SPARK is changing in order to cause this error...
#include <PLCore/PLCore.h>
PL_WARNING_PUSH
PL_WARNING_DISABLE(4530) // "warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
	// [HACK] There are missing forward declarations within the SPARK headers...
	namespace SPK {
		class Group;
	}
	#include <Core/SPK_Group.h>
PL_WARNING_POP
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLBuffer.h"
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLLineRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Protected definitions                                 ]
//[-------------------------------------------------------]
const std::string SPK_PLLineRenderer::PLBufferName("SPK_PLLineRenderer_Buffer");


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor of SPK_PLLineRenderer
*/
SPK_PLLineRenderer::~SPK_PLLineRenderer()
{
}


//[-------------------------------------------------------]
//[ Public virtual SPK::BufferHandler functions           ]
//[-------------------------------------------------------]
void SPK_PLLineRenderer::createBuffers(const SPK::Group &group)
{
	// Create the SPK_PLBuffer instance
	m_pSPK_PLBuffer = static_cast<SPK_PLBuffer*>(group.createBuffer(PLBufferName, PLBufferCreator(GetPLRenderer(), 14, 0, SPK::TEXTURE_NONE), 0U, false));
}

void SPK_PLLineRenderer::destroyBuffers(const SPK::Group &group)
{
	group.destroyBuffer(PLBufferName);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor of SPK_PLLineRenderer
*/
SPK_PLLineRenderer::SPK_PLLineRenderer(PLRenderer::Renderer &cRenderer, float fLength, float fWidth) : SPK_PLRenderer(cRenderer), SPK::LineRendererInterface(fLength, fWidth),
	m_pSPK_PLBuffer(nullptr)
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL
