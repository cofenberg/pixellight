/*********************************************************\
 *  File: SystemInterfacePL.h                            *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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