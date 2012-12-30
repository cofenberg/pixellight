/*********************************************************\
 *  File: ProgramUniformGLSL.h                           *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLRENDEREROPENGLES2_PROGRAMUNIFORMGLSL_H__
#define __PLRENDEREROPENGLES2_PROGRAMUNIFORMGLSL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/ProgramUniform.h>
#include "PLRendererOpenGLES2/Context.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLES2 {


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
		virtual void Get(int &nX) override;
		virtual void Get(float &fX) override;
		virtual void Get(double &fX) override;
		virtual void Set(int nX) override;
		virtual void Set(float fX) override;
		virtual void Set(double fX) override;
		// 2 components
		virtual void Get(int &nX, int &nY) override;
		virtual void Get(float &fX, float &fY) override;
		virtual void Get(double &fX, double &fY) override;
		virtual void Get(PLMath::Vector2i &vVector) override;
		virtual void Get(PLMath::Vector2 &vVector) override;
		virtual void Get2(int *pnComponents) override;
		virtual void Get2(float *pfComponents) override;
		virtual void Get2(double *pfComponents) override;
		virtual void Set(int nX, int nY) override;
		virtual void Set(float fX, float fY) override;
		virtual void Set(double fX, double fY) override;
		virtual void Set(const PLMath::Vector2i &vVector) override;
		virtual void Set(const PLMath::Vector2 &vVector) override;
		virtual void Set2(const int *pnComponents) override;
		virtual void Set2(const float *pfComponents) override;
		virtual void Set2(const double *pfComponents) override;
		// 3 components
		virtual void Get(int &nX, int &nY, int &nZ) override;
		virtual void Get(float &fX, float &fY, float &fZ) override;
		virtual void Get(double &fX, double &fY, double &fZ) override;
		virtual void Get(PLMath::Vector3i &vVector) override;
		virtual void Get(PLMath::Vector3 &vVector) override;
		virtual void Get(PLGraphics::Color3 &cColor) override;	// Floating point
		virtual void Get3(int *pnComponents) override;
		virtual void Get3(float *pfComponents) override;
		virtual void Get3(double *pfComponents) override;
		virtual void Set(int nX, int nY, int nZ) override;
		virtual void Set(float fX, float fY, float fZ) override;
		virtual void Set(double fX, double fY, double fZ) override;
		virtual void Set(const PLMath::Vector3i &vVector) override;
		virtual void Set(const PLMath::Vector3 &vVector) override;
		virtual void Set(const PLGraphics::Color3 &cColor) override;
		virtual void Set3(const int *pnComponents) override;
		virtual void Set3(const float *pfComponents) override;
		virtual void Set3(const double *pfComponents) override;
		// 4 components
		virtual void Get(int &nX, int &nY, int &nZ, int &nW) override;
		virtual void Get(float &fX, float &fY, float &fZ, float &fW) override;
		virtual void Get(double &fX, double &fY, double &fZ, double &fW) override;
		virtual void Get(PLMath::Vector4 &vVector) override;
		virtual void Get(PLGraphics::Color4 &cColor) override;	// Floating point
		virtual void Get(PLMath::Quaternion &qQuaternion) override;
		virtual void Get4(int *pnComponents) override;
		virtual void Get4(float *pfComponents) override;
		virtual void Get4(double *pfComponents) override;
		virtual void Set(int nX, int nY, int nZ, int nW) override;
		virtual void Set(float fX, float fY, float fZ, float fW) override;
		virtual void Set(double fX, double fY, double fZ, double fW) override;
		virtual void Set(const PLMath::Vector4 &vVector) override;
		virtual void Set(const PLGraphics::Color4 &cColor) override;
		virtual void Set(const PLMath::Quaternion &qQuaternion) override;
		virtual void Set4(const int *pnComponents) override;
		virtual void Set4(const float *pfComponents) override;
		virtual void Set4(const double *pfComponents) override;
		// Matrix
		virtual void Get(PLMath::Matrix3x3 &mMatrix) override;
		virtual void Get(PLMath::Matrix4x4 &mMatrix) override;
		virtual void Set(const PLMath::Matrix3x3 &mMatrix, bool bTranspose = false) override;
		virtual void Set(const PLMath::Matrix4x4 &mMatrix, bool bTranspose = false) override;
		// Texture
		virtual int GetTextureUnit() const override;
		virtual int Set(PLRenderer::TextureBuffer *pTextureBuffer) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLES2


#endif // __PLRENDEREROPENGLES2_PROGRAMUNIFORMGLSL_H__
