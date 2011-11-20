/*********************************************************\
 *  File: ProgramUniformGLSL.cpp                         *
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
#include <PLMath/Vector3i.h>
#include <PLMath/Matrix3x3.h>
#include <PLMath/Matrix4x4.h>
#include <PLMath/Quaternion.h>
#include <PLGraphics/Color/Color3.h>
#include <PLGraphics/Color/Color4.h>
#include "PLRendererOpenGLES2/Renderer.h"
#include "PLRendererOpenGLES2/TextureBuffer2D.h"
#include "PLRendererOpenGLES2/TextureBuffer3D.h"
#include "PLRendererOpenGLES2/TextureBufferCube.h"
#include "PLRendererOpenGLES2/ProgramUniformGLSL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLGraphics;
namespace PLRendererOpenGLES2 {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    If this uniform is a texture, this method sets the OpenGL ES texture assigned to the uniform
*/
int ProgramUniformGLSL::Set(GLenum nOpenGLESTextureTarget, GLuint nOpenGLESTexture)
{
	// Valid texture unit?
	if (m_nTextureUnit >= 0) {
		// Activate the texture unit the uniform is assigned to
		glActiveTexture(GL_TEXTURE0 + m_nTextureUnit);

		// Bind the OpenGL ES texture
		glBindTexture(nOpenGLESTextureTarget, nOpenGLESTexture);

		// Assign the current bound texture at the current activated texture unit to the uniform
		glUniform1i(m_nOpenGLESUniformLocation, m_nTextureUnit);
	}

	// Done, return the texture unit the uniform is assigned to
	return m_nTextureUnit;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
ProgramUniformGLSL::ProgramUniformGLSL(GLuint nOpenGLESProgram, int nOpenGLESUniformLocation, int nTextureUnit) :
	m_nOpenGLESProgram(nOpenGLESProgram),
	m_nOpenGLESUniformLocation(nOpenGLESUniformLocation),
	m_nTextureUnit(nTextureUnit)
{
}

/**
*  @brief
*    Destructor
*/
ProgramUniformGLSL::~ProgramUniformGLSL()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::ProgramUniform functions   ]
//[-------------------------------------------------------]
// 1 component
void ProgramUniformGLSL::Get(int &nX)
{
	glGetUniformiv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, &nX);
}

void ProgramUniformGLSL::Get(float &fX)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, &fX);
}

void ProgramUniformGLSL::Get(double &fX)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Set(int nX)
{
	glUniform1i(m_nOpenGLESUniformLocation, nX);
}

void ProgramUniformGLSL::Set(float fX)
{
	glUniform1f(m_nOpenGLESUniformLocation, fX);
}

void ProgramUniformGLSL::Set(double fX)
{
	// Not supported by OpenGL ES 2.0
}

// 2 components
void ProgramUniformGLSL::Get(int &nX, int &nY)
{
	int nElements[2];
	glGetUniformiv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, nElements);
	nX = nElements[0];
	nY = nElements[1];
}

void ProgramUniformGLSL::Get(float &fX, float &fY)
{
	float fElements[2];
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, fElements);
	fX = fElements[0];
	fY = fElements[1];
}

void ProgramUniformGLSL::Get(double &fX, double &fY)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Get(Vector2i &vVector)
{
	glGetUniformiv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, vVector.nV);
}

void ProgramUniformGLSL::Get(Vector2 &vVector)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, vVector.fV);
}

void ProgramUniformGLSL::Get2(int *pnComponents)
{
	glGetUniformiv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, pnComponents);
}

void ProgramUniformGLSL::Get2(float *pfComponents)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, pfComponents);
}

void ProgramUniformGLSL::Get2(double *pfComponents)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Set(int nX, int nY)
{
	glUniform2i(m_nOpenGLESUniformLocation, nX, nY);
}

void ProgramUniformGLSL::Set(float fX, float fY)
{
	glUniform2f(m_nOpenGLESUniformLocation, fX, fY);
}

void ProgramUniformGLSL::Set(double fX, double fY)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Set(const Vector2i &vVector)
{
	glUniform2iv(m_nOpenGLESUniformLocation, 1, vVector);
}

void ProgramUniformGLSL::Set(const Vector2 &vVector)
{
	glUniform2fv(m_nOpenGLESUniformLocation, 1, vVector);
}

