/*********************************************************\
 *  File: PLSceneMaterial.h                              *
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
		const std::string &GetName() const;

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
		bool Save(const std::string &sApplicationDrive, const std::string &sApplicationDir);


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
		PLSceneMaterial(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial *pIGameMaterial, const std::string &sName);

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
		void SaveTexture(PLCore::XmlElement &cMaterialElement, const std::string &sFilename, const std::string &sSemantic, bool bNormalMap_xGxR = false);


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
		PLScene		  *m_pScene;				/**< PL owner scene (always valid!) */
		IGameMaterial *m_pParentIGameMaterial;	/**< Parent of the IGame material, can be a null pointer */
		IGameMaterial *m_pIGameMaterial;		/**< IGame material this material comes from (always valid!) */
		std::string	   m_sName;					/**< Name of this material */
		unsigned int   m_nReferenceCount;		/**< Reference count of this material */


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
		static PLSceneMaterial *Create(PLScene &cScene, IGameMaterial *pParentIGameMaterial, IGameMaterial &cIGameMaterial, const std::string &sName);


};


#endif // __PL_SCENEMATERIAL_H__
