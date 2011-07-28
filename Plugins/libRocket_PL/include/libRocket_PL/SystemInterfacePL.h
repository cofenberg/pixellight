/*********************************************************\
 *  File: SystemInterfacePL.h                            *
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


#ifndef __LIBROCKET_PL_SYSTEMINTERFACE_H__
#define __LIBROCKET_PL_SYSTEMINTERFACE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Rocket/Core/SystemInterface.h>
#include <PLCore/String/String.h>
#include "libRocket_PL/libRocket_PL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A system interface for Rocket into PixelLight
*/
class SystemInterfacePL : public Rocket::Core::SystemInterface {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sLocalizationGroup
		*    Localization group the texts to translate are in
		*/
		LIBROCKET_PL_API SystemInterfacePL(const PLCore::String &sLocalizationGroup = "PixelLight");

		/**
		*  @brief
		*    Destructor
		*/
		LIBROCKET_PL_API virtual ~SystemInterfacePL();


	//[-------------------------------------------------------]
	//[ Public virtual Rocket::Core::SystemInterface functions ]
	//[-------------------------------------------------------]
	public:
		LIBROCKET_PL_API virtual float GetElapsedTime() override;
		LIBROCKET_PL_API virtual int TranslateString(Rocket::Core::String& translated, const Rocket::Core::String& input) override;
		LIBROCKET_PL_API virtual bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		SystemInterfacePL(const SystemInterfacePL &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		SystemInterfacePL &operator =(const SystemInterfacePL &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sLocalizationGroup;	/**< Localization group the texts to translate are in */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL


#endif // __LIBROCKET_PL_SYSTEMINTERFACE_H__