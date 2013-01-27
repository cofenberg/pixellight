/*********************************************************\
 *  File: PLSceneTexture.h                               *
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


#ifndef __PL_SCENETEXTURE_H__
#define __PL_SCENETEXTURE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PLScene;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Exported PixelLight texture
*/
class PLSceneTexture {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLScene;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the texture name
		*
		*  @return
		*    The texture name
		*/
		PLCore::String GetName() const;

		/**
		*  @brief
		*    Returns the reference count of this texture
		*
		*  @return
		*    The reference count of this texture
		*/
		unsigned int GetReferenceCount() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cScene
		*    Scene this texture is in
		*  @param[in] sName
		*    Name of this texture
		*  @param[in] bNormalMap_xGxR
		*    Is this a 'xGxR' normal map?
		*/
		PLSceneTexture(PLScene &cScene, const PLCore::String &sName, bool bNormalMap_xGxR = false);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneTexture();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLScene			*m_pScene;			/**< PL owner scene (always valid!) */
		PLCore::String	 m_sName;			/**< Name of this texture */
		unsigned int	 m_nReferenceCount;	/**< Reference count of this texture */


};


#endif // __PL_SCENETEXTURE_H__
