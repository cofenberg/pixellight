/*********************************************************\
 *  File: FileInterfacePL.h                              *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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