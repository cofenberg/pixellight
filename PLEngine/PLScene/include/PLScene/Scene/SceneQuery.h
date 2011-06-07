/*********************************************************\
 *  File: SceneQuery.h                                   *
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


#ifndef __PLSCENE_SCENEQUERY_H__
#define __PLSCENE_SCENEQUERY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/Element.h>
#include <PLGeneral/Base/ElementHandler.h>
#include <PLGeneral/Base/ElementManager.h>
#include <PLCore/Base/Object.h>
#include <PLCore/Base/Event/Event.h>
#include "PLScene/PLScene.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SceneNode;
class SceneContext;
class SceneContainer;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract scene query class
*
*  @remarks
*    The scene query is operating on a scene container. For instance there
*    can be a query to perform volume checks against the scene or a query
*    rendering the scene. This process can be quite efficient if the scene
*    container provides a good scene hierarchy. Events will inform about the results.
*
*  @note
*    - Derived classes should use a 'SQ'-prefix (example: SQLine)
*/
class SceneQuery : public PLCore::Object, public PLGeneral::Element<SceneQuery> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SceneContainer;
	friend class PLGeneral::ElementManager<SceneQuery>;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*   Flags
		*/
		enum EFlags {
			Recursive = 1<<0,	/**< Take sub scene containers into account */
			StopQuery = 1<<1	/**< Stop the currently running query (removed within PerformQuery() on start automatically) */
		};


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SceneQuery, "PLScene", PLCore::Object, "Abstract scene query class")
		// Signals
		pl_signal_2(SignalSceneNode,	SceneQuery &,	SceneNode &,	"A scene node was 'touched' during the query. Event causing scene query and found scene node as parameters.",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the scene context the scene query is in
		*
		*  @return
		*    The scene context the scene query is in, can but shouldn't be a null pointer
		*/
		PLS_API SceneContext *GetSceneContext() const;

		/**
		*  @brief
		*    Returns the scene container this query operates on
		*
		*  @return
		*    The scene container this query operates on
		*/
		inline SceneContainer &GetSceneContainer() const;

		/**
		*  @brief
		*    Returns the flags
		*
		*  @return
		*    Flags (see EFlags)
		*/
		inline PLGeneral::uint32 GetFlags() const;

		/**
		*  @brief
		*    Sets the flags
		*
		*  @param[in] nFlags
		*    Flags (see EFlags)
		*/
		inline void SetFlags(PLGeneral::uint32 nFlags = Recursive);

		/**
		*  @brief
		*    Stops the currently running query
		*/
		inline void Stop();


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Performs the query
		*
		*  @note
		*    - Before you start the query you have to do some settings within
		*      the derived query classes first. (for instance setting the query
		*      volume)
		*
		*  @return
		*    'true' if the query was cancelled by the user, else 'false'
		*/
		virtual bool PerformQuery() = 0;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		PLS_API SceneQuery();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SceneQuery();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::uint32 m_nFlags;	/**< Flags (see EFlags) */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		SceneContainer *m_pSceneContainer;	/**< Scene container this query operates on, NEVER a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "SceneQuery.inl"


#endif // __PLSCENE_SCENEQUERY_H__
