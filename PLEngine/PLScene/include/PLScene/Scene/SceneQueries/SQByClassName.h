/*********************************************************\
 *  File: SQByClassName.h                                *
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


#ifndef __PLSCENE_SCENEQUERY_BYCLASSNAME_H__
#define __PLSCENE_SCENEQUERY_BYCLASSNAME_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/RegEx.h>
#include "PLScene/Scene/SceneQuery.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node enumeration by class name scene query class
*
*  @remarks
*    This scene query will enumerate scene nodes of the scene graph
*    if their class name matches a given regular expression.
*/
class SQByClassName : public SceneQuery {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SQByClassName, "PLScene", PLScene::SceneQuery, "Scene node enumeration by class name scene query class")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*   Flags (SceneQuery flags extension)
		*/
		enum EFlags {
			IgnoreBaseClasses = 1<<2	/**< Ignore base classes of scene node classes */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SQByClassName();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SQByClassName();

		/**
		*  @brief
		*    Returns the used regular expression
		*
		*  @return
		*    The used regular expression
		*/
		PLS_API const PLGeneral::RegEx &GetRegEx() const;

		/**
		*  @brief
		*    Sets the used regular expression
		*
		*  @param[in] cRegEx
		*    The regular expression to use
		*/
		PLS_API void SetRegEx(const PLGeneral::RegEx &cRegEx);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Recursive part of PerformQuery()
		*
		*  @param[in] cContainer
		*    Current scene container we work on
		*
		*  @return
		*    'true' to continue the query, 'false' if stop it right now
		*/
		bool PerformQueryRec(const SceneContainer &cContainer);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::RegEx m_cRegEx;	/**< Regular expression used for the query */


	//[-------------------------------------------------------]
	//[ Public virtual SceneQuery functions                   ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool PerformQuery();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENEQUERY_BYCLASSNAME_H__
