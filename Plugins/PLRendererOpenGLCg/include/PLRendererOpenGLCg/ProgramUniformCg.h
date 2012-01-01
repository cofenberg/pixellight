/*********************************************************\
 *  File: ProgramUniformCg.h                             *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLRENDEREROPENGLCG_PROGRAMUNIFORMCG_H__
#define __PLRENDEREROPENGLCG_PROGRAMUNIFORMCG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Cg/cgGL.h>
#include <PLRendererOpenGL/ProgramUniform.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL Cg renderer program uniform
*/
class ProgramUniformCg : public PLRendererOpenGL::ProgramUniform {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ProgramCg;


	//[-------------------------------------------------------]
	//[ Public virtual ProgramUniform functions               ]
	//[-------------------------------------------------------]
	public:
		virtual int Set(GLenum nOpenGLTextureTarget, GLuint nOpenGLTexture) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pCgParameter
		*    Cg program parameter, must be valid!
		*/
		ProgramUniformCg(CGparameter pCgParameter);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ProgramUniformCg();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		CGparameter m_pCgParameter;	/**< Cg program parameter, always valid! */


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
} // PLRendererOpenGLCg


#endif // __PLRENDEREROPENGLCG_PROGRAMUNIFORMCG_H__
