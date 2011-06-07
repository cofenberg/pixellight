/*********************************************************\
 *  File: SNConsole.h                                    *
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


#ifndef __PLSCENE_SCENENODE_STANDARDCONSOLE_H__
#define __PLSCENE_SCENENODE_STANDARDCONSOLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]


// [TODO] Use FS own functions for this if implemented...
#ifdef WIN32
	#include <PLGeneral/PLGeneralWindowsIncludes.h>
#endif


#include <PLRenderer/Material/MaterialHandler.h>
#include "PLScene/Scene/SceneNodes/Console/SNConsoleBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Standart console implementation
*/
class SNConsole : public SNConsoleBase {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		static const PLGeneral::String StandardMaterial; /**< Standard console material */


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNConsole, "PLScene", PLScene::SNConsoleBase, "Standart console implementation")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNConsole();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNConsole();

		// Get
		PLS_API float GetPos() const;
		PLS_API float GetMaxPos() const;
		PLS_API PLRenderer::Material *GetMaterial();

		// Set
		PLS_API void SetPos(float fNewPos);
		PLS_API void SetMaxPos(float fMax);
		PLS_API void SetAlpha(float fNewAlpha);

		// Overrided virtuals
		PLS_API PLGeneral::String GetDescription() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void NotifyUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		int							m_nRow;			/**< Current log row */
		PLGeneral::uint32			m_nLastRow;		/**< Last log row */
		float						m_fPos;			/**< Y position (between 0 and 1) */
		float						m_fMaxPos;		/**< Maximum position (between 0..1) */
		float						m_fAlpha;		/**< Transparency (255 = full opacity) */
		PLRenderer::MaterialHandler	m_cMaterial;	/**< Console material */


		// [TODO] Use FS own functions for this if implemented...
		// Log view
		#ifdef WIN32
			FILETIME  m_LastTime;
			DWORD	  m_nLastFileSizeHigh;
			DWORD	  m_nLastFileSizeLow;
		#endif


		PLGeneral::Array<PLGeneral::String> m_lstLogLines;	/**< Log lines */


	//[-------------------------------------------------------]
	//[ Public virtual SceneNode functions                    ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void DrawPost(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode = nullptr);


	//[-------------------------------------------------------]
	//[ Private virtual SceneNode functions                   ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_STANDARDCONSOLE_H__
