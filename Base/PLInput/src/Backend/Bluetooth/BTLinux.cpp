/*********************************************************\
 *  File: BTLinux.cpp                                    *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <stdlib.h>
#include <dbus/dbus.h>
#include <PLCore/String/ParseTools.h>
#include <PLCore/Log/Log.h>
#include "PLInput/Backend/Bluetooth/BTLinux.h"
#include "PLInput/Backend/Bluetooth/BTDeviceLinux.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
static const int TIMEOUT = 10;		/**< Timeout for detecting devices */


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BTLinux::BTLinux()
{
}

/**
*  @brief
*    Destructor
*/
BTLinux::~BTLinux()
{
	// Clear devices
	for (uint32 i=0; i<m_lstDevices.GetNumOfElements(); i++)
		delete m_lstDevices[i];
	m_lstDevices.Clear();
}

void BTLinux::EnumerateBluetoothDevices(List<BTDevice*> &lstDevices, DBusConnection *pConnection)
{
	// Initialize error value
	DBusError sError;
	dbus_error_init(&sError);
	
	DBusMessage *pMessage;
	
	// Listen to signals from org.bluez.Adapter
	dbus_bus_add_match(pConnection, "type='signal',interface='org.bluez.Adapter'", &sError);
	dbus_connection_flush(pConnection);
	if (!dbus_error_is_set(&sError)) {
		// Listen for signals
		bool bAbort = false;
		while (!bAbort) {
			// Read next message
			dbus_connection_read_write(pConnection, 0);
			pMessage = dbus_connection_pop_message(pConnection);
			if (pMessage) {
				// Check signal
				if (dbus_message_is_signal(pMessage, "org.bluez.Adapter", "DeviceFound")) {
					// org.bluez.Adapter.DeviceFound
					String sDeviceAddress;
					String sDeviceName;
					uint32 nDeviceClass = 0;

					// Get arguments
					DBusMessageIter sIter;
					dbus_message_iter_init(pMessage, &sIter);
					int nType = 0;
					while ((nType = dbus_message_iter_get_arg_type(&sIter)) != DBUS_TYPE_INVALID) {
						// Check argument type
						if (nType == DBUS_TYPE_STRING) {
							// Device address
							char *pszAddress = nullptr;
							dbus_message_iter_get_basic(&sIter, &pszAddress);
							if (pszAddress) {
								sDeviceAddress = pszAddress;
							}
						} else if (nType == DBUS_TYPE_ARRAY) {
							// Get device infos
							DBusMessageIter sArrayIter;
							for (dbus_message_iter_recurse(&sIter, &sArrayIter);
									dbus_message_iter_get_arg_type(&sArrayIter) != DBUS_TYPE_INVALID;
									dbus_message_iter_next(&sArrayIter))
							{
								// Dictionary entry
								if (dbus_message_iter_get_arg_type(&sArrayIter) == DBUS_TYPE_DICT_ENTRY) {
									// Get values
									DBusMessageIter sDictIter;
									dbus_message_iter_recurse (&sArrayIter, &sDictIter);
									if (dbus_message_iter_get_arg_type(&sDictIter) == DBUS_TYPE_STRING) {
										// Get name
										char *pszName;
										dbus_message_iter_get_basic(&sDictIter, &pszName);
										String sName = pszName;

										// Next
										dbus_message_iter_next(&sDictIter);
										if (dbus_message_iter_get_arg_type(&sDictIter) == DBUS_TYPE_VARIANT) {
											DBusMessageIter sVariantIter;
											dbus_message_iter_recurse(&sDictIter, &sVariantIter);
											if (dbus_message_iter_get_arg_type(&sVariantIter) == DBUS_TYPE_STRING) {
												// Get value
												char *pszValue = nullptr;
												dbus_message_iter_get_basic(&sVariantIter, &pszValue);

												// Save value
												if (sName == "Name" && pszValue) {
													// Device name
													sDeviceName = pszValue;
												}
											} else if (dbus_message_iter_get_arg_type(&sVariantIter) == DBUS_TYPE_UINT32) {
												// Get value
												uint32 nValue = 0;
												dbus_message_iter_get_basic(&sVariantIter, &nValue);

												// Save value
												if (sName == "Class") {
													nDeviceClass = nValue;
												}
											}
										}
									}
								}
							}

						}
						dbus_message_iter_next(&sIter);
					}

					// Device info
					PL_LOG(Info, "BTLinux: Found device '" + sDeviceName + "', Address = " + sDeviceAddress)

					// Convert address from string to bytes
					int nAddress0 = ParseTools::ParseHexValue(sDeviceAddress.GetSubstring( 0, 2));
					int nAddress1 = ParseTools::ParseHexValue(sDeviceAddress.GetSubstring( 3, 2));
					int nAddress2 = ParseTools::ParseHexValue(sDeviceAddress.GetSubstring( 6, 2));
					int nAddress3 = ParseTools::ParseHexValue(sDeviceAddress.GetSubstring( 9, 2));
					int nAddress4 = ParseTools::ParseHexValue(sDeviceAddress.GetSubstring(12, 2));
					int nAddress5 = ParseTools::ParseHexValue(sDeviceAddress.GetSubstring(15, 2));

					// Set device info
					BTDeviceLinux *pDevice = new BTDeviceLinux();
					pDevice->m_sName = sDeviceName;
					pDevice->m_nAddress[0] = nAddress5;
					pDevice->m_nAddress[1] = nAddress4;
					pDevice->m_nAddress[2] = nAddress3;
					pDevice->m_nAddress[3] = nAddress2;
					pDevice->m_nAddress[4] = nAddress1;
					pDevice->m_nAddress[5] = nAddress0;
					pDevice->m_nAddress[6] = 0;
					pDevice->m_nAddress[7] = 0;
					pDevice->m_nClass[0] = (nDeviceClass >>  0) & 255;
					pDevice->m_nClass[1] = (nDeviceClass >>  8) & 255;
					pDevice->m_nClass[2] = (nDeviceClass >> 16) & 255;

					// Add device
					m_lstDevices.Add(pDevice);
						lstDevices.Add(pDevice);

					// Device found, not stop
					bAbort = true;
				} else if (dbus_message_is_signal(pMessage, "org.bluez.Adapter", "PropertyChanged")) {
					// org.bluez.Adapter.PropertyChanged
					DBusMessageIter sIter;
					dbus_message_iter_init(pMessage, &sIter);
					if (dbus_message_iter_get_arg_type(&sIter) == DBUS_TYPE_STRING) {
						// Get name
						char *pszName;
						dbus_message_iter_get_basic(&sIter, &pszName);
						String sName = pszName;

						// 'Discovering'
						if (sName == "Discovering") {
							// Get value
							dbus_message_iter_next(&sIter);
							if (dbus_message_iter_get_arg_type(&sIter) == DBUS_TYPE_VARIANT) {
								// Get variant
								DBusMessageIter sVariantIter;
								dbus_message_iter_recurse(&sIter, &sVariantIter);
								if (dbus_message_iter_get_arg_type(&sVariantIter) == DBUS_TYPE_BOOLEAN) {
									// Get device discovery state
									bool bState = false;
									dbus_message_iter_get_basic(&sVariantIter, &bState);

									// Stop loop when Discovering=false
									if (!bState) bAbort = true;
								}
							}
						}
					}
				}

				// Release message
				dbus_message_unref(pMessage);
			}
		}
	} else {
		PL_LOG(Error, "BTLinux: DBUS match error (" + String(sError.message) + ')')
	}
	
	// DeInitialize error value
	dbus_error_free(&sError);
}


//[-------------------------------------------------------]
//[ Private virtual BTImpl functions                      ]
//[-------------------------------------------------------]
void BTLinux::EnumerateDevices(List<BTDevice*> &lstDevices)
{
	// Clear devices
	for (uint32 i=0; i<m_lstDevices.GetNumOfElements(); i++)
		delete m_lstDevices[i];
	m_lstDevices.Clear();

	// Initialize DBUS
//	dbus_threads_init_default();

	// Initialize error value
	DBusError sError;
	dbus_error_init(&sError);

	// Get DBUS connection
	PL_LOG(Info, "BTLinux: Discovering Bluetooth devices")
	DBusConnection *pConnection = dbus_bus_get(DBUS_BUS_SYSTEM, &sError);
	if (pConnection) {
		// Get default Bluetooth adapter
		DBusMessage *pMessage = dbus_message_new_method_call("org.bluez", "/", "org.bluez.Manager", "DefaultAdapter");
		DBusMessage *pReply = dbus_connection_send_with_reply_and_block(pConnection, pMessage, -1, &sError);
		dbus_message_unref(pMessage);
		if (pReply) {
			// Get adapter name
			const char *pszAdapter = nullptr;
			dbus_message_get_args(pReply, &sError, DBUS_TYPE_OBJECT_PATH, &pszAdapter, DBUS_TYPE_INVALID);
			String sAdapter = pszAdapter;
			dbus_message_unref(pReply);

			// Set timeout for device discovery
			const char *pszTimeout = "DiscoverableTimeout";
			int nTimeout = TIMEOUT;
			pMessage = dbus_message_new_method_call("org.bluez", sAdapter.GetASCII(), "org.bluez.Adapter", "SetProperty");
			DBusMessageIter sIter;
			DBusMessageIter sVariantIter;
			dbus_message_iter_init_append(pMessage, &sIter);
			dbus_message_iter_append_basic(&sIter, DBUS_TYPE_STRING, &pszTimeout);
			dbus_message_iter_open_container(&sIter, DBUS_TYPE_VARIANT, DBUS_TYPE_UINT32_AS_STRING, &sVariantIter);
			dbus_message_iter_append_basic(&sVariantIter, DBUS_TYPE_UINT32, &nTimeout);
			dbus_message_iter_close_container(&sIter, &sVariantIter);
			pReply = dbus_connection_send_with_reply_and_block(pConnection, pMessage, -1, &sError);
			if (pReply)   dbus_message_unref(pReply);
			if (pMessage) dbus_message_unref(pMessage);
			
			if(!dbus_error_is_set(&sError)) {
				// Start device discovery
				pMessage = dbus_message_new_method_call("org.bluez", sAdapter.GetASCII(), "org.bluez.Adapter", "StartDiscovery");
				pReply = dbus_connection_send_with_reply_and_block(pConnection, pMessage, -1, &sError);
				if (pReply)   dbus_message_unref(pReply);
				if (pMessage) dbus_message_unref(pMessage);

				if(!dbus_error_is_set(&sError))
					EnumerateBluetoothDevices(lstDevices, pConnection);
				else
					PL_LOG(Error, "BTLinux (Start device discovery): DBUS error (" + String(sError.message) + ')')
			} else {
				PL_LOG(Error, "BTLinux (Set timeout for device discovery): DBUS error (" + String(sError.message) + ')')
			}
		}

		// Close connection
		dbus_error_free(&sError);
		dbus_connection_unref(pConnection);
	} else {
		PL_LOG(Error, "BTLinux: Could not create DBUS connection")
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput

