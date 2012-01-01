/*********************************************************\
 *  File: Singleton.inl                                  *
 *      Singleton template implementation
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
//[ Debugging options for Microsoft Visual Studio         ]
//[-------------------------------------------------------]
// <<nostepinto>> PLCore::Singleton::.*


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Static data                                           ]
//[-------------------------------------------------------]
template <class AType> typename Singleton<AType>::__Destruction_Guard Singleton<AType>::__Guard;
template <class AType> AType *Singleton<AType>::__Instance  = nullptr;
template <class AType> bool   Singleton<AType>::__Destroyed = false;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the class instance
*/
template <class AType> AType *Singleton<AType>::GetInstance()
{
	// [HACK] This is neccessary for the compiler to instanciate __Guard
	__Guard.init();

	// Check if the instance must be created
	if (!__Instance && !__Destroyed) {
		// Create instance
		return new AType();
	} else {
		// Return instance
		return __Instance;
	}
}

/**
*  @brief
*    Returns whether or not there's an instance
*/
template <class AType> bool Singleton<AType>::HasInstance()
{
	return (__Instance != nullptr);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class AType> Singleton<AType>::Singleton()
{
	// Register instance - Don't use reinterpret_cast in here or hell breaks loose when starting programs
	__Instance = static_cast<AType*>(this);
}

/**
*  @brief
*    Destructor
*/
template <class AType> Singleton<AType>::~Singleton()
{
	// Unregister instance
	if (__Instance == this) {
		__Instance  = nullptr;
		__Destroyed = true;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
