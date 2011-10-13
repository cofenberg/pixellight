/*********************************************************\
 *  File: Bluetooth.h                                    *
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


#ifndef __PLINPUT_BLUETOOTH_H__
#define __PLINPUT_BLUETOOTH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Core/Singleton.h>
#include <PLCore/Container/List.h>
#include "PLInput/PLInput.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLInput {
	class BTImpl;
	class BTDevice;
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
*    Class for accessing Bluetooth devices
*/
class Bluetooth : public PLCore::Singleton<Bluetooth> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLCore::Singleton<Bluetooth>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Detect available Bluetooth devices
		*/
		PLINPUT_API void DetectDevices();

		/**
		*  @brief
		*    Get list of available Bluetooth devices
		*
		*  @return
		*    Device list
		*/
		PLINPUT_API const PLCore::List<BTDevice*> &GetDevices() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		Bluetooth();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Bluetooth();

		/**
		*  @brief
		*    Remove all devices
		*/
		void Clear();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		BTImpl					*m_pBTImpl;		/**< Platform specific Bluetooth implementation */
		PLCore::List<BTDevice*>	 m_lstDevices;	/**< List of devices */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


//[-------------------------------------------------------]
//[ Template extern instance                              ]
//[-------------------------------------------------------]
#ifndef PLINPUT_BLUETOOTH_CPP
	namespace PLCore {
		PLINPUT_EXTERN_TEMPLATE Singleton<PLInput::Bluetooth>;
	}
#endif


#endif // __PLINPUT_BLUETOOTH_H__
