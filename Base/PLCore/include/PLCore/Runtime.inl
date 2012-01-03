/*********************************************************\
 *  File: Runtime.inl                                    *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Return whether or not this is a debug version of PixelLight
*/
inline bool Runtime::IsDebugVersion()
{
	#ifdef _DEBUG
		// The executable is using a debug version of PixelLight
		return true;
	#else
		// The executable is using a release version of PixelLight
		return false;
	#endif
}

/**
*  @brief
*    Try to find the local PixelLight runtime directory
*/
inline String Runtime::GetLocalDirectory()
{
	// Try to find the PixelLight runtime directory by using the PLCore shared library
	return GetDirectory(LocalInstallation);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
