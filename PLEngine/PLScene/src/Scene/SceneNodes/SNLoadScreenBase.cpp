/*********************************************************\
 *  File: SNLoadScreenBase.cpp                           *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneNodes/SNLoadScreenBase.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLRenderer;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNLoadScreenBase)


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNLoadScreenBase::SNLoadScreenBase() :
	Flags(this),
	EventHandlerContainer   (&SNLoadScreenBase::NotifyContainer,	this),
	EventHandlerLoadProgress(&SNLoadScreenBase::NotifyLoadProgress, this),
	m_pContainer(NULL),
	m_fLoadProgress(0.0f)
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|NoCulling);

	// Connect event handler
	EventContainer.Connect(&EventHandlerContainer);
}

/**
*  @brief
*    Destructor
*/
SNLoadScreenBase::~SNLoadScreenBase()
{
}

/**
*  @brief
*    Returns the current load progress
*/
float SNLoadScreenBase::GetLoadProgress() const
{
	return m_fLoadProgress;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node container changed
*/
void SNLoadScreenBase::NotifyContainer()
{
	// Disconnect event handler
	if (m_pContainer)
		m_pContainer->EventLoadProgress.Disconnect(&EventHandlerLoadProgress);

	// Connect event handler
	m_pContainer = GetContainer();
	if (m_pContainer)
		m_pContainer->EventLoadProgress.Connect(&EventHandlerLoadProgress);
}

/**
*  @brief
*    Called on load progress
*/
void SNLoadScreenBase::NotifyLoadProgress(float fLoadProgress)
{
	m_fLoadProgress = fLoadProgress;
}


//[-------------------------------------------------------]
//[ Public virtual SceneNode functions                    ]
//[-------------------------------------------------------]
void SNLoadScreenBase::DrawPost(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Show the load screen?
	if (m_fLoadProgress >= 0.0f && m_fLoadProgress <= 1.0f) {
		// Call base implementation
		SceneNode::DrawPost(cRenderer, pVisNode);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
