/*********************************************************\
 *  File: MultiThreadingTest.cpp                         *
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
#include <stdio.h>
#include <PLGeneral/System/System.h>
#include <PLGeneral/System/Mutex.h>
#include <PLGeneral/System/Thread.h>
#include "PLTestBase/General/MultiThreadingTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
uint32		   g_nPots     = 0;
volatile bool  g_bContinue = false;
Mutex		  *g_pMutex    = NULL;


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
class Child : public Thread {
	public:
		int m_nRounds;

		virtual int Run()
		{
			m_nRounds = 0;
			bool bContinue = false;
			g_pMutex->Lock();			// Secure the g_bContinue read
			bContinue = g_bContinue;
			g_pMutex->Unlock();
			while (bContinue) {
				g_pMutex->Lock();		// Secure the pot
				++g_nPots;
				printf("'%s' is using the pot.\n", GetName().GetASCII());
				if (g_nPots > 1)
					printf("Oh! Someone other is using the pot!\n"); // Can/should NEVER happen! :)
				--g_nPots;
				bContinue = g_bContinue;
				g_pMutex->Unlock();
				++m_nRounds;
			}
			printf("Yes, mum.\n");

			return 0;
		}
};


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *MultiThreadingTest::GetName() const
{
	return "MultiThreading";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void MultiThreadingTest::Test()
{
	const int nChildren = 5;
	Child *pChildren[nChildren];

	// Sleep
	Print("Sleep 0.5 Seconds\n");
	Print("\n");
	System::GetInstance()->Sleep(500);

	// Create synchronisation object
	g_pMutex = new Mutex();

	// Create tasks
	g_bContinue = true;
	for (int i=0; i<nChildren; ++i) {
		// Create the child thread
		Child *pChild = pChildren[i] = new Child();

		// Give the child thread a neat human readable name
		pChild->SetName(String::Format("Thread_%d", i));

		// Start the child thread
		pChild->Start();
	}

	System::GetInstance()->Sleep(2*50);
	g_pMutex->Lock();
	Print("All finished?\n");
	g_bContinue = false;
	g_pMutex->Unlock();

	// Wait until all our children are finished :)
	// (threads are freed automatically)
	for (int i=0; i<nChildren; ++i) {
		pChildren[i]->Join(100);
		Print("Thread %d had the pot %d times.\n", i+1, pChildren[i]->m_nRounds);
	}

	// Destroy the synchronisation object
	delete g_pMutex;
}
