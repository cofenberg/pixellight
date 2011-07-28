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


#ifndef __LIBROCKET_PL_FILEINTERFACE_H__
#define __LIBROCKET_PL_FILEINTERFACE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Rocket/Core/FileInterface.h>
#include "libRocket_PL/libRocket_PL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace libRocket_PL {


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
		LIBROCKET_PL_API FileInterfacePL();

		/**
		*  @brief
		*    Destructor
		*/
		LIBROCKET_PL_API virtual ~FileInterfacePL();


	//[-------------------------------------------------------]
	//[ Public virtual Rocket::Core::FileInterface functions  ]
	//[-------------------------------------------------------]
	public:
		LIBROCKET_PL_API virtual Rocket::Core::FileHandle Open(const Rocket::Core::String& path) override;
		LIBROCKET_PL_API virtual void Close(Rocket::Core::FileHandle file) override;
		LIBROCKET_PL_API virtual size_t Read(void* buffer, size_t size, Rocket::Core::FileHandle file) override;
		LIBROCKET_PL_API virtual bool Seek(Rocket::Core::FileHandle file, long offset, int origin) override;
		LIBROCKET_PL_API virtual size_t Tell(Rocket::Core::FileHandle file) override;


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
} // libRocket_PL


#endif // __LIBROCKET_PL_FILEINTERFACE_H__