/*********************************************************\
 *  File: libRocketAdapter.h                             *
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


#ifndef __PLLIBROCKET_ADAPTER_H__
#define __PLLIBROCKET_ADAPTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLlibRocket/PLlibRocket.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace Rocket {
	namespace Core {
		class Context;
		class FileInterface;
		class RenderInterface;
		class SystemInterface;
	}
}
namespace PLRenderer {
	class RendererContext;
}
namespace PLlibRocket {
	class SRPlibRocket;
	class MessageFilterRocket;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLlibRocket {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    libRocket <-> PixelLight
*/
class libRocketAdapter {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*
		*  @param[in] cRendererContext
		*    The used renderer context
		*/
		PLLIBROCKET_API libRocketAdapter(PLRenderer::RendererContext &cRendererContext);

		/**
		*  @brief
		*    Destructor
		*/
		PLLIBROCKET_API ~libRocketAdapter();

		/**
		*  @brief
		*    Returns the libRocket context
		*
		*  @return
		*    libRocket context, can be a null pointer
		*/
		PLLIBROCKET_API Rocket::Core::Context *GetRocketContext() const;

		/**
		*  @brief
		*    Returns the libRocket render interface
		*
		*  @return
		*    libRocket render interface, can be a null pointer
		*/
		PLLIBROCKET_API Rocket::Core::RenderInterface *GetRocketRenderInterface() const;

		/**
		*  @brief
		*    Returns the libRocket system interface
		*
		*  @return
		*    libRocket system interface, can be a null pointer
		*/
		PLLIBROCKET_API Rocket::Core::SystemInterface *GetRocketSystemInterface() const;

		/**
		*  @brief
		*    Returns the libRocket file interface
		*
		*  @return
		*    libRocket file interface, can be a null pointer
		*/
		PLLIBROCKET_API Rocket::Core::FileInterface *GetFileInterface() const;

		/**
		*  @brief
		*    Creates a libRocket scene renderer pass instance
		*
		*  @return
		*    libRocket scene renderer pass instance, can be a null pointer
		*/
		PLLIBROCKET_API SRPlibRocket *CreateSRPlibRocketInstance() const;


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
		libRocketAdapter(const libRocketAdapter &cSource);

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
		libRocketAdapter &operator =(const libRocketAdapter &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Rocket::Core::Context			*m_pRocketContext;			/**< libRocket context, can be a null pointer */
		Rocket::Core::RenderInterface	*m_pRocketRenderInterface;	/**< libRocket render interface, can be a null pointer */
		Rocket::Core::SystemInterface	*m_pRocketSystemInterface;	/**< libRocket system interface, can be a null pointer */
		Rocket::Core::FileInterface		*m_pRocketFileInterface;	/**< libRocket file interface, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLlibRocket


#endif // __PLLIBROCKET_ADAPTER_H__