void ProgramUniformGLSL::Set2(const int *pnComponents)
{
	glUniform2iv(m_nOpenGLESUniformLocation, 1, pnComponents);
}

void ProgramUniformGLSL::Set2(const float *pfComponents)
{
	glUniform2fv(m_nOpenGLESUniformLocation, 1, pfComponents);
}

void ProgramUniformGLSL::Set2(const double *pfComponents)
{
	// Not supported by OpenGL ES 2.0
}

// 3 components
void ProgramUniformGLSL::Get(int &nX, int &nY, int &nZ)
{
	int nElements[3];
	glGetUniformiv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, nElements);
	nX = nElements[0];
	nY = nElements[1];
	nZ = nElements[2];
}

void ProgramUniformGLSL::Get(float &fX, float &fY, float &fZ)
{
	float fElements[3];
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, fElements);
	fX = fElements[0];
	fY = fElements[1];
	fZ = fElements[2];
}

void ProgramUniformGLSL::Get(double &fX, double &fY, double &fZ)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Get(Vector3i &vVector)
{
	glGetUniformiv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, vVector.nV);
}

void ProgramUniformGLSL::Get(Vector3 &vVector)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, vVector.fV);
}

void ProgramUniformGLSL::Get(Color3 &cColor)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, cColor.fColor);
}

void ProgramUniformGLSL::Get3(int *pnComponents)
{
	glGetUniformiv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, pnComponents);
}

void ProgramUniformGLSL::Get3(float *pfComponents)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, pfComponents);
}

void ProgramUniformGLSL::Get3(double *pfComponents)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Set(int nX, int nY, int nZ)
{
	glUniform3i(m_nOpenGLESUniformLocation, nX, nY, nZ);
}

void ProgramUniformGLSL::Set(float fX, float fY, float fZ)
{
	glUniform3f(m_nOpenGLESUniformLocation, fX, fY, fZ);
}

void ProgramUniformGLSL::Set(double fX, double fY, double fZ)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Set(const Vector3i &vVector)
{
	glUniform3iv(m_nOpenGLESUniformLocation, 1, vVector);
}

void ProgramUniformGLSL::Set(const Vector3 &vVector)
{
	glUniform3fv(m_nOpenGLESUniformLocation, 1, vVector);
}

void ProgramUniformGLSL::Set(const Color3 &cColor)
{
	glUniform3fv(m_nOpenGLESUniformLocation, 1, cColor);
}

void ProgramUniformGLSL::Set3(const int *pnComponents)
{
	glUniform3iv(m_nOpenGLESUniformLocation, 1, pnComponents);
}

void ProgramUniformGLSL::Set3(const float *pfComponents)
{
	glUniform3fv(m_nOpenGLESUniformLocation, 1, pfComponents);
}

void ProgramUniformGLSL::Set3(const double *pfComponents)
{
	// Not supported by OpenGL ES 2.0
}

// 4 components
void ProgramUniformGLSL::Get(int &nX, int &nY, int &nZ, int &nW)
{
	int nElements[4];
	glGetUniformiv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, nElements);
	nX = nElements[0];
	nY = nElements[1];
	nZ = nElements[2];
	nW = nElements[3];
}

void ProgramUniformGLSL::Get(float &fX, float &fY, float &fZ, float &fW)
{
	float fElements[4];
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, fElements);
	fX = fElements[0];
	fY = fElements[1];
	fZ = fElements[2];
	fW = fElements[3];
}

void ProgramUniformGLSL::Get(double &fX, double &fY, double &fZ, double &fW)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Get(Vector4 &vVector)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, vVector.fV);
}

void ProgramUniformGLSL::Get(Color4 &cColor)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, cColor.fColor);
}

void ProgramUniformGLSL::Get(Quaternion &qQuaternion)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, qQuaternion.fQ);
}

void ProgramUniformGLSL::Get4(int *pnComponents)
{
	glGetUniformiv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, pnComponents);
}

void ProgramUniformGLSL::Get4(float *pfComponents)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, pfComponents);
}

void ProgramUniformGLSL::Get4(double *pfComponents)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Set(int nX, int nY, int nZ, int nW)
{
	glUniform4i(m_nOpenGLESUniformLocation, nX, nY, nZ, nW);
}

void ProgramUniformGLSL::Set(float fX, float fY, float fZ, float fW)
{
	glUniform4f(m_nOpenGLESUniformLocation, fX, fY, fZ, fW);
}

