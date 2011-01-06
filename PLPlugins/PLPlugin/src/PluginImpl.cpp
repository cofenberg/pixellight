/*********************************************************\
 *  File: PluginImpl.cpp                                 *
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPlugin/Plugin.h"
#include "PLPlugin/PluginImpl.h"


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
PluginImpl::PluginImpl() :
	m_hPluginWnd(nullptr),
	m_hPluginDC(nullptr),
	m_nWidth(0),
	m_nHeight(0)
{
}

/**
*  @brief
*    Destructor
*/
PluginImpl::~PluginImpl()
{
}

/**
*  @brief
*    Get window handle
*/
handle PluginImpl::GetWindowHandle() const
{
	// Return window handle
	return (handle)m_hPluginWnd;
}

/**
*  @brief
*    Get device context handle
*/
handle PluginImpl::GetDeviceContext() const
{
	// Return DC handle
	return (handle)m_hPluginDC;
}

/**
*  @brief
*    Get window width
*/
uint32 PluginImpl::GetWidth() const
{
	// Return current width
	return m_nWidth;
}

/**
*  @brief
*    Get window height
*/
uint32 PluginImpl::GetHeight() const
{
	// Return current height
	return m_nHeight;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called to initialize the plugin
*/
void PluginImpl::OnInit()
{
	// Call virtual function from plugin
	m_pPlugin->OnInit();
}

/**
*  @brief
*    Called to deinitialize the plugin
*/
void PluginImpl::OnDeInit()
{
	// Call virtual function from plugin
	m_pPlugin->OnDeInit();
}

/**
*  @brief
*    Called to let the plugin draw into it's window
*/
void PluginImpl::OnDraw()
{
	// Call virtual function from plugin
	m_pPlugin->OnDraw();
}

/**
*  @brief
*    Called when the window size has been changed
*/
void PluginImpl::OnSize()
{
	// Call virtual function from plugin
	m_pPlugin->OnSize();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin
