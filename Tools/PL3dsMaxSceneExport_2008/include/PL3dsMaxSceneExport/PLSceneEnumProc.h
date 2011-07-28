/*********************************************************\
 *  File: PLSceneEnumProc.h                              *
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


#ifndef __PL_SCENEENUMPROC_H__
#define __PL_SCENEENUMPROC_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <max.h>
#include <string>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PLLog;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Main export class
*/
class PLSceneEnumProc : public ITreeEnumProc {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		PLSceneEnumProc(const char szName[], Interface &cMaxInterface, DWORD nMaxOptions);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Writes down the current unit display information
		*
		*  @param[in] cLog
		*    Log to write into
		*/
		void LogUnitDisplayInformation(PLLog &cLog) const;

		/**
		*  @brief
		*    Packs everything 'PLViewer' requires into the exported directory
		*
		*  @param[in] sTargetDirectory
		*    Application directory were to copy all data into
		*/
		void Publish(const std::string &sTargetDirectory) const;


	//[-------------------------------------------------------]
	//[ Public virtual ITreeEnumProc functions                ]
	//[-------------------------------------------------------]
	public:
		virtual int callback(INode *pMaxNode) override;


};


#endif // __PL_SCENEENUMPROC_H__
