/*********************************************************\
 *  File: WorldThread.h                                  *
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


#ifndef __PLNEWTON_WORLDTHREAD_H__
#define __PLNEWTON_WORLDTHREAD_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/System/Thread.h>
#include "PLPhysicsNewton/WorldUpdate.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class Mutex;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PL Newton physics world update thread
*/
class WorldThread : public WorldUpdate, public PLGeneral::Thread {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class World;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    Owner Newton world
		*/
		WorldThread(World &cWorld);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~WorldThread();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::Mutex *m_pMutex;				/**< Synchronisation object (always valid!) */
		volatile bool	  m_bShutDown;			/**< Shut down this thread? */
		volatile float	  m_fTimeScaleFactor;	/**< Cached time scale factor */
		volatile float	  m_fMaxTimeDifference;	/**< Cached maximum time difference */
		volatile float	  m_fSimulationSpeed;	/**< Cached simulation speed */
		volatile float	  m_fFrameRate;			/**< Cached simulation frame frame */


	//[-------------------------------------------------------]
	//[ Private virtual WorldUpdate functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual bool IsThread();
		virtual bool Lock();
		virtual bool Update(float fTimeScaleFactor, float fMaxTimeDifference, float fSimulationSpeed, float fFrameRate);
		virtual bool Unlock();


	//[-------------------------------------------------------]
	//[ Public virtual PLGeneral::Thread functions            ]
	//[-------------------------------------------------------]
	public:
		virtual int Run();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton


#endif // __PLNEWTON_WORLDTHREAD_H__