void ProgramUniformGLSL::Set(double fX, double fY, double fZ, double fW)
{
	// Not supported by OpenGL ES 2.0
}

void ProgramUniformGLSL::Set(const Vector4 &vVector)
{
	glUniform4fv(m_nOpenGLESUniformLocation, 1, vVector);
}

void ProgramUniformGLSL::Set(const Color4 &cColor)
{
	glUniform4fv(m_nOpenGLESUniformLocation, 1, cColor);
}

void ProgramUniformGLSL::Set(const Quaternion &qQuaternion)
{
	glUniform4fv(m_nOpenGLESUniformLocation, 1, qQuaternion);
}

void ProgramUniformGLSL::Set4(const int *pnComponents)
{
	glUniform4iv(m_nOpenGLESUniformLocation, 1, pnComponents);
}

void ProgramUniformGLSL::Set4(const float *pfComponents)
{
	glUniform4fv(m_nOpenGLESUniformLocation, 1, pfComponents);
}

void ProgramUniformGLSL::Set4(const double *pfComponents)
{
	// Not supported by OpenGL ES 2.0
}

// Matrix
void ProgramUniformGLSL::Get(Matrix3x3 &mMatrix)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, mMatrix.fM);
}

void ProgramUniformGLSL::Get(Matrix4x4 &mMatrix)
{
	glGetUniformfv(m_nOpenGLESProgram, m_nOpenGLESUniformLocation, mMatrix.fM);
}

void ProgramUniformGLSL::Set(const Matrix3x3 &mMatrix, bool bTranspose)
{
	glUniformMatrix3fv(m_nOpenGLESUniformLocation, 1, bTranspose, mMatrix);
}

void ProgramUniformGLSL::Set(const Matrix4x4 &mMatrix, bool bTranspose)
{
	glUniformMatrix4fv(m_nOpenGLESUniformLocation, 1, bTranspose, mMatrix);
}

// Texture
int ProgramUniformGLSL::GetTextureUnit() const
{
	return m_nTextureUnit;
}

int ProgramUniformGLSL::Set(PLRenderer::TextureBuffer *pTextureBuffer)
{
	// Valid texture unit?
	if (m_nTextureUnit >= 0) {
		// Get the OpenGL ES texture
		GLuint nOpenGLESTexture       = 0;
		GLenum nOpenGLESTextureTarget = GL_TEXTURE_2D;
		if (pTextureBuffer) {
			// Check resource type
			switch (pTextureBuffer->GetType()) {
				case PLRenderer::Resource::TypeTextureBuffer1D:
					// OpenGL ES 2.0 doesn't support 1D textures - set no texture
					break;

				case PLRenderer::Resource::TypeTextureBuffer2D:
					nOpenGLESTexture = static_cast<TextureBuffer2D*>(pTextureBuffer)->GetOpenGLESTexture();
					nOpenGLESTextureTarget = GL_TEXTURE_2D;
					break;

				case PLRenderer::Resource::TypeTextureBuffer3D:
					nOpenGLESTexture =  static_cast<TextureBuffer3D*>(pTextureBuffer)->GetOpenGLESTexture();
					nOpenGLESTextureTarget = GL_TEXTURE_3D_OES;
					break;

				case PLRenderer::Resource::TypeTextureBufferCube:
					nOpenGLESTexture = static_cast<TextureBufferCube*>(pTextureBuffer)->GetOpenGLESTexture();
					nOpenGLESTextureTarget = GL_TEXTURE_CUBE_MAP;
					break;
			}
		}

		// Activate the texture unit the uniform is assigned to
		glActiveTexture(GL_TEXTURE0 + m_nTextureUnit);

		// Bind the OpenGL ES texture
		glBindTexture(nOpenGLESTextureTarget, nOpenGLESTexture);

		// Assign the current bound texture at the current activated texture unit to the uniform
		glUniform1i(m_nOpenGLESUniformLocation, m_nTextureUnit);

		// Inform the renderer
		if (pTextureBuffer)
			static_cast<Renderer&>(pTextureBuffer->GetRenderer()).SetShaderProgramTextureBuffer(m_nTextureUnit, pTextureBuffer);

		// Done, return the texture unit the uniform is assigned to
		return m_nTextureUnit;
	}

	// Error!
	return -1;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2
