/*********************************************************\
 *  File: OutputStream.h                                 *
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


#ifndef __PLJABBER_OUTPUTSTREAM_H__
#define __PLJABBER_OUTPUTSTREAM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Xml/XmlDocument.h>
#include "PLJabber/PLJabber.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class XmlElement;
};
namespace PLJabber {
	class JabberConnection;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLJabber {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    XML output stream
*/
class OutputStream {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLJABBER_API OutputStream(JabberConnection &cJabberConnection);

		/**
		*  @brief
		*    Destructor
		*/
		PLJABBER_API ~OutputStream();

		/**
		*  @brief
		*    Opens the XML stream
		*
		*  @param[in] sServer
		*    Name of server
		*/
		PLJABBER_API void OpenStream(const PLCore::String &sServer);

		/**
		*  @brief
		*    Sends an XML element
		*
		*  @param[in] cElement
		*    XML element
		*/
		PLJABBER_API void SendElement(const PLCore::XmlElement &cElement) const;

		/**
		*  @brief
		*    Closes the XML stream
		*/
		PLJABBER_API void CloseStream() const;

		/**
		*  @brief
		*    Save the complete XML stream to a file
		*
		*  @param[in] sFilename
		*    Name of file
		*/
		PLJABBER_API void Save(const PLCore::String &sFilename);


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
		OutputStream(const OutputStream &cSource);

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
		OutputStream &operator =(const OutputStream &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		JabberConnection	*m_pJabberConnection;	/**< Jabber connection (always valid!) */
		PLCore::XmlDocument  m_cXml;				/**< The XML document that is streamed */
		PLCore::XmlElement	*m_pStream;				/**< Root node of XML stream, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLJabber


#endif // __PLJABBER_OUTPUTSTREAM_H__
