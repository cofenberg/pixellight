/*********************************************************\
 *  File: Http.cpp                                       *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Network/Http/Http.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get status string from status code
*/
String Http::GetStatusString(EHttpStatus nStatusCode)
{
	// Get status code
	switch (nStatusCode) {
		case Http_000_Unknown:						return "Unknown status code (invalid)";
		case Http_100_Continue:						return "100 Continue";
		case Http_101_SwitchingProtocols:			return "101 Switching Protocols";
		case Http_200_OK:							return "200 OK";
		case Http_201_Created:						return "201 Created";
		case Http_202_Accepted:						return "202 Accepted";
		case Http_203_NonAuthoritativeInformation:	return "203 Non-Authoritative Information";
		case Http_204_NoContent:					return "204 No Content";
		case Http_205_ResetContent:					return "205 Reset Content";
		case Http_206_PartialContent:				return "206 Partial Content";
		case Http_300_MultipleChoices:				return "300 Multiple Choices";
		case Http_301_MovedPermanently:				return "301 Moved Permanently";
		case Http_302_Found:						return "302 Found";
		case Http_303_SeeOther:						return "303 See Other";
		case Http_304_NotModified:					return "304 Not Modified";
		case Http_305_UseProxy:						return "305 Use Proxy";
		case Http_307_TemporaryRedirect:			return "307 Temporary Redirect";
		case Http_400_BadRequest:					return "400 Bad Request";
		case Http_401_Unauthorized:					return "401 Unauthorized";
		case Http_403_Forbidden:					return "403 Forbidden";
		case Http_404_NotFound:						return "404 Not Found";
		case Http_405_MethodNotAllowed:				return "405 Method Not Allowed";
		case Http_406_NotAcceptable:				return "406 Not Acceptable";
		case Http_407_ProxyAuthenticationRequired:	return "407 Proxy Authentication Required";
		case Http_408_RequestTimeout:				return "408 Request Timeout";
		case Http_409_Conflict:						return "409 Conflict";
		case Http_410_Gone:							return "410 Gone";
		case Http_411_LengthRequired:				return "411 Length Required";
		case Http_412_PreconditionFailed:			return "412 Precondition Failed";
		case Http_413_RequestEntityTooLarge:		return "413 Request Entity Too Large";
		case Http_414_RequestURITooLong:			return "414 Request-URI Too Long";
		case Http_415_UnsupportedMediaType:			return "415 Unsupported Media Type";
		case Http_416_RequestedRangeNotSatisfiable:	return "416 Requested Range Not Satisfiable";
		case Http_417_ExpectationFailed:			return "417 Expectation Failed";
		case Http_500_InternalServerError:			return "500 Internal Server Error";
		case Http_501_NotImplemented:				return "501 Not Implemented";
		case Http_502_BadGateway:					return "502 Bad Gateway";
		case Http_503_ServiceUnavailable:			return "503 Service Unavailable";
		case Http_504_GatewayTimeout:				return "504 Gateway Timeout";
		case Http_505_HTTPVersionNotSupported:		return "505 HTTP Version Not Supported";
		default:									return "";
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
