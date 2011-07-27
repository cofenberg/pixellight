/*********************************************************\
 *  File: ConsoleWindows.h                               *
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


#ifndef __PLCORE_CONSOLE_WINDOWS_H__
#define __PLCORE_CONSOLE_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/System/Console.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Windows 'Console' implementation
*/
class ConsoleWindows : public Console {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SystemWindows;


	//[-------------------------------------------------------]
	//[ Public virtual Console functions                      ]
	//[-------------------------------------------------------]
	public:
		virtual void Print(const String &sString) const override;
		virtual int IsKeyHit() const override;
		virtual int GetCharacter(bool bEcho = false) const override;
		virtual void ClearScreen() const override;
		virtual void GetCursorPosition(uint16 &nX, uint16 &nY) const override;
		virtual void SetCursorPosition(uint16 nX, uint16 nY) const override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		ConsoleWindows();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ConsoleWindows();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONSOLE_WINDOWS_H__
