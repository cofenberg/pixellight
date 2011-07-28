/*********************************************************\
 *  File: PLSceneCellPortal.h                            *
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


#ifndef __PL_SCENECELLPORTAL_H__
#define __PL_SCENECELLPORTAL_H__
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
*    Exported PixelLight cell-portal
*/
class PLSceneCellPortal : public PLScenePortal {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLSceneContainer;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the name of the target cell
		*
		*  @return
		*    The name of the target cell
		*/
		const std::string &GetTargetCell() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cContainer
		*    Container this cell-portal is in
		*  @param[in] cIGameNode
		*    IGame node this scene node represents
		*  @param[in] sName
		*    Name of this scene node
		*  @param[in] sTargetCell
		*    Name of the target cell
		*/
		PLSceneCellPortal(PLSceneContainer &cContainer, IGameNode &cIGameNode, const std::string &sName, const std::string &sTargetCell);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneCellPortal();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		std::string m_sTargetCell;	/**< Name of the target cell */


	//[-------------------------------------------------------]
	//[ Private virtual PLSceneNode functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual void WriteToFile(PLCore::XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir) override;


};


#endif // __PL_SCENECELLPORTAL_H__
