/*********************************************************\
 *  File: PLCheckMacros.h                                 *
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

#ifndef __PLCHECKMACROS_H_
#define __PLCHECKMACROS_H_
#pragma once

#ifdef CHECK_MATRIX3X3
	#error UnitTest++ redefines CHECK_MATRIX3X3
#endif

#ifdef CHECK_IMPLEMENT
	#error UnitTest++ redefines CHECK_MATRIX3X3
#endif

#ifdef CHECK_NOT_EQUAL
	#errorCHECK_NOT_EQUAL
#endif

#define CHECK_MATRIX3X3(expected, actual, tolerance) \
    do \
    { \
        try { \
            UnitTest::CheckMatrix3x3(*UnitTest::CurrentTest::Results(), expected, actual, tolerance, UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__)); \
        } \
        catch (...) { \
            UnitTest::CurrentTest::Results()->OnTestFailure(UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in CHECK_MATRIX3X3()"); \
        } \
    } while (0)

#define CHECK_IMPLEMENT \
    do \
    { \
        try { \
            UnitTest::CheckMissingImplementation(*UnitTest::CurrentTest::Results(), UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__)); \
        } \
        catch (...) { \
            UnitTest::CurrentTest::Results()->OnTestFailure(UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in CHECK_IMPLEMENT"); \
        } \
    } while (0)

#define CHECK_NOT_EQUAL(expected, actual) \
    do \
    { \
        try { \
            UnitTest::CheckNotEqual(*UnitTest::CurrentTest::Results(), expected, actual, UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__)); \
        } \
        catch (...) { \
            UnitTest::CurrentTest::Results()->OnTestFailure(UnitTest::TestDetails(*UnitTest::CurrentTest::Details(), __LINE__), \
                    "Unhandled exception in CHECK_NOT_EQUAL(" #expected ", " #actual ")"); \
        } \
    } while (0)

#endif // __PLCHECKMACROS_H_
