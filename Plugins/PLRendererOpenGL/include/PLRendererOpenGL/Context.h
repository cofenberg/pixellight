/*********************************************************\
 *  File: Context.h                                      *
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


#ifndef __PLRENDEREROPENGL_CONTEXT_H__
#define __PLRENDEREROPENGL_CONTEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	template <class ValueType> class Array;
}
namespace PLRenderer {
	struct DisplayMode;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract OpenGL context base class
*/
class Context {


	//[-------------------------------------------------------]
	//[ Public virtual Context methods                        ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Context();

		/**
		*  @brief
		*    Returns whether or not the context is valid
		*
		*  @return
		*    'true' if the context is valid, else 'false'
		*/
		virtual bool IsValid() const = 0;

		/**
		*  @brief
		*    Returns makes the internal dummy to the current render target
		*/
		virtual void MakeDummyCurrent() const = 0;

		/**
		*  @brief
		*    Enumerates all available display modes
		*
		*  @param[out] lstDisplayModeList
		*    Receives all found display modes, list is not cleared before new items are added
		*
		*  @return
		*    'true' if all went fine and at least one display mode was found, else 'false'
		*/
		virtual bool QueryDisplayModes(PLGeneral::Array<const PLRenderer::DisplayMode*> &lstDisplayModeList) = 0;


	//[-------------------------------------------------------]
	//[ Protected methods                                     ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		Context();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Context(const Context &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Context &operator =(const Context &cSource);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_CONTEXT_H__
