/*********************************************************\
 *  File: PLScenePortal.h                                *
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


#ifndef __PL_SCENEPORTAL_H__
#define __PL_SCENEPORTAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <vector>
#include "PL3dsMaxSceneExport/PLSceneNode.h"


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract exported PixelLight portal
*/
class PLScenePortal : public PLSceneNode {


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cContainer
		*    Container this portal is in
		*  @param[in] cIGameNode
		*    IGame node this scene node represents
		*  @param[in] sName
		*    Name of this scene node
		*  @param[in] nType
		*    Scene node type
		*  @param[in] sClassName
		*    PixelLight class name of this scene node
		*/
		PLScenePortal(PLSceneContainer &cContainer, IGameNode &cIGameNode, const PLCore::String &sName, EType nType, const PLCore::String &sClassName);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLScenePortal();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		std::vector<Point3> m_lstVertices;	/**< The portal vertices (node space) */
		Point3				m_vCenter;		/**< Portal center (world space) */
		Point3				m_vNormal;		/**< Portal normal (world space, must point INTO the cell the portal is in!) */


};


#endif // __PL_SCENEPORTAL_H__
