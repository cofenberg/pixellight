/*********************************************************\
 *  File: Url.h                                          *
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


#ifndef __PLGENERAL_URL_H__
#define __PLGENERAL_URL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Contains a path or URL (Uniform Resource Locator)
*
*  @note
*    - An URL is always stored using a protocol ("file://" for a local path) and "/" as the delimiter.
*    - For getting the URL in native style, use the specific functions (GetWindowsPath(), GetUnixPath(), GetNativePath())
*/
class Url {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGENERAL_API Url();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cUrl
		*    URL to copy
		*/
		PLGENERAL_API Url(const Url &cUrl);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sUrl
		*    URL as string
		*/
		PLGENERAL_API Url(const String &sUrl);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API ~Url();

		/**
		*  @brief
		*    Copy an URL
		*
		*  @param[in] cUrl
		*    URL to copy
		*
		*  @return
		*    Reference to this URL
		*/
		PLGENERAL_API Url &operator =(const Url &cUrl);

		/**
		*  @brief
		*    Copy an URL (passed as a string)
		*
		*  @param[in] sUrl
		*    String containing URL to copy
		*
		*  @return
		*    Reference to this URL
		*/
		PLGENERAL_API Url &operator =(const String &sUrl);

		/**
		*  @brief
		*    Concatenate an URL
		*
		*  @param[in] cUrl
		*    URL to add
		*
		*  @return
		*    Resulting URL
		*
		*  @note
		*    - Both URLs must be valid
		*    - The second URL must be relative
		*    - The protocol of the second URL must match the first one or be empty
		*/
		PLGENERAL_API Url operator +(const Url &cUrl) const;

		/**
		*  @brief
		*    Concatenate an URL
		*
		*  @param[in] cUrl
		*    URL to add
		*
		*  @return
		*    Reference to this URL
		*
		*  @see
		*    - operator +
		*/
		PLGENERAL_API Url &operator +=(const Url &cUrl);

		/**
		*  @brief
		*    Get value in URL notation
		*
		*  @return
		*    Path in URL style
		*
		*  @note
		*    - If the value contains a local file path, a file:// URL is returned
		*    - Any other URL (e.g. http://) is returned directly
		*/
		PLGENERAL_API String GetUrl() const;

		/**
		*  @brief
		*    Get value in native notation
		*
		*  @return
		*    Path in native path format style
		*
		*  @note
		*    - Returns the URL in native (Windows/Unix) notation, if it is a local path
		*    - If it is another URL (e.g. http://), the URL is returned
		*/
		PLGENERAL_API String GetNativePath() const;

		/**
		*  @brief
		*    Get value in Windows notation
		*
		*  @return
		*    Path in Windows format style
		*
		*  @note
		*    - If the value contains a valid Windows or Unix file path or an file:// URL, it is returned in Windows style
		*    - If the value contains another URL (e.g. http://), the URL is returned without being converted
		*/
		PLGENERAL_API String GetWindowsPath() const;

		/**
		*  @brief
		*    Get value in Unix notation
		*
		*  @return
		*    Path in Unix format style
		*
		*  @note
		*    - If the value contains a valid Windows or Unix file path or an file:// URL, it is returned in Unix style
		*    - If the value contains another URL (e.g. http://), the URL is returned without being converted
		*/
		PLGENERAL_API String GetUnixPath() const;

		/**
		*  @brief
		*    Returns if the URL is valid
		*
		*  @return
		*    'true' if the value is valid, else 'false'
		*/
		PLGENERAL_API bool IsValid() const;

		/**
		*  @brief
		*    Check if the URL is a valid native file path
		*
		*  @return
		*    'true', if the path is valid in the native path format style
		*
		*  @note
		*    - A wrapper for IsValidWindowsPath()/IsValidUnixPath() based on the used system
		*/
		PLGENERAL_API bool IsValidNativePath() const;

		/**
		*  @brief
		*    Check if the URL is valid as a Windows file path
		*
		*  @return
		*    'true', if the path is valid in Windows format style
		*
		*  @note
		*    - 'false', if the protocol is any other than "file://" or empty
		*    - 'false', if the file root is any other than "X:/" or empty ("/" is invalid!)
		*/
		PLGENERAL_API bool IsValidWindowsPath() const;

		/**
		*  @brief
		*    Check if the URL is valid as a Unix file path
		*
		*  @return
		*    'true', if the path is valid in Unix format style
		*
		*  @note
		*    - 'false', if the protocol is any other than "file://" or empty
		*    - 'false', if the file root is any other than "/" or empty ("X:/" is invalid!)
		*/
		PLGENERAL_API bool IsValidUnixPath() const;

		/**
		*  @brief
		*    Returns if the URL is empty
		*
		*  @return
		*    'true' if the path is empty, else 'false'
		*
		*  @note
		*    - The protocol is ignored
		*/
		PLGENERAL_API bool IsEmpty() const;

		/**
		*  @brief
		*    Returns if the URL is absolute
		*
		*  @return
		*    'true' if the path is absolute, else 'false'
		*/
		PLGENERAL_API bool IsAbsolute() const;

		/**
		*  @brief
		*    Returns if the URL is relative
		*
		*  @return
		*    'true' if the path is relative, else 'false'
		*/
		PLGENERAL_API bool IsRelative() const;

		/**
		*  @brief
		*    Returns if the URL targets a directory
		*
		*  @return
		*    'true' if the path targets a directory, else 'false'
		*
		*  @note
		*    - Returns true, if the URL ends with "/" which indicates a directory
		*    - This is a consideration on pure syntax level - it does not mean that the path pointed
		*      to is really a directory or that it even exists!
		*/
		PLGENERAL_API bool IsDirectory() const;

		/**
		*  @brief
		*    Returns the protocol part
		*
		*  @return
		*    Protocol part (e.g. "file://" or "http://")
		*/
		PLGENERAL_API String GetProtocol() const;

		/**
		*  @brief
		*    Returns the root part
		*
		*  @return
		*    Root part (e.g. "C:/" or "/")
		*/
		PLGENERAL_API String GetRoot() const;

		/**
		*  @brief
		*    Returns the path (without root and filename)
		*
		*  @return
		*    Path (e.g. "Programme/")
		*/
		PLGENERAL_API String GetPath() const;

		/**
		*  @brief
		*    Returns the filename (including it's extension)
		*
		*  @return
		*    Filename (e.g. "readme.txt")
		*/
		PLGENERAL_API String GetFilename() const;

		/**
		*  @brief
		*    Returns the filename without it's extension
		*
		*  @return
		*    Filename without extension (e.g. "readme")
		*/
		PLGENERAL_API String GetTitle() const;

		/**
		*  @brief
		*    Returns the file extension
		*
		*  @return
		*    File extension (e.g. "txt")
		*/
		PLGENERAL_API String GetExtension() const;

		/**
		*  @brief
		*    Returns the path without the filename
		*
		*  @return
		*    Path without filename (e.g. "C:\Programme\App\App.exe" -> "C:\Programme\App\")
		*/
		PLGENERAL_API String CutFilename() const;

		/**
		*  @brief
		*    Returns the path and filename without extension
		*
		*  @return
		*    Path and filename without extension (e.g. "C:\Programme\App\App.exe" -> "C:\Programme\App\App")
		*/
		PLGENERAL_API String CutExtension() const;

		/**
		*  @brief
		*    Returns the first part of the path
		*
		*  @param[out] nPathPos
		*    Will receive the new position within the path
		*
		*  @return
		*    First path
		*
		*  @note
		*    - Ignores the root (e.g. "C:/" or "/")
		*    - Example: "test/foo.bar" -> "test"
		*/
		PLGENERAL_API String GetFirstPath(uint32 &nPathPos) const;

		/**
		*  @brief
		*    Returns the first part of the path
		*
		*  @return
		*    First path
		*
		*  @note
		*    - Ignores the root (e.g. "C:/" or "/")
		*    - Example: "test/foo.bar" -> "test"
		*/
		PLGENERAL_API String GetFirstPath() const;

		/**
		*  @brief
		*    Returns the next part of the path
		*
		*  @param[in, out] nPathPos
		*    Position within the path
		*
		*  @return
		*    First path
		*
		*  @note
		*    - Call GetFirstPath() first
		*/
		PLGENERAL_API String GetNextPath(uint32 &nPathPos) const;

		/**
		*  @brief
		*    Collapses the URL
		*
		*  @return
		*    Reference to this object
		*
		*  @note
		*    - Collapsing means, '..' and '.' inside the path will be resolved (on a syntactical level only!)
		*    - If the URL is invalid, the function will fail
		*/
		PLGENERAL_API Url &Collapse();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Sets the value of the URL
		*
		*  @param[in] sUrl
		*    New URL value
		*/
		void SetValue(const String &sUrl);

		/**
		*  @brief
		*    Checks if the character is a letter (a..z, A..Z)
		*
		*  @param[in] nChar
		*    Character to check
		*
		*  @return
		*    'true', if the character is a letter, else 'false'
		*/
		bool IsLetter(char nChar) const;

		/**
		*  @brief
		*    Checks if the string is a valid name (does not contain ':', '/' or '\')
		*
		*  @param[in] sString
		*    String to check
		*
		*  @return
		*    'true', if the string is a valid name, else 'false'
		*/
		bool IsName(const String &sString) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String m_sUrl;		/**< Path or URL */
		String m_sProtocol;	/**< Protocol part (e.g. "http://") */
		String m_sRoot;		/**< Root part (e.g. "/" or "C:\") */
		String m_sPath;		/**< Path (e.g. "Programme\") */
		String m_sFilename;	/**< Filename (e.g. "readme.txt") */
		bool   m_bValid;	/**< Is the URL valid? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_URL_H__
