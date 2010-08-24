/*********************************************************\
 *  File: PLSceneTexture.h                               *
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


#ifndef __PL_SCENETEXTURE_H__
#define __PL_SCENETEXTURE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <string>


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
		const std::string &GetName() const;

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
		PLSceneTexture(PLScene &cScene, const std::string &sName, bool bNormalMap_xGxR = false);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneTexture();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLScene		*m_pScene;			/**< PL owner scene (always valid!) */
		std::string	 m_sName;			/**< Name of this texture */
		unsigned int m_nReferenceCount;	/**< Reference count of this texture */


};


#endif // __PL_SCENETEXTURE_H__
