/*********************************************************\
 *  File: SystemInterfacePL.h                            *
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


#ifndef __PLLIBROCKET_SYSTEMINTERFACE_H__
#define __PLLIBROCKET_SYSTEMINTERFACE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Rocket/Core/SystemInterface.h>
#include <PLCore/String/String.h>
#include "PLlibRocket/PLlibRocket.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLlibRocket {


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
		PLLIBROCKET_API SystemInterfacePL(const PLCore::String &sLocalizationGroup = "PixelLight");

		/**
		*  @brief
		*    Destructor
		*/
		PLLIBROCKET_API virtual ~SystemInterfacePL();


	//[-------------------------------------------------------]
	//[ Public virtual Rocket::Core::SystemInterface functions ]
	//[-------------------------------------------------------]
	public:
		PLLIBROCKET_API virtual float GetElapsedTime() override;
		PLLIBROCKET_API virtual int TranslateString(Rocket::Core::String& translated, const Rocket::Core::String& input) override;
		PLLIBROCKET_API virtual bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message) override;


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
} // PLlibRocket


#endif // __PLLIBROCKET_SYSTEMINTERFACE_H__