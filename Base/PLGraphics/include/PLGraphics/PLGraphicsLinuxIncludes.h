/*********************************************************\
 *  File: PLGraphicsLinuxInclude.h                       *
 *      Linux includes for PLGraphics
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


#ifndef __PLGRAPHICS_LINUXINCLUDE_H__
#define __PLGRAPHICS_LINUXINCLUDE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <X11/Xlib.h>


//[-------------------------------------------------------]
//[ Public definitions                                    ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mouse buttons
*/
#ifdef Button1
	namespace PLGraphicsLinuxIncludes {
		enum {
			X11_Button1 = Button1,
			X11_Button2 = Button2,
			X11_Button3 = Button3,
			X11_Button4 = Button4,
			X11_Button5 = Button5
		};
	}

	#undef Button1
	#undef Button2
	#undef Button3
	#undef Button4
	#undef Button5

	namespace XLib {
		enum {
			Button1 = PLGraphicsLinuxIncludes::X11_Button1,
			Button2 = PLGraphicsLinuxIncludes::X11_Button2,
			Button3 = PLGraphicsLinuxIncludes::X11_Button3,
			Button4 = PLGraphicsLinuxIncludes::X11_Button4,
			Button5 = PLGraphicsLinuxIncludes::X11_Button5
		};
	}
#endif

	
/**
*  @brief
*    Misc
*/
#ifdef None
	namespace PLGraphicsLinuxIncludes {
		enum {
			X11_None = None,
			X11_Always = Always
		};
	}

	#undef None
	#undef Always
	//#undef PSize

	namespace XLib {
		enum {
			None = PLGraphicsLinuxIncludes::X11_None,
			Always = PLGraphicsLinuxIncludes::X11_Always
		};
	}
#endif


#endif // __PLGRAPHICS_LINUXINCLUDE_H__
