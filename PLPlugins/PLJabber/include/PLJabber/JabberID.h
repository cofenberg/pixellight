/*********************************************************\
 *  File: JabberID.h                                     *
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


#ifndef __PLJABBER_JABBERID_H__
#define __PLJABBER_JABBERID_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/String.h>
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
		PLJABBER_API JabberID(const PLGeneral::String &sJabberID = "");

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
		PLJABBER_API PLGeneral::String GetValue() const;

		/**
		*  @brief
		*    Set Jabber ID
		*
		*  @param[in] sJabberID
		*    Jabber ID as string
		*/
		PLJABBER_API void SetValue(const PLGeneral::String &sJabberID);

		/**
		*  @brief
		*    Get user name
		*
		*  @returns
		*    User name
		*/
		PLJABBER_API PLGeneral::String GetUserName() const;

		/**
		*  @brief
		*    Set user name
		*
		*  @param[in] sUserName
		*    User name
		*/
		PLJABBER_API void SetUserName(const PLGeneral::String &sUserName);

		/**
		*  @brief
		*    Get host name
		*
		*  @returns
		*    Host name
		*/
		PLJABBER_API PLGeneral::String GetHostName() const;

		/**
		*  @brief
		*    Set host name
		*
		*  @param[in] sHostName
		*    Host name
		*/
		PLJABBER_API void SetHostName(const PLGeneral::String &sHostName);

		/**
		*  @brief
		*    Get ressource
		*
		*  @returns
		*    Ressource
		*/
		PLJABBER_API PLGeneral::String GetRessource() const;

		/**
		*  @brief
		*    Set ressource
		*
		*  @param[in] sRessource
		*    Ressource
		*/
		PLJABBER_API void SetRessource(const PLGeneral::String &sRessource);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Parses the jabber ID to determine it's components (user name, host name and ressource)
		*/
		void ParseJabberID();

		/**
		*  @brief
		*    Composes the jabber ID from it's components (user name, host name and ressource)
		*/
		void ComposeJabberID();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sJabberID;	/**< Complete Jabber ID */
		PLGeneral::String m_sUserName;	/**< User name */
		PLGeneral::String m_sHostName;	/**< Host name */
		PLGeneral::String m_sRessource;	/**< Ressource */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLJabber


#endif // __PLJABBER_JABBERID_H__
