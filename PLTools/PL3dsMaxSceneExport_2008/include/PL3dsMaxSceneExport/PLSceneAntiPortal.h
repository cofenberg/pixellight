/*********************************************************\
 *  File: PLSceneAntiPortal.h                            *
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


#ifndef __PL_SCENEANTIPORTAL_H__
#define __PL_SCENEANTIPORTAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PL3dsMaxSceneExport/PLScenePortal.h"


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Exported PixelLight anti-portal
*/
class PLSceneAntiPortal : public PLScenePortal {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
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
		*    Container this anti-portal is in
		*  @param[in] cIGameNode
		*    IGame node this scene node represents
		*  @param[in] sName
		*    Name of this scene node
		*/
		PLSceneAntiPortal(PLSceneContainer &cContainer, IGameNode &cIGameNode, const std::string &sName);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneAntiPortal();


	//[-------------------------------------------------------]
	//[ Private virtual PLSceneNode functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual void WriteToFile(PLGeneral::XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir);


};


#endif // __PL_SCENEANTIPORTAL_H__
