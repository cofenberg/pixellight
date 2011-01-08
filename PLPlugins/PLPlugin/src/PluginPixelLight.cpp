/*********************************************************\
 *  File: PluginPixelLight.cpp                           *
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGui/Widgets/Widget.h>
// [TODO] PLGui: Native widget
//#include <PLGui/Base/NativeWindow.h>
#include "PLPlugin/PluginImpl.h"
#include "PLPlugin/Application.h"
#include "PLPlugin/PluginPixelLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLGui;
namespace PLPlugin {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PluginPixelLight::PluginPixelLight(PluginImpl &cImpl) : Plugin(cImpl),
	m_pApplication(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
PluginPixelLight::~PluginPixelLight()
{
}


//[-------------------------------------------------------]
//[ Private virtual Plugin functions                      ]
//[-------------------------------------------------------]
void PluginPixelLight::OnInit()
{
	m_pApplication = new Application();
// [TODO] PLGui: Native widget
//	m_pApplication->Embed(new NativeWindow(m_pImpl->GetWindowHandle()));
}

void PluginPixelLight::OnDeInit()
{
// [TODO] PLGui: Native widget
	//	m_pApplication->StopEmbedded();
	delete m_pApplication;
	m_pApplication = nullptr;
}

void PluginPixelLight::OnDraw()
{
	m_pApplication->Update();
	Redraw();
}

void PluginPixelLight::OnSize()
{
	if (m_pApplication) {
		Widget *pWidget = m_pApplication->GetMainWindow();
		if (pWidget)
			pWidget->SetSize(Vector2i(GetWidth(), GetHeight()));
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPlugin
