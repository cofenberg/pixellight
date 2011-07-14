/*********************************************************\
 *  File: Keys.h                                         *
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


#ifndef __PLGUI_KEYS_H__
#define __PLGUI_KEYS_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGui {


//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
#ifdef WIN32

//           Virtual code            Hex Value      Key
#define		 PLGUIMOD_ALT				0x0001		/**< alt */
#define		 PLGUIMOD_CONTROL			0x0002		/**< control */
#define		 PLGUIMOD_ALTGR				0x0003		/**< alt-gr */
#define		 PLGUIMOD_SHIFT				0x0004		/**< shift */
#define		 PLGUIMOD_WIN				0x0008		/**< Windows key */

#define 	 PLGUIKEY_LBUTTON			0x01		/**< left mouse button */
#define 	 PLGUIKEY_RBUTTON			0x02		/**< right mouse button */
#define 	 PLGUIKEY_CANCEL			0x03		/**< control-break processing */
#define 	 PLGUIKEY_MBUTTON			0x04		/**< middle mouse button (three-button mouse) */

#define 	 PLGUIKEY_BACK				0x08		/**< backspace */
#define 	 PLGUIKEY_TAB				0x09		/**< tab */

#define 	 PLGUIKEY_CLEAR				0x0C		/**< clear */
#define 	 PLGUIKEY_RETURN			0x0D		/**< enter */

#define 	 PLGUIKEY_SHIFT				0x10		/**< shift */
#define 	 PLGUIKEY_CONTROL			0x11		/**< ctrl */
#define 	 PLGUIKEY_MENU				0x12		/**< alt */
#define 	 PLGUIKEY_PAUSE				0x13		/**< pause */
#define 	 PLGUIKEY_CAPITAL			0x14		/**< caps lock */

#define 	 PLGUIKEY_ESCAPE			0x1B		/**< esc */
#define 	 PLGUIKEY_SPACE				0x20		/**< spacebar */
#define 	 PLGUIKEY_PRIOR				0x21		/**< page up */
#define 	 PLGUIKEY_NEXT				0x22		/**< page down */
#define 	 PLGUIKEY_END				0x23		/**< end key */
#define 	 PLGUIKEY_HOME				0x24		/**< home key */
#define 	 PLGUIKEY_LEFT				0x25		/**< left arrow */
#define 	 PLGUIKEY_UP				0x26		/**< up arrow */
#define 	 PLGUIKEY_RIGHT				0x27		/**< right arrow */
#define 	 PLGUIKEY_DOWN				0x28		/**< down arrow */
#define 	 PLGUIKEY_SELECT			0x29		/**< select key */

#define 	 PLGUIKEY_EXECUTE			0x2B		/**< execute key */
#define 	 PLGUIKEY_SNAPSHOT			0x2C		/**< print screen key */
#define 	 PLGUIKEY_INSERT			0x2D		/**< insert key */
#define 	 PLGUIKEY_DELETE			0x2E		/**< delete key */
#define 	 PLGUIKEY_HELP				0x2F		/**< help key */
#define 	 PLGUIKEY_0					0x30		/**< 0 */
#define 	 PLGUIKEY_1					0x31		/**< 1 */
#define 	 PLGUIKEY_2					0x32		/**< 2 */
#define 	 PLGUIKEY_3					0x33		/**< 3 */
#define 	 PLGUIKEY_4					0x34		/**< 4 */
#define 	 PLGUIKEY_5					0x35		/**< 5 */
#define 	 PLGUIKEY_6					0x36		/**< 6 */
#define 	 PLGUIKEY_7					0x37		/**< 7 */
#define 	 PLGUIKEY_8					0x38		/**< 8 */
#define 	 PLGUIKEY_9					0x39		/**< 9 */
											
#define 	 PLGUIKEY_A					0x41		/**< a */
#define 	 PLGUIKEY_B					0x42		/**< b */
#define 	 PLGUIKEY_C					0x43		/**< c */
#define 	 PLGUIKEY_D					0x44		/**< d */
#define 	 PLGUIKEY_E					0x45		/**< e */
#define 	 PLGUIKEY_F					0x46		/**< f */
#define 	 PLGUIKEY_G					0x47		/**< g */
#define 	 PLGUIKEY_H					0x48		/**< h */
#define 	 PLGUIKEY_I					0x49		/**< i */
#define 	 PLGUIKEY_J					0x4A		/**< j */
#define 	 PLGUIKEY_K					0x4B		/**< k */
#define 	 PLGUIKEY_L					0x4C		/**< l */
#define 	 PLGUIKEY_M					0x4D		/**< m */
#define 	 PLGUIKEY_N					0x4E		/**< n */
#define		 PLGUIKEY_O					0x4F		/**< o */
#define 	 PLGUIKEY_P					0x50		/**< p */
#define		 PLGUIKEY_Q					0x51		/**< q */
#define 	 PLGUIKEY_R					0x52		/**< r */
#define 	 PLGUIKEY_S					0x53		/**< s */
#define 	 PLGUIKEY_T					0x54		/**< t */
#define 	 PLGUIKEY_U					0x55		/**< u */
#define 	 PLGUIKEY_V					0x56		/**< v */
#define 	 PLGUIKEY_W					0x57		/**< w */
#define 	 PLGUIKEY_X					0x58		/**< x */
#define 	 PLGUIKEY_Y					0x59		/**< y */
#define 	 PLGUIKEY_Z					0x5A		/**< z */
#define  	 PLGUIKEY_NUMPAD0			0x60		/**< Numeric keypad 0 key */
#define 	 PLGUIKEY_NUMPAD1			0x61		/**< Numeric keypad 1 key */
#define 	 PLGUIKEY_NUMPAD2			0x62		/**< Numeric keypad 2 key */
#define 	 PLGUIKEY_NUMPAD3			0x63		/**< Numeric keypad 3 key */
#define 	 PLGUIKEY_NUMPAD4			0x64		/**< Numeric keypad 4 key */
#define 	 PLGUIKEY_NUMPAD5			0x65		/**< Numeric keypad 5 key */
#define 	 PLGUIKEY_NUMPAD6			0x66		/**< Numeric keypad 6 key */
#define 	 PLGUIKEY_NUMPAD7			0x67		/**< Numeric keypad 7 key */
#define 	 PLGUIKEY_NUMPAD8			0x68		/**< Numeric keypad 8 key */
#define 	 PLGUIKEY_NUMPAD9			0x69		/**< Numeric keypad 9 key */
#define 	 PLGUIKEY_MULTIPLY			0x6A		/**< Multiply key */
#define 	 PLGUIKEY_ADD				0x6B		/**< Add key */
#define 	 PLGUIKEY_SEPARATOR			0x6C		/**< Separator key */
#define 	 PLGUIKEY_SUBTRACT			0x6D		/**< Subtract key */
#define 	 PLGUIKEY_DECIMAL			0x6E		/**< Decimal key */
#define 	 PLGUIKEY_DIVIDE			0x6F		/**< Divide key */
#define 	 PLGUIKEY_F1				0x70		/**< f1 key */
#define 	 PLGUIKEY_F2				0x71		/**< f2 key */
#define 	 PLGUIKEY_F3				0x72		/**< f3 key */
#define 	 PLGUIKEY_F4				0x73		/**< f4 key */
#define 	 PLGUIKEY_F5				0x74		/**< f5 key */
#define 	 PLGUIKEY_F6				0x75		/**< f6 key */
#define 	 PLGUIKEY_F7				0x76		/**< f7 key */
#define 	 PLGUIKEY_F8				0x77		/**< f8 key */
#define 	 PLGUIKEY_F9				0x78		/**< f9 key */
#define 	 PLGUIKEY_F10				0x79		/**< f10 key */
#define 	 PLGUIKEY_F11				0x7A		/**< f11 key */
#define 	 PLGUIKEY_F12				0x7B		/**< f12 key */
	 	   
#define 	 PLGUIKEY_NUMLOCK			0x90		// num lock key */
#define 	 PLGUIKEY_SCROLL			0x91		// scroll lock key */  

#define 	 PLGUIKEY_CIRCUMFLEX		0xDC		// ^ circumflex */

#elif defined(LINUX)

#include <X11/keysym.h>
#ifdef None
	#undef None
#endif

//           Virtual code            Hex Value      Key
// [TODO] Check modification keys
#define		 PLGUIMOD_ALT				0x0001				// alt
#define		 PLGUIMOD_CONTROL			0x0002				// control
#define		 PLGUIMOD_ALTGR				0x0003				// alt-gr
#define		 PLGUIMOD_SHIFT				0x0004				// shift
#define		 PLGUIMOD_WIN				0x0008				// Windows key

#define 	 PLGUIKEY_LBUTTON			0x01				// left mouse button  
#define 	 PLGUIKEY_RBUTTON			0x02				// right mouse button  
#define 	 PLGUIKEY_CANCEL			XK_Cancel 			// control-break processing (0x03?)  
#define 	 PLGUIKEY_MBUTTON			0x04				// middle mouse button (three-button mouse)  
#define 	 PLGUIKEY_BACK				XK_BackSpace		// backspace  
#define 	 PLGUIKEY_TAB				XK_Tab				// tab  
#define 	 PLGUIKEY_CLEAR				XK_Clear			// clear  
#define 	 PLGUIKEY_RETURN			XK_Return			// enter  
#define 	 PLGUIKEY_SHIFT				XK_Shift_L			// shift
#define 	 PLGUIKEY_CONTROL			XK_Control_L		// ctrl
#define 	 PLGUIKEY_MENU				XK_Menu				// alt
#define 	 PLGUIKEY_PAUSE				XK_Pause			// pause
#define 	 PLGUIKEY_CAPITAL			XK_Caps_Lock		// caps lock
#define 	 PLGUIKEY_ESCAPE			XK_Escape			// esc  
#define 	 PLGUIKEY_SPACE				XK_space			// spacebar  
#define 	 PLGUIKEY_PRIOR				XK_Prior			// page up   
#define 	 PLGUIKEY_NEXT				XK_Next				// page down  
#define 	 PLGUIKEY_END				XK_End				// end key  
#define 	 PLGUIKEY_HOME				XK_Home				// home key  
#define 	 PLGUIKEY_LEFT				XK_Left				// left arrow  
#define 	 PLGUIKEY_UP				XK_Up				// up arrow  
#define 	 PLGUIKEY_RIGHT				XK_Right			// right arrow  
#define 	 PLGUIKEY_DOWN				XK_Down				// down arrow  
#define 	 PLGUIKEY_SELECT			XK_Select			// select key  
#define 	 PLGUIKEY_EXECUTE			XK_Execute			// execute key  
#define 	 PLGUIKEY_SNAPSHOT			XK_Print			// print screen key  
#define 	 PLGUIKEY_INSERT			XK_Insert			// insert key  
#define 	 PLGUIKEY_DELETE			XK_Delete			// delete key  
#define 	 PLGUIKEY_HELP				XK_Help				// help key  
#define 	 PLGUIKEY_0					XK_0				// 0   
#define 	 PLGUIKEY_1					XK_1				// 1   
#define 	 PLGUIKEY_2					XK_2				// 2   
#define 	 PLGUIKEY_3					XK_3				// 3   
#define 	 PLGUIKEY_4					XK_4				// 4   
#define 	 PLGUIKEY_5					XK_5				// 5   
#define 	 PLGUIKEY_6					XK_6				// 6   
#define 	 PLGUIKEY_7					XK_7				// 7   
#define 	 PLGUIKEY_8					XK_8				// 8   
#define 	 PLGUIKEY_9					XK_9				// 9   
#define 	 PLGUIKEY_A					XK_a				// a   
#define 	 PLGUIKEY_B					XK_b				// b   
#define 	 PLGUIKEY_C					XK_c				// c   
#define 	 PLGUIKEY_D					XK_d				// d   
#define 	 PLGUIKEY_E					XK_e				// e   
#define 	 PLGUIKEY_F					XK_f				// f   
#define 	 PLGUIKEY_G					XK_g				// g   
#define 	 PLGUIKEY_H					XK_h				// h   
#define 	 PLGUIKEY_I					XK_i				// i   
#define 	 PLGUIKEY_J					XK_j				// j   
#define 	 PLGUIKEY_K					XK_k				// k   
#define 	 PLGUIKEY_L					XK_l				// l   
#define 	 PLGUIKEY_M					XK_m				// m   
#define 	 PLGUIKEY_N					XK_n				// n   
#define		 PLGUIKEY_O					XK_o				// o   
#define 	 PLGUIKEY_P					XK_p				// p
#define		 PLGUIKEY_Q					XK_q				// q   
#define 	 PLGUIKEY_R					XK_r				// r   
#define 	 PLGUIKEY_S					XK_s				// s   
#define 	 PLGUIKEY_T					XK_t				// t   
#define 	 PLGUIKEY_U					XK_u				// u   
#define 	 PLGUIKEY_V					XK_v				// v   
#define 	 PLGUIKEY_W					XK_w				// w   
#define 	 PLGUIKEY_X					XK_x				// x   
#define 	 PLGUIKEY_Y					XK_y				// y   
#define 	 PLGUIKEY_Z					XK_z				// z   
#define  	 PLGUIKEY_NUMPAD0			XK_KP_0				// Numeric keypad 0 key  
#define 	 PLGUIKEY_NUMPAD1			XK_KP_1				// Numeric keypad 1 key  
#define 	 PLGUIKEY_NUMPAD2			XK_KP_2				// Numeric keypad 2 key  
#define 	 PLGUIKEY_NUMPAD3			XK_KP_3				// Numeric keypad 3 key  
#define 	 PLGUIKEY_NUMPAD4			XK_KP_4				// Numeric keypad 4 key  
#define 	 PLGUIKEY_NUMPAD5			XK_KP_5				// Numeric keypad 5 key  
#define 	 PLGUIKEY_NUMPAD6			XK_KP_6				// Numeric keypad 6 key  
#define 	 PLGUIKEY_NUMPAD7			XK_KP_7				// Numeric keypad 7 key  
#define 	 PLGUIKEY_NUMPAD8			XK_KP_8				// Numeric keypad 8 key  
#define 	 PLGUIKEY_NUMPAD9			XK_KP_9				// Numeric keypad 9 key  
#define 	 PLGUIKEY_MULTIPLY			XK_KP_Multiply		// Multiply key  
#define 	 PLGUIKEY_ADD				XK_KP_Add			// Add key  
#define 	 PLGUIKEY_SEPARATOR			XK_KP_Separator		// Separator key  
#define 	 PLGUIKEY_SUBTRACT			XK_KP_Subtract		// Subtract key  
#define 	 PLGUIKEY_DECIMAL			XK_KP_Decimal		// Decimal key  
#define 	 PLGUIKEY_DIVIDE			XK_KP_Divide		// Divide key  
#define 	 PLGUIKEY_F1				XK_F1				// F1 key  
#define 	 PLGUIKEY_F2				XK_F2				// F2 key  
#define 	 PLGUIKEY_F3				XK_F3				// F3 key  
#define 	 PLGUIKEY_F4				XK_F4				// F4 key  
#define 	 PLGUIKEY_F5				XK_F5				// F5 key  
#define 	 PLGUIKEY_F6				XK_F6				// F6 key  
#define 	 PLGUIKEY_F7				XK_F7				// F7 key  
#define 	 PLGUIKEY_F8				XK_F8				// F8 key  
#define 	 PLGUIKEY_F9				XK_F9				// F9 key  
#define 	 PLGUIKEY_F10				XK_F10				// F10 key  
#define 	 PLGUIKEY_F11				XK_F11				// F11 key  
#define 	 PLGUIKEY_F12				XK_F12				// F12 key  
#define 	 PLGUIKEY_NUMLOCK			XK_Num_Lock			// num lock key  
#define 	 PLGUIKEY_SCROLL			XK_Scroll_Lock		// scroll lock key  
#define 	 PLGUIKEY_CIRCUMFLEX		XK_asciicircum		// ^ circumflex

#endif


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGui


#endif // __PLGUI_KEYS_H__
