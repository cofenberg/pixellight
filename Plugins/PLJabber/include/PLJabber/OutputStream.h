/*********************************************************\
 *  File: OutputStream.h                                 *
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
