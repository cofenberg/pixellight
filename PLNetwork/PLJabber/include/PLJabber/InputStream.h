/*********************************************************\
 *  File: InputStream.h                                  *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLJABBER_INPUTSTREAM_H__
#define __PLJABBER_INPUTSTREAM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Xml/XmlDocument.h>
#include "PLJabber/PLJabber.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
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
*    XML input stream
*/
class InputStream {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLJABBER_API InputStream(JabberConnection &cJabberConnection);

		/**
		*  @brief
		*    Destructor
		*/
		PLJABBER_API ~InputStream();

		/**
		*  @brief
		*    Parse incoming stream data
		*
		*  @param[in] sStream
		*    Incoming stream data
		*/
		PLJABBER_API void ParseStream(const PLGeneral::String &sStream);

		/**
		*  @brief
		*    Save the complete XML stream to a file
		*
		*  @param[in] sFilename
		*    Name of file
		*/
		PLJABBER_API void Save(const PLGeneral::String &sFilename);


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
		InputStream(const InputStream &cSource);

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
		InputStream &operator =(const InputStream &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		JabberConnection		*m_pJabberConnection;	/**< Jabber connection (always valid!) */
		PLGeneral::XmlDocument   m_cXml;				/**< The XML document that is streamed */
		PLGeneral::XmlElement	*m_pStream;				/**< Root node of XML stream, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLJabber


#endif // __PLJABBER_INPUTSTREAM_H__
