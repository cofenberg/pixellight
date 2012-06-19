/*********************************************************\
 *  File: SNClipPrimitiveBox.cpp                         *
 *
 *  Master thesis
 *    "Scalable Realtime Volume Rendering"
 *
 *  At
 *    Fachhochschule Würzburg-Schweinfurt
 *    Fakultät Informatik, Wirtschaftsinformatik (FIW)
 *    http://www.fh-wuerzburg.de/
 *
 *  Author
 *    Christian Ofenberg (c.ofenberg@pixellight.org or cofenberg@googlemail.com)
 *    Copyright (C) 2011-2012
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Visibility/VisNode.h>
#include "PLVolume/Scene/SNClipPrimitiveBox.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLMath;
using namespace PLRenderer;
using namespace PLScene;
namespace PLVolume {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNClipPrimitiveBox)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNClipPrimitiveBox::SNClipPrimitiveBox() :
	AABBMin(this),
	AABBMax(this)
{
	// Overwritten PLScene::SceneNode variables
	SetAABoundingBox(AABoundingBox(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.5f, 0.5f, 0.5f)));
}

/**
*  @brief
*    Destructor
*/
SNClipPrimitiveBox::~SNClipPrimitiveBox()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLScene::SceneNode functions           ]
//[-------------------------------------------------------]
void SNClipPrimitiveBox::DrawDebug(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Call base implementation
	SNClipPrimitive::DrawDebug(cRenderer, pVisNode);

	// Draw the box visualization?
	if (pVisNode && !(GetDebugFlags() & DebugNoVisualization)) {
		// Get the 'scene node space' bounding box?
		const AABoundingBox &cAABB = GetAABoundingBox();

		// Setup render states
		// -> Lookout! Enable depth buffer else we will see both transparent box sides which is quite confusing
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::ZEnable,      true);
		cRenderer.SetRenderState(RenderState::ZWriteEnable, true);
		cRenderer.SetRenderState(RenderState::BlendEnable,  true);

		// Invert clipping?
		const bool bInvertClipping = (GetFlags() & InvertClipping) != 0;

		// View side allowing to see the clipped part *camera outside the clipping primitive*
		// -> Negative
		cRenderer.SetRenderState(RenderState::CullMode, Cull::CCW);
		cRenderer.GetDrawHelpers().DrawBox(bInvertClipping ? DebugColorPositive.Get() : DebugColorNegative.Get(), cAABB.vMin, cAABB.vMax, pVisNode->GetWorldViewProjectionMatrix());

		// View side allowing to see the non-clipped rest *camera inside the clipping primitive*
		// -> Positive
		cRenderer.SetRenderState(RenderState::CullMode, Cull::CW);
		cRenderer.GetDrawHelpers().DrawBox(bInvertClipping ? DebugColorNegative.Get() : DebugColorPositive.Get(), cAABB.vMin, cAABB.vMax, pVisNode->GetWorldViewProjectionMatrix());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume
