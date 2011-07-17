/*********************************************************\
 *  File: HID.h                                          *
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


#ifndef __PLINPUT_HID_H__
#define __PLINPUT_HID_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/Singleton.h>
#include <PLGeneral/Container/List.h>
#include "PLInput/PLInput.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLInput {
	class HIDImpl;
	class HIDDevice;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class for accessing HID (Human Interface Device) devices
*/
class HID : public PLGeneral::Singleton<HID> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLGeneral::Singleton<HID>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Detect available HID devices
		*/
		PLINPUT_API void DetectDevices();

		/**
		*  @brief
		*    Get list of available HID devices
		*
		*  @return
		*    Device list
		*/
		PLINPUT_API const PLGeneral::List<HIDDevice*> &GetDevices() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		HID();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~HID();

		/**
		*  @brief
		*    Remove all devices
		*/
		void Clear();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HIDImpl						*m_pHIDImpl;	/**< Platform specific HID implementation */
		PLGeneral::List<HIDDevice*>	 m_lstDevices;	/**< List of devices */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
namespace PLGeneral {
	PLINPUT_TEMPLATE template class PLINPUT_API Singleton<PLInput::HID>;
}


#endif // __PLINPUT_HID_H__
