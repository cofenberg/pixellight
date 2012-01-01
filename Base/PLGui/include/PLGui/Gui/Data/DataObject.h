/*********************************************************\
 *  File: DataObject.h                                   *
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


#ifndef __PLGUI_DATAOBJECT_H__
#define __PLGUI_DATAOBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include <PLCore/Container/Array.h>
#include "PLGui/PLGui.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Represents a data object, use e.g. for the clipboard and drag&drop events
*/
class DataObject {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLGUI_API DataObject();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sString
		*    String
		*/
		PLGUI_API DataObject(const PLCore::String &sString);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] lstFiles
		*    List of file names
		*/
		PLGUI_API DataObject(const PLCore::Container<PLCore::String> &lstFiles);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nValue
		*    Data value
		*/
		PLGUI_API DataObject(PLCore::uint32 nValue);

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pData
		*    Data buffer
		*  @param[in] nSize
		*    Size of data buffer
		*/
		PLGUI_API DataObject(PLCore::uint8 *pData, PLCore::uint32 nSize);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cOther
		*    Data object
		*/
		PLGUI_API DataObject(const DataObject &cOther);

		/**
		*  @brief
		*    Destructor
		*/
		PLGUI_API ~DataObject();

		/**
		*  @brief
		*    Comparison operator
		*
		*  @param[in] cOther
		*    Data object
		*
		*  @return
		*    'true' if equal, else 'false'
		*/
		PLGUI_API bool operator ==(const DataObject &cOther) const;

		/**
		*  @brief
		*    Assignment operator
		*
		*  @param[in] cOther
		*    Data object
		*
		*  @return
		*    Reference to this object
		*/
		PLGUI_API DataObject &operator =(const DataObject &cOther);

		/**
		*  @brief
		*    Get data type
		*
		*  @return
		*    Data type
		*/
		PLGUI_API EDataType GetType() const;

		/**
		*  @brief
		*    Get string data
		*
		*  @return
		*    String, empty string if data type is other than DataString
		*/
		PLGUI_API PLCore::String GetString() const;

		/**
		*  @brief
		*    Set string data
		*
		*  @param[in] sString
		*    String
		*/
		PLGUI_API void Set(const PLCore::String &sString);

		/**
		*  @brief
		*    Get file names
		*
		*  @return
		*    List of file names, empty list if data type is other than DataFiles
		*/
		PLGUI_API const PLCore::Container<PLCore::String> &GetFiles() const;

		/**
		*  @brief
		*    Set file names
		*
		*  @param[in] lstFiles
		*    List of file names
		*/
		PLGUI_API void Set(const PLCore::Container<PLCore::String> &lstFiles);

		/**
		*  @brief
		*    Get custom data
		*
		*  @return
		*    Data value, 0 if data type is other than DataCustom
		*/
		PLGUI_API PLCore::uint32 GetValue() const;

		/**
		*  @brief
		*    Set custom data
		*
		*  @param[in] nValue
		*    Data value
		*/
		PLGUI_API void Set(PLCore::uint32 nValue);

		/**
		*  @brief
		*    Get binary data size
		*
		*  @return
		*    Size of custom data, 0 if data type is other than DataBinary
		*/
		PLGUI_API PLCore::uint32 GetBinarySize() const;

		/**
		*  @brief
		*    Get binary data
		*
		*  @return
		*    Data pointer, a null pointer if data type is other than DataBinary
		*/
		PLGUI_API PLCore::uint8 *GetBinaryData() const;

		/**
		*  @brief
		*    Set binary data
		*
		*  @param[in] pData
		*    Data buffer
		*  @param[in] nSize
		*    Size of data buffer
		*
		*  @remarks
		*    A new buffer of the given size will be allocated and the data will be copied to that buffer.
		*    The class takes care of deleting the allocated memory later.
		*/
		PLGUI_API void Set(PLCore::uint8 *pData, PLCore::uint32 nSize);

		/**
		*  @brief
		*    Clear data
		*/
		PLGUI_API void Clear();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		EDataType						 m_nDataType;	/**< Data type */
		PLCore::String					 m_sString;		/**< String data */
		PLCore::Array<PLCore::String>	 m_lstFiles;	/**< List of file names */
		PLCore::uint32					 m_nValue;		/**< Custom data */
		PLCore::uint8					*m_pData;		/**< Binary data buffer */
		PLCore::uint32					 m_nDataSize;	/**< Binary data buffer size */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_DATAOBJECT_H__
