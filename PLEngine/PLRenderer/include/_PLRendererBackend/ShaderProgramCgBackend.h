/*********************************************************\
 *  File: ShaderProgramCgBackend.h                       *
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


#ifndef __PLRENDERER_SHADERPROGRAMCGBACKEND_H__
#define __PLRENDERER_SHADERPROGRAMCGBACKEND_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Cg/cg.h>
#include <PLRenderer/Renderer/ShaderProgram.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Shader program Cg backend implementation
*/
class ShaderProgramCgBackend : public ShaderProgram {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Renderer;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ShaderProgramCgBackend();

		/**
		*  @brief
		*    Returns the Cg shader program profile this shader program is using
		*
		*  @return
		*    The Cg shader program profile this shader program is using
		*/
		CGprofile GetCgProfile() const;

		/**
		*  @brief
		*    Returns the Cg program
		*
		*  @return
		*    The Cg program
		*/
		CGprogram GetCgProgram() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*  @param[in] nType
		*    Resource type
		*  @param[in] sDefines
		*    Additional defines for the shader program
		*  @param[in] sEntry
		*    The entry point to the program in the shader program source. If empty, 'main' is used by default.
		*/
		ShaderProgramCgBackend(Renderer &cRenderer, EType nType, const PLGeneral::String &sDefines = "",
							   const PLGeneral::String &sEntry = "main");

		/**
		*  @brief
		*    De-initializes the shader program
		*/
		void DeInit();


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Initializes the shader program
		*
		*  @param[in] pProgram
		*    Shader program this shader is using
		*  @param[in] pCgProfile
		*    Profile requirement
		*/
		virtual void Init(const void *pProgram, CGprofile pCgProfile) = 0;


	//[-------------------------------------------------------]
	//[ Protected static Cg callback functions                ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Internal Cg error callback function
		*/
		static void CgErrorCallback();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Static data
		static CGcontext		 m_pCgContext;		/**< Cg shader program context, can be NULL */
		static PLGeneral::uint32 m_nContexCounter;	/**< Context counter */

		// Per shader program data
		CGprofile m_pCgProfile;			/**< Cg profile */
		CGprogram m_pCgProgram;			/**< Cg program */
		CGprofile m_pCgProfileBackup;	/**< Cg profile backup */


	//[-------------------------------------------------------]
	//[ Public virtual ShaderProgram functions                ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetProfile() const;


	//[-------------------------------------------------------]
	//[ Public virtual Parameters functions                   ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsParameter(const PLGeneral::String &sName) const;
		virtual PLGeneral::String GetParameterString(const PLGeneral::String &sName) const;
		virtual bool SetParameterString(const PLGeneral::String &sName, const PLGeneral::String &sValue);
		// Integer
		virtual bool GetParameter1i(const PLGeneral::String &sName, int &nX) const;
		virtual bool SetParameter1i(const PLGeneral::String &sName, int nX);
		// Integer2
		virtual bool GetParameter2i(const PLGeneral::String &sName, int &nX, int &nY) const;
		virtual bool GetParameter2iv(const PLGeneral::String &sName, int nValue[]) const;
		virtual bool SetParameter2i(const PLGeneral::String &sName, int nX, int nY);
		virtual bool SetParameter2iv(const PLGeneral::String &sName, const int nValue[]);
		// Integer3
		virtual bool GetParameter3i(const PLGeneral::String &sName, int &nX, int &nY, int &nZ) const;
		virtual bool GetParameter3iv(const PLGeneral::String &sName, int nValue[]) const;
		virtual bool SetParameter3i(const PLGeneral::String &sName, int nX, int nY, int nZ);
		virtual bool SetParameter3iv(const PLGeneral::String &sName, const int nValue[]);
		// Integer4
		virtual bool GetParameter4i(const PLGeneral::String &sName, int &nX, int &nY, int &nZ, int &nW) const;
		virtual bool GetParameter4iv(const PLGeneral::String &sName, int nValue[]) const;
		virtual bool SetParameter4i(const PLGeneral::String &sName, int nX, int nY, int nZ, int nW);
		virtual bool SetParameter4iv(const PLGeneral::String &sName, const int nValue[]);
		// Float
		virtual bool GetParameter1f(const PLGeneral::String &sName, float &fX) const;
		virtual bool SetParameter1f(const PLGeneral::String &sName, float fX);
		// Float2
		virtual bool GetParameter2f(const PLGeneral::String &sName, float &fX, float &fY) const;
		virtual bool GetParameter2fv(const PLGeneral::String &sName, float fValue[]) const;
		virtual bool SetParameter2f(const PLGeneral::String &sName, float fX, float fY);
		virtual bool SetParameter2fv(const PLGeneral::String &sName, const float fValue[]);
		// Float3
		virtual bool GetParameter3f(const PLGeneral::String &sName, float &fX, float &fY, float &fZ) const;
		virtual bool GetParameter3fv(const PLGeneral::String &sName, float fValue[]) const;
		virtual bool SetParameter3f(const PLGeneral::String &sName, float fX, float fY, float fZ);
		virtual bool SetParameter3fv(const PLGeneral::String &sName, const float fValue[]);
		// Float4
		virtual bool GetParameter4f(const PLGeneral::String &sName, float &fX, float &fY, float &fZ, float &fW) const;
		virtual bool GetParameter4fv(const PLGeneral::String &sName, float fValue[]) const;
		virtual bool SetParameter4f(const PLGeneral::String &sName, float fX, float fY, float fZ, float fW);
		virtual bool SetParameter4fv(const PLGeneral::String &sName, const float fValue[]);
		// Double
		virtual bool GetParameter1d(const PLGeneral::String &sName, double &fX) const;
		virtual bool SetParameter1d(const PLGeneral::String &sName, double fX);
		// Double2
		virtual bool GetParameter2d(const PLGeneral::String &sName, double &fX, double &fY) const;
		virtual bool GetParameter2dv(const PLGeneral::String &sName, double fValue[]) const;
		virtual bool SetParameter2d(const PLGeneral::String &sName, double fX, double fY);
		virtual bool SetParameter2dv(const PLGeneral::String &sName, const double fValue[]);
		// Double3
		virtual bool GetParameter3d(const PLGeneral::String &sName, double &fX, double &fY, double &fZ) const;
		virtual bool GetParameter3dv(const PLGeneral::String &sName, double fValue[]) const;
		virtual bool SetParameter3d(const PLGeneral::String &sName, double fX, double fY, double fZ);
		virtual bool SetParameter3dv(const PLGeneral::String &sName, const double fValue[]);
		// Double4
		virtual bool GetParameter4d(const PLGeneral::String &sName, double &fX, double &fY, double &fZ, double &fW) const;
		virtual bool GetParameter4dv(const PLGeneral::String &sName, double fValue[]) const;
		virtual bool SetParameter4d(const PLGeneral::String &sName, double fX, double fY, double fZ, double fW);
		virtual bool SetParameter4dv(const PLGeneral::String &sName, const double fValue[]);
		// Float3x3
		virtual bool GetParameterFloat3x3(const PLGeneral::String &sName, float fValue[]) const;
		virtual bool SetParameterFloat3x3(const PLGeneral::String &sName, const float fValue[]);
		// Float3x4
		virtual bool GetParameterFloat3x4(const PLGeneral::String &sName, float fValue[]) const;
		virtual bool SetParameterFloat3x4(const PLGeneral::String &sName, const float fValue[]);
		// Float4x4
		virtual bool GetParameterMatrixfv(const PLGeneral::String &sName, float fValue[]) const;
		virtual bool SetParameterMatrixfv(const PLGeneral::String &sName, const float fValue[]);
		// Double4x4
		virtual bool GetParameterMatrixdv(const PLGeneral::String &sName, double fValue[]) const;
		virtual bool SetParameterMatrixdv(const PLGeneral::String &sName, const double fValue[]);
		// Texture buffer
		virtual PLRenderer::TextureBuffer *GetParameterTextureBuffer(const PLGeneral::String &sName) const;
		virtual PLRenderer::Texture *GetParameterTexture(const PLGeneral::String &sName) const;


	//[-------------------------------------------------------]
	//[ Protected virtual Resource functions                  ]
	//[-------------------------------------------------------]
	protected:
		virtual void BackupDeviceData(PLGeneral::uint8 **ppBackup);
		virtual void RestoreDeviceData(PLGeneral::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer


#endif // __PLRENDERER_SHADERPROGRAMCGBACKEND_H__
