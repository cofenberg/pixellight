/*********************************************************\
 *  File: FileInterfacePL.h                              *
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


#ifndef __PLLIBROCKET_FILEINTERFACE_H__
#define __PLLIBROCKET_FILEINTERFACE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Rocket/Core/FileInterface.h>
#include "PLlibRocket/PLlibRocket.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLlibRocket {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A file interface for Rocket into PixelLight
*/
class FileInterfacePL : public Rocket::Core::FileInterface {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLLIBROCKET_API FileInterfacePL();

		/**
		*  @brief
		*    Destructor
		*/
		PLLIBROCKET_API virtual ~FileInterfacePL();


	//[-------------------------------------------------------]
	//[ Public virtual Rocket::Core::FileInterface functions  ]
	//[-------------------------------------------------------]
	public:
		PLLIBROCKET_API virtual Rocket::Core::FileHandle Open(const Rocket::Core::String& path) override;
		PLLIBROCKET_API virtual void Close(Rocket::Core::FileHandle file) override;
		PLLIBROCKET_API virtual size_t Read(void* buffer, size_t size, Rocket::Core::FileHandle file) override;
		PLLIBROCKET_API virtual bool Seek(Rocket::Core::FileHandle file, long offset, int origin) override;
		PLLIBROCKET_API virtual size_t Tell(Rocket::Core::FileHandle file) override;


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
		FileInterfacePL(const FileInterfacePL &cSource);

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
		FileInterfacePL &operator =(const FileInterfacePL &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLlibRocket


#endif // __PLLIBROCKET_FILEINTERFACE_H__