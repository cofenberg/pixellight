/*********************************************************\
 *  File: PLSceneObject.h                                *
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


#ifndef __PL_SCENEOBJECT_H__
#define __PL_SCENEOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PL3dsMaxSceneExport/PLSceneNode.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PLSceneMesh;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Exported PixelLight object (SNMesh)
*/
class PLSceneObject : public PLSceneNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLScene;
	friend class PLSceneContainer;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cContainer
		*    Container this object is in
		*  @param[in] cIGameNode
		*    IGame node this scene node represents
		*  @param[in] sName
		*    Name of this scene node
		*  @param[in] pMesh
		*    Mesh this object is using, can be a null pointer
		*/
		PLSceneObject(PLSceneContainer &cContainer, IGameNode &cIGameNode, const std::string &sName, PLSceneMesh *pMesh);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneObject();

		/**
		*  @brief
		*    Returns the mesh this object is using
		*
		*  @return
		*    The mesh this object is using, can be a null pointer
		*/
		PLSceneMesh *GetMesh() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLSceneMesh *m_pMesh;	/**< The mesh this object is using, can be a null pointer (managed by the scene!) */


	//[-------------------------------------------------------]
	//[ Private virtual PLSceneNode functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual void WriteToFile(PLGeneral::XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir);


};


#endif // __PL_SCENEOBJECT_H__
