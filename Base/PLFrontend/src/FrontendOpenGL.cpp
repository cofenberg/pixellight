/*********************************************************\
 *  File: FrontendOpenGL.cpp                             *
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


// [TODO] Remove those libs if you don't use this frontend test
// opengl32.lib
// glu32.lib


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontend/FrontendOpenGL.h"
#include "PLFrontend/FrontendImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLFrontend {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FrontendOpenGL::FrontendOpenGL(FrontendImpl &cImpl) : Frontend(cImpl),
	m_hRC(nullptr),
	m_fAngle(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
FrontendOpenGL::~FrontendOpenGL()
{
}


//[-------------------------------------------------------]
//[ Private virtual FrontendImpl functions                ]
//[-------------------------------------------------------]
void FrontendOpenGL::OnInit()
{
	// Set up pixel format for OpenGL window
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// Size Of This Pixel Format Descriptor
		1,								// Version Number
		PFD_DRAW_TO_WINDOW |			// Format Must Support Window
		PFD_SUPPORT_OPENGL |			// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,				// Must Support Double Buffering
		PFD_TYPE_RGBA,					// Request An RGBA Format
		32,								// Select Our Color Depth
		0, 0, 0, 0, 0, 0,				// Color Bits Ignored
		0,								// No Alpha Buffer
		0,								// Shift Bit Ignored
		0,								// No Accumulation Buffer
		0, 0, 0, 0,						// Accumulation Bits Ignored
		16,								// 16Bit Z-Buffer (Depth Buffer)
		0,								// No Stencil Buffer
		0,								// No Auxiliary Buffer
		PFD_MAIN_PLANE,					// Main Drawing Layer
		0,								// Reserved
		0, 0, 0							// Layer Masks Ignored
	};

	// Get device context
	HDC hDC = (HDC)GetImpl()->GetDeviceContext();

	// Set pixel format
	int nPixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, nPixelFormat, &pfd);

	// Create rendering context
	m_hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, m_hRC);

	// Initialize OpenGL window
	ResizeGL();
	InitGL();
}

void FrontendOpenGL::OnDeInit()
{
}

void FrontendOpenGL::OnDraw()
{
	// Draw OpenGL scene
	DrawGL();

	// Swap buffers (double buffering)
	HDC hDC = (HDC)GetImpl()->GetDeviceContext();
	SwapBuffers(hDC);

	// Rotate our rectangle
	m_fAngle += 0.2f;
	if (m_fAngle >= 360.0f)
		m_fAngle -= 360.0f;

	// Issue a redraw request
	Redraw();
}

void FrontendOpenGL::OnSize()
{
	// Adjust size of scene
	ResizeGL();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialize OpenGL
*/
void FrontendOpenGL::InitGL()
{
	// Set up OpenGL rendering modes
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/**
*  @brief
*    Resize GL scene to fit the current window size
*/
void FrontendOpenGL::ResizeGL()
{
	// Get size
	uint32 nWidth  = GetWidth();
	uint32 nHeight = GetHeight();
	if (nWidth > 0 && nHeight > 0) {
		// Set viewport
		glViewport(0, 0, nWidth, nHeight);

		// Set projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)nWidth /(GLfloat)nHeight, 0.1f, 100.0f);

		// Switch back to model/view matrix
		glMatrixMode(GL_MODELVIEW);
	}
}

/**
*  @brief
*    Draw scene
*/
void FrontendOpenGL::DrawGL()
{
	// Set scale factor for our rectangle
	static float fScale = 0.6f;

	// Clear buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Rotate and scale view
	glLoadIdentity();
	glRotatef(m_fAngle, 0.0f, 0.0f, 1.0f);
	glScalef(fScale, fScale, 1.0f);

	// Draw a colored rectangle
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glEnd();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontend
