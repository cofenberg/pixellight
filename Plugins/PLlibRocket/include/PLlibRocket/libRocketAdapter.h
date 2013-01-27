/*********************************************************\
 *  File: libRocketAdapter.h                             *
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