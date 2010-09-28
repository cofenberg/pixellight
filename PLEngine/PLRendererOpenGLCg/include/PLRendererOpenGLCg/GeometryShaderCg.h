/*********************************************************\
 *  File: GeometryShaderCg.h                             *
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


#ifndef __PLRENDEREROPENGLCG_GEOMETRYSHADERCG_H__
#define __PLRENDEREROPENGLCG_GEOMETRYSHADERCG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Cg/cgGL.h>
#include <PLRenderer/Renderer/GeometryShader.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL Cg renderer geometry shader resource
*/
class GeometryShaderCg : public PLRenderer::GeometryShader {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ShaderLanguageCg;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~GeometryShaderCg();

		/**
		*  @brief
		*    Returns the Cg profile
		*
		*  @return
		*    The Cg profile, can be CG_PROFILE_UNKNOWN
		*/
		CGprofile GetCgProfile() const;

		/**
		*  @brief
		*    Returns the Cg geometry program
		*
		*  @return
		*    The Cg geometry program, can be NULL, do not destroy it!
		*/
		CGprogram GetCgGeometryProgram() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*/
		GeometryShaderCg(PLRenderer::Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		CGprofile		  m_pCgProfile;			/**< Used Cg profile, can be CG_PROFILE_UNKNOWN */
		PLGeneral::String m_sEntry;				/**< User defined entry point */
		CGprogram		  m_pCgGeometryProgram;	/**< Cg geometry program, can be NULL */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::AbstractShader functions   ]
	//[-------------------------------------------------------]
	public:
		virtual PLGeneral::String GetShaderLanguage() const;
		virtual PLGeneral::String GetSourceCode() const;
		virtual PLGeneral::String GetProfile() const;
		virtual PLGeneral::String GetEntry() const;
		virtual bool SetSourceCode(const PLGeneral::String &sSourceCode, const PLGeneral::String &sProfile = "", const PLGeneral::String &sEntry = "");


	//[-------------------------------------------------------]
	//[ Private virtual PLRenderer::Resource functions        ]
	//[-------------------------------------------------------]
	private:
		virtual void BackupDeviceData(PLGeneral::uint8 **ppBackup);
		virtual void RestoreDeviceData(PLGeneral::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg


#endif // __PLRENDEREROPENGLCG_GEOMETRYSHADERCG_H__
