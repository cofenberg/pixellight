/*********************************************************\
 *  File: IOStream.h                                     *
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


#ifndef __PLASSIMP_IOSTREAM_H__
#define __PLASSIMP_IOSTREAM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Assimp/IOStream.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class File;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLAssimp {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Assimp IO stream implementation
*/
class IOStream : public Assimp::IOStream {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class IOSystem;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~IOStream();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to load from, must be opened and readable
		*  @param[in] bTakeOver
		*    Take over the control of the file object?
		*/
		IOStream(PLCore::File &cFile, bool bTakeOver);


	//[-------------------------------------------------------]
	//[ Public virtual Assimp::IOStream functions             ]
	//[-------------------------------------------------------]
	public:
		virtual size_t Read(void *pvBuffer, size_t pSize, size_t pCount);
		virtual size_t Write(const void *pvBuffer, size_t pSize, size_t pCount);
		virtual aiReturn Seek(size_t pOffset, aiOrigin pOrigin);
		virtual size_t Tell() const;
		virtual size_t FileSize() const;
		virtual void Flush();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Default constructor
		*/
		IOStream();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		IOStream(const IOStream &cSource);

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
		IOStream &operator =(const IOStream &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::File *m_pFile;		/**< File to load from, must be always valid, opened and readable */
		bool		  m_bTakeOver;	/**< Take over the control of the file object? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp


#endif // __PLASSIMP_IOSTREAM_H__
