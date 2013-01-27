/*********************************************************\
 *  File: MyPicking.h                                    *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLSAMPLE_64_MYPICKING_H__
#define __PLSAMPLE_64_MYPICKING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodeHandler.h>
#include <PLEngine/Picking/MousePicking.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Application64;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Picking application component
*/
class MyPicking : public PLEngine::MousePicking {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cApplication
		*    Owner application
		*/
		MyPicking(Application64 &cApplication);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MyPicking();

		/**
		*  @brief
		*    Performs the picking
		*/
		void PerformPicking();


	//[-------------------------------------------------------]
	//[ Private virtual PLEngine::Picking functions           ]
	//[-------------------------------------------------------]
	private:
		virtual bool OnPickingCandidate(PLScene::SceneNode &cSceneNode) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Application64			   *m_pApplication;						/**< Owner application, always valid! */
		PLCore::uint64				m_nLastPickingTime;					/**< Last picking time */
		PLScene::SceneNodeHandler	m_cCurrentPickedSceneNodeHandler;	/**< Currently picked scene node */


};


#endif // __PLSAMPLE_64_MYPICKING_H__
