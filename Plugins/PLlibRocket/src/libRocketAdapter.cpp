/*********************************************************\
 *  File: libRocketAdapter.cpp                           *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>
#include "PLlibRocket/SRPlibRocket.h"
#include "PLlibRocket/FileInterfacePL.h"
#include "PLlibRocket/SystemInterfacePL.h"
#include "PLlibRocket/RenderInterfacePLShaders.h"
#include "PLlibRocket/libRocketAdapter.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLRenderer;
namespace PLlibRocket {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
libRocketAdapter::libRocketAdapter(RendererContext &cRendererContext) :
	m_pRocketContext(nullptr),
	m_pRocketRenderInterface(nullptr),
	m_pRocketSystemInterface(nullptr),
	m_pRocketFileInterface(nullptr)
{
	// Create and set the render interface
	m_pRocketRenderInterface = new RenderInterfacePLShaders(cRendererContext);
	Rocket::Core::SetRenderInterface(m_pRocketRenderInterface);

	// Create and set the file interface
	m_pRocketFileInterface = new FileInterfacePL();
	Rocket::Core::SetFileInterface(m_pRocketFileInterface);

	// Create and set the system interface
	m_pRocketSystemInterface = new SystemInterfacePL();
	Rocket::Core::SetSystemInterface(m_pRocketSystemInterface);

	// Initialize libRocket
	Rocket::Core::Initialise();
	Rocket::Controls::Initialise();

	// Create and set the context by using a default size (we need anything to start with in here)
	m_pRocketContext = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(1024, 768));
	Rocket::Debugger::Initialise(m_pRocketContext);
}

/**
*  @brief
*    Destructor
*/
libRocketAdapter::~libRocketAdapter()
{
	// De-initialize libRocket
	if (m_pRocketContext) {
		m_pRocketContext->RemoveReference();
		m_pRocketContext = nullptr;
	}
	Rocket::Core::Shutdown();
	if (m_pRocketFileInterface) {
		delete m_pRocketFileInterface;
		m_pRocketFileInterface = nullptr;
	}
	if (m_pRocketSystemInterface) {
		delete m_pRocketSystemInterface;
		m_pRocketSystemInterface = nullptr;
	}
	if (m_pRocketRenderInterface) {
		delete m_pRocketRenderInterface;
		m_pRocketRenderInterface = nullptr;
	}
}

/**
*  @brief
*    Returns the libRocket context
*/
Rocket::Core::Context *libRocketAdapter::GetRocketContext() const
{
	return m_pRocketContext;
}

/**
*  @brief
*    Returns the libRocket render interface
*/
Rocket::Core::RenderInterface *libRocketAdapter::GetRocketRenderInterface() const
{
	return m_pRocketRenderInterface;
}

/**
*  @brief
*    Returns the libRocket system interface
*/
Rocket::Core::SystemInterface *libRocketAdapter::GetRocketSystemInterface() const
{
	return m_pRocketSystemInterface;
}

/**
*  @brief
*    Returns the libRocket file interface
*/
Rocket::Core::FileInterface *libRocketAdapter::GetFileInterface() const
{
	return m_pRocketFileInterface;
}

/**
*  @brief
*    Creates a libRocket scene renderer pass instance
*/
SRPlibRocket *libRocketAdapter::CreateSRPlibRocketInstance() const
{
	return (m_pRocketContext && m_pRocketRenderInterface) ? new SRPlibRocket(*m_pRocketContext, *static_cast<RenderInterfacePL*>(m_pRocketRenderInterface)) : nullptr;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
libRocketAdapter::libRocketAdapter(const libRocketAdapter &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
libRocketAdapter &libRocketAdapter::operator =(const libRocketAdapter &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLlibRocket
