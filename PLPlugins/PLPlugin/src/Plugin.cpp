/*********************************************************\
 *  File: Plugin.cpp                                     *
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPlugin/PluginImpl.h"
#include "PLPlugin/Plugin.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLPlugin {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Plugin::Plugin(PluginImpl &cImpl) :
	m_pImpl(&cImpl)
{
	// Set plugin
	m_pImpl->m_pPlugin = this;
}

/**
*  @brief
*    Destructor
*/
Plugin::~Plugin()
{
}

/**
*  @brief
*    Get window width
*/
uint32 Plugin::GetWidth() const
{
	// Call backend
	return m_pImpl->GetWidth();
}

/**
*  @brief
*    Get window height
*/
uint32 Plugin::GetHeight() const
{
	// Call backend
	return m_pImpl->GetHeight();
}

/**
*  @brief
*    Redraw plugin window
*/
void Plugin::Redraw()
{
	// Call backend
	m_pImpl->Redraw();
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get plugin implementation
*/
PluginImpl *Plugin::GetImpl() const
{
	// Return implementation
	return m_pImpl;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin
