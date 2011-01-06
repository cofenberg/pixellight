/*********************************************************\
 *  File: Url.cpp                                        *
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
#include "PLGeneral/Container/Stack.h"
#include "PLGeneral/File/Url.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Url::Url() :
	m_bValid(false)
{
}

/**
*  @brief
*    Copy constructor
*/
Url::Url(const Url &cUrl) :
	m_sUrl(cUrl.m_sUrl),
	m_sProtocol(cUrl.m_sProtocol),
	m_sRoot(cUrl.m_sRoot),
	m_sPath(cUrl.m_sPath),
	m_sFilename(cUrl.m_sFilename),
	m_bValid(cUrl.m_bValid)
{
}

/**
*  @brief
*    Constructor
*/
Url::Url(const String &sUrl) :
	m_bValid(false)
{
	// Save path or URL
	SetValue(sUrl);
}

/**
*  @brief
*    Destructor
*/
Url::~Url()
{
}

/**
*  @brief
*    Copy an URL
*/
Url &Url::operator =(const Url &cUrl)
{
	// Save path or URL
	m_sUrl		= cUrl.m_sUrl;
	m_sProtocol	= cUrl.m_sProtocol;
	m_sRoot		= cUrl.m_sRoot;
	m_sPath		= cUrl.m_sPath;
	m_sFilename	= cUrl.m_sFilename;
	m_bValid	= cUrl.m_bValid;
	return *this;
}

/**
*  @brief
*    Copy an URL (passed as a string)
*/
Url &Url::operator =(const String &sUrl)
{
	// Save path or URL
	SetValue(sUrl);
	return *this;
}

/**
*  @brief
*    Concatenate an URL
*/
Url Url::operator +(const Url &cUrl) const
{
	// Check if the first URL is valid
	if (m_bValid) {
		// Check if the second URL is valid and can be added
		if ( cUrl.IsValid() &&														// URL must be valid
			(cUrl.GetProtocol() == GetProtocol() || cUrl.GetProtocol() == "") &&	// Protocols must match
			 cUrl.IsRelative() &&													// URL must be relative
			 IsDirectory()) {														// First URL must not have a filename
			// Compose URLs
			return Url(GetProtocol() + GetRoot() + GetPath() + cUrl.GetPath() + cUrl.GetFilename());
		}

		// Could not add second URL
		return *this;
	}

	// Error, URL is invalid
	return Url();
}

/**
*  @brief
*    Concatenate an URL
*/
Url &Url::operator +=(const Url &cUrl)
{
	// Check if the first URL is valid
	if (m_bValid) {
		// Check if the second URL is valid and can be added
		if ( cUrl.IsValid() &&														// URL must be valid
			(cUrl.GetProtocol() == GetProtocol() || cUrl.GetProtocol() == "") &&	// Protocols must match
			 cUrl.IsRelative() &&													// URL must be relative
			 IsDirectory()) {														// First URL must not have a filename
			// Compose URLs
			SetValue(GetProtocol() + GetRoot() + GetPath() + cUrl.GetPath() + cUrl.GetFilename());
		}
	}

	// Return this URL
	return *this;
}

/**
*  @brief
*    Get value in URL notation
*/
String Url::GetUrl() const
{
	return m_sUrl;
}

/**
*  @brief
*    Get value in native notation
*/
String Url::GetNativePath() const
{
	#if defined(WIN32)
		return GetWindowsPath();
	#elif defined(LINUX)
		return GetUnixPath();
	#endif
}

/**
*  @brief
*    Get value in Windows notation
*/
String Url::GetWindowsPath() const
{
	// Convert to Windows path
	if (m_sProtocol.CompareNoCase("file://") || m_sProtocol == "") {
		// Compose Windows path
		String sUrl = m_sRoot + m_sPath + m_sFilename;
		sUrl.Replace('/', '\\');
		return sUrl;
	} else {
		// Cannot convert, return URL instead
		return GetUrl();
	}
}

/**
*  @brief
*    Get value in Unix notation
*/
String Url::GetUnixPath() const
{
	// Convert to Unix path
	if (m_sProtocol.CompareNoCase("file://") || m_sProtocol == "") {
		// Compose Unix path
		return m_sRoot + m_sPath + m_sFilename;
	} else {
		// Cannot convert, return URL instead
		return GetUrl();
	}
}

/**
*  @brief
*    Returns if the URL is valid
*/
bool Url::IsValid() const
{
	// Return whether the URL is valid or not
	return m_bValid;
}

/**
*  @brief
*    Check if the URL is a valid native file path
*/
bool Url::IsValidNativePath() const
{
	#if defined(WIN32)
		return IsValidWindowsPath();
	#elif defined(LINUX)
		return IsValidUnixPath();
	#endif
}

/**
*  @brief
*    Check if the URL is valid as a Windows file path
*/
bool Url::IsValidWindowsPath() const
{
	return ((m_sProtocol.CompareNoCase("file://") || m_sProtocol == "") && (m_sRoot.GetSubstring(1, 2) == ":/" || m_sRoot == ""));
}

/**
*  @brief
*    Check if the URL is valid as a Unix file path
*/
bool Url::IsValidUnixPath() const
{
	return ((m_sProtocol.CompareNoCase("file://") || m_sProtocol == "") && (m_sRoot == "/" || m_sRoot == ""));
}

/**
*  @brief
*    Returns if the URL is empty
*/
bool Url::IsEmpty() const
{
	return (m_bValid && m_sRoot == "" && m_sPath == "" && m_sFilename == "");
}

/**
*  @brief
*    Returns if the URL is absolute
*/
bool Url::IsAbsolute() const
{
	return (m_bValid && m_sRoot != "");
}

/**
*  @brief
*    Returns if the URL is relative
*/
bool Url::IsRelative() const
{
	return (m_bValid && m_sRoot == "");
}

/**
*  @brief
*    Returns if the URL targets a directory
*/
bool Url::IsDirectory() const
{
	return (m_bValid && (m_sRoot != "" || m_sPath != "") && m_sFilename == "");
}

/**
*  @brief
*    Returns the protocol part
*/
String Url::GetProtocol() const
{
	// Return protocol part
	return m_sProtocol;
}

/**
*  @brief
*    Returns the root part
*/
String Url::GetRoot() const
{
	// Return root part
	return m_sRoot;
}

/**
*  @brief
*    Returns the path (without root and filename)
*/
String Url::GetPath() const
{
	// Return path
	return m_sPath;
}

/**
*  @brief
*    Returns the filename (including it's extension)
*/
String Url::GetFilename() const
{
	// Return filename
	return m_sFilename;
}

/**
*  @brief
*    Returns the filename without it's extension
*/
String Url::GetTitle() const
{
	const int nColon = m_sFilename.LastIndexOf(".");
	return (nColon >= 0) ? m_sFilename.GetSubstring(0, nColon) : m_sFilename;
}

/**
*  @brief
*    Returns the file extension
*/
String Url::GetExtension() const
{
	const int nColon = m_sFilename.LastIndexOf(".");
	return (nColon >= 0) ? m_sFilename.GetSubstring(nColon+1) : "";
}

/**
*  @brief
*    Returns the path without the filename
*/
String Url::CutFilename() const
{
	// Return complete path, omit protocol for local path
	String sPath;
	if (!m_sProtocol.CompareNoCase("file://") && m_sProtocol != "")
		sPath = m_sProtocol;
	sPath += m_sRoot + m_sPath;
	return sPath;
}

/**
*  @brief
*    Returns the path and filename without extension
*/
String Url::CutExtension() const
{
	// Return complete path, omit protocol for local path
	String sPath;
	if (!m_sProtocol.CompareNoCase("file://") && m_sProtocol != "")
		sPath = m_sProtocol;
	sPath += m_sRoot + m_sPath + GetTitle();
	return sPath;
}

/**
*  @brief
*    Returns the first part of the path
*/
String Url::GetFirstPath(uint32 &nPathPos) const
{
	nPathPos = 0;
	return GetNextPath(nPathPos);
}

/**
*  @brief
*    Returns the first part of the path
*/
String Url::GetFirstPath() const
{
	uint32 nPathPos = 0;
	return GetNextPath(nPathPos);
}

/**
*  @brief
*    Collapses the URL
*/
Url &Url::Collapse()
{
	// Check if the URL is valid
	if (m_bValid) {
		// Validate paths (Resolve paths like '..' and '.')
		Stack<String> cNameStack;
		uint32 nPos;
		String sName = GetFirstPath(nPos);
		while (sName != "") {
			// Check next subdir
			const String sTop = cNameStack.Top();
			if (sName.GetLength()) {
				if (sName == ".." && sTop != ".." && (sTop != "" || m_sRoot != "")) {
					// Delete last subdir when '..' occurs
					// Note: m_sRoot != "" is there because e.g. "C:\.." is a valid directory on Windows systems.
					// To avoid directory names like C:\..\..\Programme\", this function will therefore ignore
					// ".." at the beginning of a filename, but ONLY if the root is not empty (relative paths
					// can of cause begin with "..")
					if (sTop != "")
						cNameStack.Pop();
				} else if (sName == ".") {
					// Ignore '.'
				} else {
					// Push subdir on stack
					cNameStack.Push(sName);
				}
			}

			// Read next
			sName = GetNextPath(nPos);
		}

		// Look for .. or . in the filename
		const String sTop = cNameStack.Top();
		if (m_sFilename == ".." && sTop != ".." && (sTop != "" || m_sRoot != "")) {
			cNameStack.Pop();
			m_sFilename = cNameStack.Top();
			cNameStack.Pop();
		} else if (m_sFilename == ".") {
			m_sFilename = cNameStack.Top();
			if (!m_sFilename.GetLength())
				m_sFilename = ".";
			cNameStack.Pop();
		}

		// Put path together
		m_sPath = "";
		while (cNameStack.GetNumOfElements() > 0) {
			m_sPath = cNameStack.Top() + "/" + m_sPath;
			cNameStack.Pop();
		}

		// Compose new path or URL
		m_sUrl = m_sProtocol + m_sRoot + m_sPath + m_sFilename;
	}

	// Done
	return *this;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the next part of the path
*/
String Url::GetNextPath(uint32 &nPathPos) const
{
	const String sTemp = m_sPath.GetSubstring(nPathPos);
	const int nBacks = sTemp.IndexOf("\\");
	int nSlash = sTemp.IndexOf("/");
	if (nSlash < 0 || (nBacks >= 0 && nBacks < nSlash))
		nSlash = nBacks;
	if (nSlash >= 0) {
		nPathPos += nSlash + 1;
		return sTemp.GetSubstring(0, nSlash);
	} else {
		nPathPos += sTemp.GetLength();
		return "";
	}
}

/**
*  @brief
*    Sets the value of the URL
*/
void Url::SetValue(const String &sUrl)
{
	// Parse the URL according to the following regular expression:
	//   ({Name} '://')? '/'? ({Letter} (':/' | ':\'))? ({Name} ('/' | '\'))* {Name}?
	//   Where {Name} is any string without '/', '\' and ':'
	//   and   {Letter} is ['a'..'z', A'..'Z']

	// Init URL
	m_sUrl		= "";
	m_sProtocol	= "";
	m_sRoot		= "";
	m_sPath		= "";
	m_sFilename	= "";
	m_bValid	= false;

	// Check some death conditions
	if (sUrl.GetLength()) {
		// Analyze URL
		String sTemp = sUrl;

		// Check for a protocol, like "http://"
		String sProtocol;
		const int nPos = sTemp.IndexOf("://");
		if (nPos >= 2) { // the protocol name must be at least of length 2 (otherwise C:// is treated as a protocol)
			// Token "://" has been found, now check the protocol
			sProtocol = sUrl.GetSubstring(0, nPos);
			if (!IsName(sProtocol)) {
				// There are errors in the protocol string!
				return;
			}

			// Valid protocol has been found, validate ('Http://' -> 'http')
			sProtocol += "://";
			sProtocol.ToLower();
			sTemp = sTemp.GetSubstring(sProtocol.GetLength());
		}

		// Check for file root ('/')
		String sRoot;
		if (sTemp[(uint32)0] == '/' || sTemp[(uint32)0] == '\\') {
			// Root sign found
			sRoot = sTemp[(uint32)0];
			sTemp = sTemp.GetSubstring(1);
		}

		// Check for a drive letter, like C:\ or C:/
		if (IsLetter(sTemp[(uint32)0]) && sTemp[(uint32)1] == ':' && (sTemp[(uint32)2] == '/' || sTemp[(uint32)2] == '\\')) {
			// Drive letter found, validate ('c:' -> 'C:')
			sRoot = sTemp.GetSubstring(0, 1).ToUpper() + ":/";
			sTemp = sTemp.GetSubstring(3);
		}

		// Set protocol to "file://", if there is no protocol and the root is not empty
		if (sProtocol == "" && sRoot != "")
			sProtocol = "file://";

		// Check path
		String sPath, sFilename;
		while (sTemp != "") {
			// Get '/' or '\'
			const int nBacks = sTemp.IndexOf('\\');
			int nSlash = sTemp.IndexOf('/');
			if (nSlash < 0 || (nBacks >= 0 && nBacks < nSlash))
				nSlash = nBacks;

			// Check name
			const String sName = (nSlash >= 0) ? sTemp.GetSubstring(0, nSlash) : sTemp;
			if (!IsName(sName)) {
				// Error in path string found
				return;
			}

			// Compose path
			if (nSlash >= 0) {
				// Add to path
				sPath += sName + "/";
			} else {
				// Get filename
				sFilename = sTemp;
			}

			// Get next part
			if (nSlash >= 0)
				sTemp = sTemp.GetSubstring(nSlash+1);
			else
				sTemp = "";
		}

		// Last checks (Unix path with backslashes)
		if (sRoot != "/" || m_sUrl.IndexOf('\\') < 0) {
			// No errors, save result
			m_bValid	= true;
			m_sProtocol	= sProtocol;
			m_sRoot		= sRoot;
			m_sPath		= sPath;
			m_sFilename	= sFilename;
			m_sUrl		= sProtocol + sRoot + sPath + sFilename;
		}
	}
}

/**
*  @brief
*    Checks if the character is a letter (a..z, A..Z)
*/
bool Url::IsLetter(char nChar) const
{
	// Check if the character is a letter
	return ((nChar >= 'a' && nChar <= 'z') || (nChar >= 'A' && nChar <= 'Z'));
}

/**
*  @brief
*    Checks if the string is a valid name (does not contain ':', '/' or '\')
*/
bool Url::IsName(const String &sString) const
{
	// The string is not a valid name, if it is empty or if it contains ':', '/' or '\'
	return (sString.GetLength() && !sString.IsSubstring(":") && !sString.IsSubstring("/") && !sString.IsSubstring("\\"));
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral
