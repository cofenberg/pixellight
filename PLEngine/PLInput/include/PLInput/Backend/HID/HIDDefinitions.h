/*********************************************************\
 *  File: HIDDefinitions.h                               *
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


#ifndef __PLINPUT_HIDDEFINITIONS_H__
#define __PLINPUT_HIDDEFINITIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
// Usage Page: Generic (e.g. Values, Axes)
static const int UsagePageGeneric	= 0x01;
	static const int UsageJoystick				= 0x04;
	static const int UsageGamepad				= 0x05;
	static const int UsageMultiAxisController	= 0x08;
	static const int UsageX						= 0x30;
	static const int UsageY						= 0x31;
	static const int UsageZ						= 0x32;
	static const int UsageRX					= 0x33;
	static const int UsageRY					= 0x34;
	static const int UsageRZ					= 0x35;
	static const int UsageSlider				= 0x36;
	static const int UsageDial					= 0x37;
	static const int UsageWheel					= 0x38;
	static const int UsageHat					= 0x39;


// Usage Page: Buttons
static const int UsagePageButtons	= 0x09;
	static const int UsageNoButton				= 0x00;
	static const int UsageButton1				= 0x01;
	static const int UsageButton2				= 0x02;
	static const int UsageButton3				= 0x03;
	static const int UsageButton4				= 0x04;
	static const int UsageButton5				= 0x05;
	static const int UsageButton6				= 0x06;
	static const int UsageButton7				= 0x07;
	static const int UsageButton8				= 0x08;


// Usage Page: LED (used for rumble on my gamepad)
static const int UsagePageLED		= 0x08;
	static const int UsageSlowBlinkOnTime		= 0x43;
	static const int UsageSlowBlinkOffTime		= 0x44;
	static const int UsageFastBlinkOnTime		= 0x45;
	static const int UsageFastBlinkOffTime		= 0x46;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_HIDDEFINITIONS_H__
