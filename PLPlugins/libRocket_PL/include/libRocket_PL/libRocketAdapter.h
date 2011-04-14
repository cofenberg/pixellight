/*********************************************************\
 *  File: libRocketAdapter.h                             *
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


#ifndef __LIBROCKET_PL_ADAPTER_H__
#define __LIBROCKET_PL_ADAPTER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "libRocket_PL/libRocket_PL.h"


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
namespace PLMath {
	class Vector2i;
}
namespace PLGui {
	class Widget;
}
namespace PLRenderer {
	class RendererContext;
}
namespace libRocket_PL {
	class SRPlibRocket;
	class MessageFilterRocket;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace libRocket_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Rocket <-> PixelLight
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
		*  @param[in] pWidget
		*    PLGui widget we render in, can be a null pointer
		*/
		LIBROCKET_PL_API libRocketAdapter(PLRenderer::RendererContext &cRendererContext, PLGui::Widget *pWidget);

		/**
		*  @brief
		*    Destructor
		*/
		LIBROCKET_PL_API ~libRocketAdapter();

		/**
		*  @brief
		*    Returns the libRocket context
		*
		*  @return
		*    libRocket context, can be a null pointer
		*/
		LIBROCKET_PL_API Rocket::Core::Context *GetRocketContext() const;

		/**
		*  @brief
		*    Returns the libRocket render interface
		*
		*  @return
		*    libRocket render interface, can be a null pointer
		*/
		LIBROCKET_PL_API Rocket::Core::RenderInterface *GetRocketRenderInterface() const;

		/**
		*  @brief
		*    Returns the libRocket system interface
		*
		*  @return
		*    libRocket system interface, can be a null pointer
		*/
		LIBROCKET_PL_API Rocket::Core::SystemInterface *GetRocketSystemInterface() const;

		/**
		*  @brief
		*    Returns the libRocket file interface
		*
		*  @return
		*    libRocket file interface, can be a null pointer
		*/
		LIBROCKET_PL_API Rocket::Core::FileInterface *GetFileInterface() const;

		/**
		*  @brief
		*    Returns the message filter that feeds PLGui messages into libRocket
		*
		*  @return
		*    Message filter that feeds PLGui messages into libRocket, can be a null pointer
		*/
		LIBROCKET_PL_API MessageFilterRocket *GetMessageFilterRocket() const;

		/**
		*  @brief
		*    Creates a libRocket scene renderer pass instance
		*
		*  @return
		*    libRocket scene renderer pass instance, can be a null pointer
		*/
		LIBROCKET_PL_API SRPlibRocket *CreateSRPlibRocketInstance() const;


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

		/**
		*  @brief
		*    Called when the size was changed
		*
		*  @param[in] vSize
		*    New size
		*/
		void NotifySize(const PLMath::Vector2i &vSize);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<const PLMath::Vector2i&> EventHandlerSize;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		Rocket::Core::Context			*m_pRocketContext;			/**< libRocket context, can be a null pointer */
		Rocket::Core::RenderInterface	*m_pRocketRenderInterface;	/**< libRocket render interface, can be a null pointer */
		Rocket::Core::SystemInterface	*m_pRocketSystemInterface;	/**< libRocket system interface, can be a null pointer */
		Rocket::Core::FileInterface		*m_pRocketFileInterface;	/**< libRocket file interface, can be a null pointer */
		MessageFilterRocket				*m_pMessageFilterRocket;	/**< Message filter that feeds PLGui messages into libRocket, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // libRocket_PL


#endif // __LIBROCKET_PL_ADAPTER_H__