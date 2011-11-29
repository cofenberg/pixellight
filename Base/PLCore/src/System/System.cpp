/*********************************************************\
 *  File: System.cpp                                     *
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
#include "PLCore/System/Thread.h"
#if defined(WIN32)
	#include "PLCore/System/SystemWindows.h"
#elif defined(ANDROID)
	#include "PLCore/System/SystemAndroid.h"
#elif defined(APPLE)
	#include "PLCore/System/SystemMacOSX.h"
#elif defined(LINUX)
	#include "PLCore/System/SystemLinux.h"
#endif
#include "PLCore/System/System.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
template class Singleton<System>;


//[-------------------------------------------------------]
//[ Public static PLCore::Singleton functions             ]
//[-------------------------------------------------------]
System *System::GetInstance()
{
	// The compiler should be able to optimize this extra call (inlining)
	return Singleton<System>::GetInstance();
}

bool System::HasInstance()
{
	// The compiler should be able to optimize this extra call (inlining)
	return Singleton<System>::HasInstance();
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns an information string about the system
*/
String System::GetInfo() const
{
	static const String sString = String("PLCore library") +
								  "\nEndian: "			+ (IsLittleEndian() ? "'Little Endian First'" : "'Big Endian First'") +
								  "\nPlatform: "		+ GetPlatform() + ' ' + GetPlatformBitArchitecture() + " bit (" + GetPlatformArchitecture() + ')' +
								  "\nOS: "				+ GetOS() +
								  '\n';
	return sString;
}

/**
*  @brief
*    Detects the current machine's endian ("byte order")
*/
bool System::IsLittleEndian() const
{
	union Probe {
		unsigned int  nNumber;
		unsigned char nBytes[sizeof(unsigned int)];
	};

	// Initialize the first member of p with unsigned 1
	Probe p = { 1u };

	// In a big endian architecture, p.nBytes[0] equals 0
	return (p.nBytes[0] == 1u);
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
System::System() :
	m_pSystemImpl(nullptr),
	m_pMainThread(nullptr)
{
	// Create system implementation for the right platform
	#if defined(WIN32)
		// Create Windows implementation
		m_pSystemImpl = new SystemWindows();
	#elif defined(ANDROID)
		// Create Android implementation
		m_pSystemImpl = new SystemAndroid();
	#elif defined(APPLE)
		// Create Mac OS X implementation
		m_pSystemImpl = new SystemMacOSX();
	#elif defined(LINUX)
		// Create Linux implementation
		m_pSystemImpl = new SystemLinux();
	#else
		// Unknown system
		#error "Unsupported platform"
	#endif

	// Create main thread object (NULL_HANDLE for current thread)
	m_pMainThread = new Thread(NULL_HANDLE);
}

/**
*  @brief
*    Copy constructor
*/
System::System(const System &cSource) :
	m_pSystemImpl(nullptr),
	m_pMainThread(nullptr)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Destructor
*/
System::~System()
{
	// Destroy main thread object
	delete m_pMainThread;

	// Destroy system specific implementation
	if (m_pSystemImpl)
		delete m_pSystemImpl;
}

/**
*  @brief
*    Copy operator
*/
System &System::operator =(const System &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
