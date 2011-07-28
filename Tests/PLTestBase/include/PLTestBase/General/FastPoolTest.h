/*********************************************************\
 *  File: FastPoolTest.h                                 *
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


#ifndef __PLTESTBASE_GENERAL_FASTPOOLTEST_H__
#define __PLTESTBASE_GENERAL_FASTPOOLTEST_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Container/FastPool.h>
#include "PLTestBase/General/ContainerTestCase.h"


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class TestFastPoolElement : public PLCore::FastPoolElement<TestFastPoolElement> {
	public:
		int i;
		TestFastPoolElement() : i(0) {}
		TestFastPoolElement(int nOther) : i(nOther) { }
		bool operator ==(const TestFastPoolElement &cOther) const
		{
			return i == cOther.i;
		}
		bool operator ==(int nOther) const
		{
			return i == nOther;
		}
		bool operator !=(int nOther) const
		{
			return i != nOther;
		}
};


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Fast pool class for function tests
*/
class FastPoolTest : public ContainerTestCase<TestFastPoolElement> {
	

	//[-------------------------------------------------------]
	//[ Public virtual TestCase functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual const char *GetName() const override;


	//[-------------------------------------------------------]
	//[ Private virtual TestCase functions                    ]
	//[-------------------------------------------------------]
	private:
		virtual void Test() override;


};


#endif // __PLTESTBASE_GENERAL_FASTPOOLTEST_H__
