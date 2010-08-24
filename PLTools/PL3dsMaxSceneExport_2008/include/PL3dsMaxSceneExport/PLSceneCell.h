/*********************************************************\
 *  File: PLSceneCell.h                                  *
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


#ifndef __PL_SCENECELL_H__
#define __PL_SCENECELL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PL3dsMaxSceneExport/PLSceneContainer.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PLSceneCellPortal;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Exported PixelLight scene cell
*/
class PLSceneCell : public PLSceneContainer {


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
		*    Container this container is in
		*  @param[in] sName
		*    Name of this scene node
		*/
		PLSceneCell(PLSceneContainer &cContainer, const std::string &sName);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneCell();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		std::vector<PLSceneCellPortal*> m_lstOutgoingCellPortals;	/**< List of outgoing cell-portals (pointer to scene nodes - do NOT delete!) */
		std::vector<PLSceneCellPortal*> m_lstIncomingCellPortals;	/**< List of incoming cell-portals (pointer to scene nodes - do NOT delete!) */


	//[-------------------------------------------------------]
	//[ Private virtual PLSceneNode functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual void WriteToFile(PLGeneral::XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir);


	//[-------------------------------------------------------]
	//[ Private virtual PLSceneContainer functions            ]
	//[-------------------------------------------------------]
	private:
		virtual void PostProcess();


};


#endif // __PL_SCENECELL_H__
