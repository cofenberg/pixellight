/*********************************************************\
 *  File: ProgramUniformGLSL.h                           *
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


#ifndef __PLRENDEREROPENGLES_PROGRAMUNIFORMGLSL_H__
#define __PLRENDEREROPENGLES_PROGRAMUNIFORMGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/ProgramUniform.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL ES GLSL renderer program uniform
*/
class ProgramUniformGLSL : public PLRenderer::ProgramUniform {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ProgramGLSL;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    If this uniform is a texture, this method sets the OpenGL ES texture assigned to the uniform
		*
		*  @param[in] nOpenGLESTextureTarget
		*    OpenGL ES texture target
		*  @param[in] nOpenGLESTexture
		*    OpenGL ES texture to set
		*
		*  @return
		*    The texture unit assigned to this uniform (same as GetTextureUnit()), negative on error
		*/
		int Set(GLenum nOpenGLESTextureTarget, GLuint nOpenGLESTexture);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nOpenGLESProgram
		*    OpenGL ES program, must be valid!
		*  @param[in] nOpenGLESUniformLocation
		*    OpenGL ES uniform location, must be valid!
		*  @param[in] nTextureUnit
		*    Texture unit assigned to this uniform (for sampler uniforms), negative if not assigned to any texture unit
		*/
		ProgramUniformGLSL(GLuint nOpenGLESProgram, int nOpenGLESUniformLocation, int nTextureUnit);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramUniformGLSL();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		GLuint m_nOpenGLESProgram;			/**< OpenGL ES program, always valid! */
		int    m_nOpenGLESUniformLocation;	/**< OpenGL ES uniform location, always valid! */
		int    m_nTextureUnit;				/**< Texture unit assigned to this uniform (for sampler uniforms), negative if not assigned to any texture unit */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::ProgramUniform functions   ]
	//[-------------------------------------------------------]
	public:
		// 1 component
		virtual void Get(int &nX);
		virtual void Get(float &fX);
		virtual void Get(double &fX);
		virtual void Set(int nX);
		virtual void Set(float fX);
		virtual void Set(double fX);
		// 2 components
		virtual void Get(int &nX, int &nY);
		virtual void Get(float &fX, float &fY);
		virtual void Get(double &fX, double &fY);
		virtual void Get(PLMath::Vector2i &vVector);
		virtual void Get(PLMath::Vector2 &vVector);
		virtual void Get2(int *pnComponents);
		virtual void Get2(float *pfComponents);
		virtual void Get2(double *pfComponents);
		virtual void Set(int nX, int nY);
		virtual void Set(float fX, float fY);
		virtual void Set(double fX, double fY);
		virtual void Set(const PLMath::Vector2i &vVector);
		virtual void Set(const PLMath::Vector2 &vVector);
		virtual void Set2(const int *pnComponents);
		virtual void Set2(const float *pfComponents);
		virtual void Set2(const double *pfComponents);
		// 3 components
		virtual void Get(int &nX, int &nY, int &nZ);
		virtual void Get(float &fX, float &fY, float &fZ);
		virtual void Get(double &fX, double &fY, double &fZ);
		virtual void Get(PLMath::Vector3i &vVector);
		virtual void Get(PLMath::Vector3 &vVector);
		virtual void Get(PLGraphics::Color3 &cColor);	// Floating point
		virtual void Get3(int *pnComponents);
		virtual void Get3(float *pfComponents);
		virtual void Get3(double *pfComponents);
		virtual void Set(int nX, int nY, int nZ);
		virtual void Set(float fX, float fY, float fZ);
		virtual void Set(double fX, double fY, double fZ);
		virtual void Set(const PLMath::Vector3i &vVector);
		virtual void Set(const PLMath::Vector3 &vVector);
		virtual void Set(const PLGraphics::Color3 &cColor);
		virtual void Set3(const int *pnComponents);
		virtual void Set3(const float *pfComponents);
		virtual void Set3(const double *pfComponents);
		// 4 components
		virtual void Get(int &nX, int &nY, int &nZ, int &nW);
		virtual void Get(float &fX, float &fY, float &fZ, float &fW);
		virtual void Get(double &fX, double &fY, double &fZ, double &fW);
		virtual void Get(PLMath::Vector4 &vVector);
		virtual void Get(PLGraphics::Color4 &cColor);	// Floating point
		virtual void Get(PLMath::Quaternion &qQuaternion);
		virtual void Get4(int *pnComponents);
		virtual void Get4(float *pfComponents);
		virtual void Get4(double *pfComponents);
		virtual void Set(int nX, int nY, int nZ, int nW);
		virtual void Set(float fX, float fY, float fZ, float fW);
		virtual void Set(double fX, double fY, double fZ, double fW);
		virtual void Set(const PLMath::Vector4 &vVector);
		virtual void Set(const PLGraphics::Color4 &cColor);
		virtual void Set(const PLMath::Quaternion &qQuaternion);
		virtual void Set4(const int *pnComponents);
		virtual void Set4(const float *pfComponents);
		virtual void Set4(const double *pfComponents);
		// Matrix
		virtual void Get(PLMath::Matrix3x3 &mMatrix);
		virtual void Get(PLMath::Matrix4x4 &mMatrix);
		virtual void Set(const PLMath::Matrix3x3 &mMatrix, bool bTranspose = false);
		virtual void Set(const PLMath::Matrix4x4 &mMatrix, bool bTranspose = false);
		// Texture
		virtual int GetTextureUnit() const;
		virtual int Set(PLRenderer::TextureBuffer *pTextureBuffer);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES


#endif // __PLRENDEREROPENGLES_PROGRAMUNIFORMGLSL_H__
