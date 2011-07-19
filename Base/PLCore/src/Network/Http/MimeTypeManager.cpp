/*********************************************************\
 *  File: MimeTypeManager.cpp                            *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/File/Url.h"
#include "PLCore/Network/Http/MimeTypeManager.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get mime type from filename
*/
String MimeTypeManager::GetMimeType(const String &sFilename)
{
	// Get filename extension
	const String sExtension = Url(sFilename).GetExtension();

	// Check known MIME types
	if (sExtension == "css")	return "text/css";
	if (sExtension == "html")	return "text/html";
	if (sExtension == "htm")	return "text/html";
	if (sExtension == "txt")	return "text/plain";
	if (sExtension == "xml")	return "text/xml";
	if (sExtension == "gif")	return "image/gif";
	if (sExtension == "ico")	return "image/vnd.microsoft.icon";
	if (sExtension == "jpg")	return "image/jpeg";
	if (sExtension == "png")	return "image/png";
	if (sExtension == "svg")	return "image/svg+xml";
	if (sExtension == "tif")	return "image/tiff";
	if (sExtension == "xhtml")	return "application/xhtml+xml";
	if (sExtension == "js")		return "application/x-javascript";
	if (sExtension == "pdf")	return "application/pdf";

	// Unknown MIME type, assume a text file
	return "text/plain";
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
