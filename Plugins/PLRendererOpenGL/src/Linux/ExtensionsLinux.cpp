/*********************************************************\
 *  File: ExtensionsLinux.cpp                            *
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
#include <PLCore/Log/Log.h>
#include "PLRendererOpenGL/Linux/ContextLinux.h"
#include "PLRendererOpenGL/Extensions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialize the supported extensions
*/
bool Extensions::Init(bool bUseExtensions)
{
	// Should the extensions be used?
	if (bUseExtensions) {
		m_bInitialized = true;
	} else {
		ResetExtensions();
		m_bInitialized = true;
		PL_LOG(Info, "Use no hardware supported extensions")

		// Done
		return true;
	}

	{ // Print a list of all available extensions into the log
		PL_LOG(Info, "Extensions info:")
		PL_LOG(Info, reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)))

		WriteExtensionStringIntoLog(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)));

		// Get the X server display connection
		Display *pDisplay = static_cast<ContextLinux&>(*m_pContext).GetDisplay();
		if (pDisplay) {
			// glXQueryExtensionsString
			PL_LOG(Info, "glx Extensions info:")
			WriteExtensionStringIntoLog(static_cast<const char*>(glXQueryExtensionsString(pDisplay, XDefaultScreen(pDisplay))));

			// glXGetClientString
			PL_LOG(Info, "glx client extensions info:")
			WriteExtensionStringIntoLog(static_cast<const char*>(glXGetClientString(pDisplay, GLX_EXTENSIONS)));
		}
	}


	//[-------------------------------------------------------]
	//[ WGL & ATI & NV                                        ]
	//[-------------------------------------------------------]
	// WGL_ARB_multisample
	m_bWGL_ARB_multisample = IsSupported("GLX_ARB_multisample");

	// WGL_ATI_pixel_format_float
	m_bWGL_ATI_pixel_format_float = IsSupported("GLX_ATI_pixel_format_float");

	// WGL_NV_float_buffer
	m_bWGL_NV_float_buffer = IsSupported("GLX_NV_float_buffer");


	//[-------------------------------------------------------]
	//[ GLX (Linux only)                                      ]
	//[-------------------------------------------------------]
	// GLX_SGI_swap_control
	if (IsSupported("GLX_SGI_swap_control")) {
		glXSwapIntervalSGI = reinterpret_cast<PFNGLXSWAPINTERVALSGIPROC>(glXGetProcAddressARB(reinterpret_cast<const GLubyte*>("glXSwapIntervalSGI")));
		if (!glXSwapIntervalSGI) {
			PL_LOG(Info, "Couldn't use extension 'GLX_SGI_swap_control'!")
			m_bGLX_SGI_swap_control = false;
		} else {
			m_bGLX_SGI_swap_control = true;
		}
	} else {
		m_bGLX_SGI_swap_control = false;
	}


	// Initialize the supported universal extensions
	return InitUniversal();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL
