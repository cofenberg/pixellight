/*********************************************************\
 *  File: IOSystem.h                                     *
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


#ifndef __PLASSIMP_IOSYSTEM_H__
#define __PLASSIMP_IOSYSTEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Assimp/IOSystem.h>


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
*    Assimp IO system implementation
*/
class IOSystem : public Assimp::IOSystem {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		static const char *MagicDefaultFilename;		/**< Magic filename (concept based on "Assimp::MemoryIOSystem") */
		static const int   MagicDefaultFilenameLength;	/**< Length of the magic filename */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cFile
		*    File to load from, must be opened and readable
		*  @param[in] pszMagicDefaultFilename
		*    Magic filename (concept based on "Assimp::MemoryIOSystem")
		*  @param[in] nMagicDefaultFilenameLength
		*    Length of the magic filename
		*/
		IOSystem(PLCore::File &cFile, const char *pszMagicDefaultFilename, int nMagicDefaultFilenameLength);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~IOSystem();


	//[-------------------------------------------------------]
	//[ Public virtual Assimp::IOSystem functions             ]
	//[-------------------------------------------------------]
	public:
		virtual bool Exists(const char *pFile) const;
		virtual char getOsSeparator() const;
		virtual Assimp::IOStream *Open(const char *pFile, const char *pMode = "rb");
		virtual void Close(Assimp::IOStream *pFile);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Default constructor
		*/
		IOSystem();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		IOSystem(const IOSystem &cSource);

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
		IOSystem &operator =(const IOSystem &cSource);

		/**
		*  @brief
		*    Returns a real filename
		*
		*  @param[in] pFile
		*    Filename as given by Assimp
		*
		*  @return
		*    The constructed real filename (... and hopefully a correct one...)
		*/
		PLCore::String GetRealFilename(const char *pszAssimpFile) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::File *m_pFile;							/**< File to load from, must be always valid, opened and readable (just shared, not closed or even destroyed in here) */
		const char   *m_pszMagicDefaultFilename;		/**< Magic filename (concept based on "Assimp::MemoryIOSystem") - just shared, do not destroy it */
		const int     m_nMagicDefaultFilenameLength;	/**< Length of the magic filename */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp


#endif // __PLASSIMP_IOSYSTEM_H__
