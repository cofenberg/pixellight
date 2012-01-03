/*********************************************************\
 *  File: SNConsole.h                                    *
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


#ifndef __PLENGINE_COMPOSITING_STANDARDCONSOLE_H__
#define __PLENGINE_COMPOSITING_STANDARDCONSOLE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]


// [TODO] Use FS own functions for this if implemented...
#ifdef WIN32
	#include <PLCore/PLCoreWindowsIncludes.h>
#endif


#include <PLRenderer/Material/MaterialHandler.h>
#include "PLEngine/Compositing/Console/SNConsoleBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Standard console implementation
*/
class SNConsole : public SNConsoleBase {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		static const PLCore::String StandardMaterial; /**< Standard console material */


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SNConsole, "PLEngine", PLEngine::SNConsoleBase, "Standard console implementation")
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
		PL_API SNConsole();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SNConsole();

		// Get
		PL_API float GetPos() const;
		PL_API float GetMaxPos() const;
		PL_API PLRenderer::Material *GetMaterial();

		// Set
		PL_API void SetPos(float fNewPos);
		PL_API void SetMaxPos(float fMax);
		PL_API void SetAlpha(float fNewAlpha);

		// Overridden virtual
		PL_API PLCore::String GetDescription() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void OnUpdate();


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
		PLCore::uint32				m_nLastRow;		/**< Last log row */
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


		PLCore::Array<PLCore::String> m_lstLogLines;	/**< Log lines */


	//[-------------------------------------------------------]
	//[ Public virtual PLScene::SceneNode functions           ]
	//[-------------------------------------------------------]
	public:
		PL_API virtual void DrawPost(PLRenderer::Renderer &cRenderer, const PLScene::VisNode *pVisNode = nullptr) override;


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void InitFunction() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_COMPOSITING_STANDARDCONSOLE_H__
