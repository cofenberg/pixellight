/*********************************************************\
 *  File: HIDWindows.h                                   *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLINPUT_HID_WINDOWS_H__
#define __PLINPUT_HID_WINDOWS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Backend/HID/HIDImpl.h"
#include "PLInput/PLInputWindowsIncludes.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class DynLib;
}
namespace PLInput {
	class HIDDeviceWindows;
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
*    Windows implementation of 'HIDImpl'
*/
class HIDWindows : public HIDImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class HID;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		HIDWindows();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~HIDWindows();


	//[-------------------------------------------------------]
	//[ Private virtual HIDImpl functions                     ]
	//[-------------------------------------------------------]
	private:
		virtual void EnumerateDevices(PLGeneral::List<HIDDevice*> &lstDevices);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::DynLib				   *m_pDynLibHID;	/**< Dynamic HID library, always valid! */
		PLGeneral::List<HIDDeviceWindows*>	m_lstDevices;	/**< List of devices */
		GUID								m_sGUID;		/**< HID device interface GUID */




};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_HID_WINDOWS_H__
