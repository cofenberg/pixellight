/*********************************************************\
 *  File: WorldUpdate.h                                  *
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


#ifndef __PLPHYSICSNEWTON_WORLDUPDATE_H__
#define __PLPHYSICSNEWTON_WORLDUPDATE_H__
#pragma once


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class World;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PL Newton physics world update class
*/
class WorldUpdate {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class World;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cWorld
		*    Owner Newton world
		*/
		WorldUpdate(World &cWorld);


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~WorldUpdate();

		/**
		*  @brief
		*    Returns whether or not the implementation is using a thread
		*
		*  @return
		*    'true' if the implementation is using a thread, else 'false'
		*/
		virtual bool IsThread();

		/**
		*  @brief
		*    Locks the updated
		*
		*  @return
		*    'true' if successful, 'false' on error
		*/
		virtual bool Lock();

		/**
		*  @brief
		*    Updates the physics
		*
		*  @param[in] fTimeScaleFactor
		*    The time scale factor
		*  @param[in] fMaxTimeDifference
		*    The maximum time difference in seconds
		*  @param[in] fSimulationSpeed
		*    The simulation speed
		*  @param[in] fFrameRate
		*    The frame rate the simulation runs on
		*
		*  @return
		*    'true' if successful, 'false' on error
		*
		*  @note
		*    - It's recommended to call Lock() before, and Unlock() after this function
		*/
		virtual bool Update(float fTimeScaleFactor, float fMaxTimeDifference, float fSimulationSpeed, float fFrameRate);

		/**
		*  @brief
		*    Unlocks the updated
		*
		*  @return
		*    'true' if successful, 'false' on error
		*/
		virtual bool Unlock();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		World		   *m_pWorld;			/**< Owner Newton world (always valid!) */
		PLCore::uint32  m_nTotalNumOfSteps;	/**< Total number of performed physics steps */
		PLCore::uint64  m_nLastTime;		/**< Time the last update was performed in milliseconds */
		float			m_fTimeElapsed;		/**< Elapsed time in seconds */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton


#endif // __PLPHYSICSNEWTON_WORLDUPDATE_H__
