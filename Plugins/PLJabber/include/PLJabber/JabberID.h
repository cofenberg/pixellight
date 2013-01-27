/*********************************************************\
 *  File: JabberID.h                                     *
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


#ifndef __PLJABBER_JABBERID_H__
#define __PLJABBER_JABBERID_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include "PLJabber/PLJabber.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLJabber {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Jabber ID
*/
class JabberID {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sJabberID
		*    Jabber ID as string
		*/
		PLJABBER_API JabberID(const PLCore::String &sJabberID = "");

		/**
		*  @brief
		*    Destructor
		*/
		PLJABBER_API ~JabberID();

		/**
		*  @brief
		*    Get Jabber ID
		*
		*  @returns
		*    Jabber ID as string
		*/
		PLJABBER_API PLCore::String GetValue() const;

		/**
		*  @brief
		*    Set Jabber ID
		*
		*  @param[in] sJabberID
		*    Jabber ID as string
		*/
		PLJABBER_API void SetValue(const PLCore::String &sJabberID);

		/**
		*  @brief
		*    Get user name
		*
		*  @returns
		*    User name
		*/
		PLJABBER_API PLCore::String GetUserName() const;

		/**
		*  @brief
		*    Set user name
		*
		*  @param[in] sUserName
		*    User name
		*/
		PLJABBER_API void SetUserName(const PLCore::String &sUserName);

		/**
		*  @brief
		*    Get host name
		*
		*  @returns
		*    Host name
		*/
		PLJABBER_API PLCore::String GetHostName() const;

		/**
		*  @brief
		*    Set host name
		*
		*  @param[in] sHostName
		*    Host name
		*/
		PLJABBER_API void SetHostName(const PLCore::String &sHostName);

		/**
		*  @brief
		*    Get resource
		*
		*  @returns
		*    Resource
		*/
		PLJABBER_API PLCore::String GetRessource() const;

		/**
		*  @brief
		*    Set resource
		*
		*  @param[in] sRessource
		*    Resource
		*/
		PLJABBER_API void SetRessource(const PLCore::String &sRessource);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Parses the jabber ID to determine it's components (user name, host name and resource)
		*/
		void ParseJabberID();

		/**
		*  @brief
		*    Composes the jabber ID from it's components (user name, host name and resource)
		*/
		void ComposeJabberID();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sJabberID;		/**< Complete Jabber ID */
		PLCore::String m_sUserName;		/**< User name */
		PLCore::String m_sHostName;		/**< Host name */
		PLCore::String m_sRessource;	/**< Resource */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLJabber


#endif // __PLJABBER_JABBERID_H__
