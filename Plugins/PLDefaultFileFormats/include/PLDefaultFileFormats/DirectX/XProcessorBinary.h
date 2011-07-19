/*********************************************************\
 *  File: XProcessorBinary.h                             *
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


#ifndef __PLDEFAULTFILEFORMATS_DIRECTX_XPROCESSORBINARY_H__
#define __PLDEFAULTFILEFORMATS_DIRECTX_XPROCESSORBINARY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLDefaultFileFormats/DirectX/XProcessor.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class File;
}
namespace PLDefaultFileFormats {
	class XToken;
	class XTokenName;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    DirectX root for binary files
*/
class XRootBinary : public XRoot {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to use
		*/
		XRootBinary(PLCore::File &cFile);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XRootBinary();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Processes a header block
		*
		*  @param[in] cTokenName
		*    Current processed name token
		*
		*  @return
		*    The processed header, a null pointer on error
		*/
		XHeader *ProcessHeader(XTokenName &cTokenName);

		/**
		*  @brief
		*    Processes a material block
		*
		*  @param[in] ppToken
		*    Current processed token (MUST be valid!)
		*
		*  @return
		*    The processed material, a null pointer on error
		*/
		XMaterial *ProcessMaterial(XToken **ppToken);

		/**
		*  @brief
		*    Processes a frame block
		*
		*  @param[in] ppToken
		*    Current processed token (MUST be valid!)
		*
		*  @return
		*    The processed frame, a null pointer on error
		*/
		XFrame *ProcessFrame(XToken **pToken);

		/**
		*  @brief
		*    Processes a frame transform matrix block
		*
		*  @param[in] cTokenName
		*    Current processed name token
		*
		*  @return
		*    The processed frame transform matrix, a null pointer on error
		*/
		XFrameTransformMatrix *ProcessFrameTransformMatrix(XTokenName &cTokenName);

		/**
		*  @brief
		*    Processes a mesh block
		*
		*  @param[in] ppToken
		*    Current processed token (MUST be valid!)
		*
		*  @return
		*    The processed mesh, a null pointer on error
		*/
		XMesh *ProcessMesh(XToken **ppToken);

		/**
		*  @brief
		*    Processes a mesh face wraps block
		*
		*  @param[in] cTokenName
		*    Current processed name token
		*
		*  @return
		*    The processed mesh face wraps, a null pointer on error
		*/
		XMeshFaceWraps *ProcessMeshFaceWraps(XTokenName &cTokenName);

		/**
		*  @brief
		*    Processes a mesh texture coordinates block
		*
		*  @param[in] cTokenName
		*    Current processed name token
		*
		*  @return
		*    The processed mesh texture coordinates, a null pointer on error
		*/
		XMeshTextureCoords *ProcessMeshTextureCoords(XTokenName &cTokenName);

		/**
		*  @brief
		*    Processes a mesh normals block
		*
		*  @param[in] cTokenName
		*    Current processed name token
		*
		*  @return
		*    The processed mesh normals, a null pointer on error
		*/
		XMeshNormals *ProcessMeshNormals(XTokenName &cTokenName);

		/**
		*  @brief
		*    Processes a mesh vertex colors block
		*
		*  @param[in] cTokenName
		*    Current processed name token
		*
		*  @return
		*    The processed mesh vertex colors, a null pointer on error
		*/
		XMeshVertexColors *ProcessMeshVertexColors(XTokenName &cTokenName);

		/**
		*  @brief
		*    Processes a mesh material list block
		*
		*  @param[in] cTokenName
		*    Current processed name token
		*
		*  @return
		*    The processed mesh material list, a null pointer on error
		*/
		XMeshMaterialList *ProcessMeshMaterialList(XTokenName &cTokenName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_DIRECTX_XPROCESSORBINARY_H__
