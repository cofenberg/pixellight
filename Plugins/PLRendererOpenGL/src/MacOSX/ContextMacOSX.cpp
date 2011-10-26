/*********************************************************\
 *  File: ContextMacOSX.h                                *
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
#include <OpenGL/OpenGL.h>
#include <PLCore/Log/Log.h>
#include <PLMath/Vector2i.h>
#include <PLRenderer/Renderer/Types.h>
#include "PLRendererOpenGL/MacOSX/ContextMacOSX.h"
#include <IOKit/graphics/IOGraphicsTypes.h>	// Include this after the rest, else we get OS definition issues, again


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Public methods                                        ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ContextMacOSX::ContextMacOSX(Renderer &cRenderer) :
	m_pRenderer(&cRenderer),
	m_pCGLContextObj(nullptr)
{
	CGLError nCGLError = kCGLNoError;

	// Search for a suitable pixel format
	CGLPixelFormatAttribute nCGLPixelFormatAttribute[] = {
		static_cast<CGLPixelFormatAttribute>(0)
	};
	GLint nNumOfVirtualScreens = 0;
	CGLPixelFormatObj pCGLPixelFormatObj = nullptr;
	nCGLError = CGLChoosePixelFormat(nCGLPixelFormatAttribute, &pCGLPixelFormatObj, &nNumOfVirtualScreens);
	if (nCGLError == kCGLNoError) {
		// Create the CGL context object
		nCGLError = CGLCreateContext(pCGLPixelFormatObj, nullptr, &m_pCGLContextObj);
		if (nCGLError == kCGLNoError) {
			// Make our CGL context object to the current one (don't use "MakeDummyCurrent()" in here, we want to see if it's working in general)
			nCGLError = CGLSetCurrentContext(m_pCGLContextObj);
			if (nCGLError != kCGLNoError)
				PL_LOG(Error, String("Failed to make the CGL context object to the current one (\"") + CGLErrorString(nCGLError) + "\")")
		} else {
			// Error!
			PL_LOG(Error, String("Failed to create the CGL context object (\"") + CGLErrorString(nCGLError) + "\")")
		}

		// Destroy the pixel format (meaning, release our reference)
		CGLDestroyPixelFormat(pCGLPixelFormatObj);
	} else {
		// Error!
		PL_LOG(Error, String("Failed to choose CGL pixel format (\"") + CGLErrorString(nCGLError) + "\")")
	}
}

/**
*  @brief
*    Destructor
*/
ContextMacOSX::~ContextMacOSX()
{
	// Is there a CGL context object?
	if (m_pCGLContextObj) {
		// Destroy the CGL context object (meaning, release our reference)
		const CGLError nCGLError = CGLDestroyContext(m_pCGLContextObj);
		if (nCGLError != kCGLNoError)
			PL_LOG(Error, String("Failed to destroy the CGL context object (\"") + CGLErrorString(nCGLError) + "\")")
	}
}


//[-------------------------------------------------------]
//[ Public virtual Context methods                        ]
//[-------------------------------------------------------]
bool ContextMacOSX::IsValid() const
{
	return (m_pCGLContextObj != nullptr);
}

void ContextMacOSX::MakeDummyCurrent() const
{
	// Make our CGL context object to the current one
	CGLSetCurrentContext(m_pCGLContextObj);
}

bool ContextMacOSX::QueryDisplayModes(Array<const PLRenderer::DisplayMode*> &lstDisplayModeList)
{
	// Clear old list of display modes
	for (uint32 i=0; i<lstDisplayModeList.GetNumOfElements(); i++)
		delete lstDisplayModeList[i];
	lstDisplayModeList.Clear();

	// Get list of display modes
	PL_LOG(Info, "Query available display modes")
	const CFArrayRef lstDisplayModes = CGDisplayCopyAllDisplayModes(kCGDirectMainDisplay, nullptr);
	for (CFIndex nMode=0; nMode<CFArrayGetCount(lstDisplayModes); nMode++) {
		// Get the current display mode
		const CGDisplayModeRef pCGDisplayMode = (CGDisplayModeRef)CFArrayGetValueAtIndex(lstDisplayModes, nMode);	// No C++ style cast because it's tricky in here
		const Vector2i vSize(CGDisplayModeGetWidth(pCGDisplayMode), CGDisplayModeGetHeight(pCGDisplayMode));		// Screen resolution
		const uint32   nColorBits = GetColorBitsFromDisplayMode(pCGDisplayMode);									// Number of bits for the color (for example 32)
		const uint32   nFrequency = static_cast<uint32>(CGDisplayModeGetRefreshRate(pCGDisplayMode));				// Refresh rate (for example 60)

		// First at all, we're only interested in some of the settings - as a result, we really should check if there's
		// already a display mode within our list with the interesting settings of the current found display mode
		bool bNewMode = true;
		for (uint32 i=0; i<lstDisplayModeList.GetNumOfElements(); i++) {
			const PLRenderer::DisplayMode *pDisplayMode = lstDisplayModeList[i];
			if (pDisplayMode->vSize == vSize && pDisplayMode->nColorBits == nColorBits && pDisplayMode->nFrequency == nFrequency) {
				// We already have such a display mode within our list!
				bNewMode = false;

				// Get us out of this loop right now!
				i = lstDisplayModeList.GetNumOfElements();
			}
		}
		if (bNewMode) {
			// Get required information
			PLRenderer::DisplayMode *pDisplayMode = new PLRenderer::DisplayMode;
			pDisplayMode->vSize		 = vSize;
			pDisplayMode->nColorBits = nColorBits;
			pDisplayMode->nFrequency = nFrequency;

			// Give out log message
			String sTemp;
			if (pDisplayMode->nFrequency) {
				sTemp = String::Format("Found: %dx%dx%d %d Hz", pDisplayMode->vSize.x, pDisplayMode->vSize.y,
																pDisplayMode->nColorBits, pDisplayMode->nFrequency);
			} else {
				sTemp = String::Format("Found: %dx%dx%d", pDisplayMode->vSize.x, pDisplayMode->vSize.y, pDisplayMode->nColorBits);
			}

			// Add found display mode to list
			PL_LOG(Info, sTemp)
			lstDisplayModeList.Add(pDisplayMode);
		}
	}

	// Was at least one display mode found?
	if (lstDisplayModeList.IsEmpty()) {
		PL_LOG(Error, "No available & supported display modes found!")

		// Error!
		return false;
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Private methods                                       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the number of color bits from a given display mode
*/
uint32 ContextMacOSX::GetColorBitsFromDisplayMode(CGDisplayModeRef pCGDisplayMode) const
{
	uint32 nColorBits = 0;
	const CFStringRef psString = CGDisplayModeCopyPixelEncoding(pCGDisplayMode);
	if (CFStringCompare(psString, CFSTR(IO8BitIndexedPixels), kCFCompareCaseInsensitive) == kCFCompareEqualTo)
		nColorBits = 8;
	else if (CFStringCompare(psString, CFSTR(IO16BitDirectPixels), kCFCompareCaseInsensitive) == kCFCompareEqualTo)
		nColorBits = 16;
	else if (CFStringCompare(psString, CFSTR(IO32BitDirectPixels), kCFCompareCaseInsensitive) == kCFCompareEqualTo)
		nColorBits = 32;
	return nColorBits;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
