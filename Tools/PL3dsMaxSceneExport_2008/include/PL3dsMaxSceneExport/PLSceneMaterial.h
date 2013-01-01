/*********************************************************\
 *  File: PLSceneMaterial.h                              *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PL_SCENEMATERIAL_H__
#define __PL_SCENEMATERIAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <string>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PLScene;
class IGameMaterial;
namespace PLCore {
	class XmlElement;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract exported PixelLight material
*/
class PLSceneMaterial {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLScene;
	friend class PLSceneMesh;
	friend class PLSceneMaterialBakeShell;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the IGame material this material comes from
		*
		*  @return
		*    The IGame node this material comes from, can be a null pointer
		*/
		IGameMaterial *GetIGameMaterial() const;

		/**
		*  @brief
		*    Returns the material name
		*
		*  @return
		*    The material name
		*/
		PLCore::String GetName() const;

		/**
		*  @brief
		*    Returns the reference count of this material
		*
		*  @return
		*    The reference count of this material
		*/
		unsigned int GetReferenceCount() const;

		/**
		*  @brief
		*    Saves the material
		*
		*  @param[in] sApplicationDrive
		*    Application drive
		*  @param[in] sApplicationDir
		*    Application directory
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Save(const PLCore::String &sApplicationDrive, const PLCore::String &sApplicationDir);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cScene
		*    Scene this material is in
		*  @param[in] pParentIGameMaterial
		*    Parent of the IGame material, can be a null pointer
		*  @param[in] pIGameMaterial
		*    IGame material this material comes from, can be a null pointer
		*  @param[in] sName
		*    Name of this material
		*/
		PLSceneMaterial(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial *pIGameMaterial, const PLCore::String &sName);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneMaterial();

		/**
		*  @brief
		*    Saves a texture
		*
		*  @param[in] cMaterialElement
		*    Material XML element to insert into
		*  @param[in] sFilename
		*    Filename of the texture to save
		*  @param[in] sSemantic
		*    Texture semantic
		*  @param[in] bNormalMap_xGxR
		*    Is this a 'xGxR' normal map?
		*/
		void SaveTexture(PLCore::XmlElement &cMaterialElement, const PLCore::String &sFilename, const PLCore::String &sSemantic, bool bNormalMap_xGxR = false);


	//[-------------------------------------------------------]
	//[ Protected virtual PLSceneMaterial functions           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Saves the parameters
		*
		*  @param[in] cMaterialElement
		*    Material XML element to insert into
		*/
		virtual void SaveParameters(PLCore::XmlElement &cMaterialElement) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLScene		   *m_pScene;				/**< PL owner scene (always valid!) */
		IGameMaterial  *m_pParentIGameMaterial;	/**< Parent of the IGame material, can be a null pointer */
		IGameMaterial  *m_pIGameMaterial;		/**< IGame material this material comes from (always valid!) */
		PLCore::String  m_sName;				/**< Name of this material */
		unsigned int    m_nReferenceCount;		/**< Reference count of this material */


	//[-------------------------------------------------------]
	//[ Private static functions                              ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Creates a material
		*
		*  @param[in] cScene
		*    Scene this material is in
		*  @param[in] pParentIGameMaterial
		*    Parent of the IGame material, can be a null pointer
		*  @param[in] cIGameMaterial
		*    IGame material this material comes from
		*  @param[in] sName
		*    Name of this material
		*
		*  @return
		*    The created material, a null pointer on error
		*/
		static PLSceneMaterial *Create(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const PLCore::String &sName);


};


#endif // __PL_SCENEMATERIAL_H__
