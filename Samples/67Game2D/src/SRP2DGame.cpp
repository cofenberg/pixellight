/*********************************************************\
 *  File: SRP2DGame.cpp                                  *
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
#include <PLCore/Tools/Localization.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/FontManager.h>
#include <PLRenderer/Renderer/SamplerStates.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLRenderer/Texture/TextureManager.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Visibility/SQCull.h>
#include "SNGun.h"
#include "SNBomb.h"
#include "SRP2DGame.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SRP2DGame)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SRP2DGame::SRP2DGame()
{
}

/**
*  @brief
*    Destructor
*/
SRP2DGame::~SRP2DGame()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Draws an image
*/
bool SRP2DGame::DrawImage(Renderer &cRenderer, const String &sName, const Vector2 &vPos, const Vector2 &vSize,
						  const Vector2 &vTextureCoordinate, const Vector2 &vTextureCoordinateSize) const
{
	// Get the texture
	const Texture *pTexture = cRenderer.GetRendererContext().GetTextureManager().LoadResource(sName);
	if (pTexture && pTexture->GetTextureBuffer()) {
		// To get the perfect look, we want to see some pixels - so, do not perform texture filtering!
		SamplerStates cSamplerStates;
		cSamplerStates.Set(Sampler::MagFilter, TextureFiltering::None);
		cSamplerStates.Set(Sampler::MinFilter, TextureFiltering::None);
		cSamplerStates.Set(Sampler::MipFilter, TextureFiltering::None);

		// Draw image
		cRenderer.GetDrawHelpers().DrawImage(*pTexture->GetTextureBuffer(), cSamplerStates, vPos, vSize, Color4::White, 0.5f, vTextureCoordinate, vTextureCoordinateSize);

		// Done
		return true;
	}

	// Error!
	return false;
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneRendererPass functions  ]
//[-------------------------------------------------------]
void SRP2DGame::Draw(Renderer &cRenderer, const SQCull &cCullQuery)
{
	// Set render states
	cRenderer.GetRendererContext().GetEffectManager().Use();
	cRenderer.SetRenderState(RenderState::ZEnable,      false);
	cRenderer.SetRenderState(RenderState::ZWriteEnable, false);

	// Begin 2D mode
	DrawHelpers &cDrawHelpers = cRenderer.GetDrawHelpers();
	cDrawHelpers.Begin2DMode(0, 0, 320, 200);

		// Draw the background
		DrawImage(cRenderer, "Data/Textures/2DGame/Background.png", Vector2::Zero);

		// Get the scene container
		SceneContainer &cSceneContainer = cCullQuery.GetSceneContainer();

		// Draw solid
		for (uint32 i=0; i<cSceneContainer.GetNumOfElements(); i++) {
			SceneNode *pSceneNode = cSceneContainer.GetByIndex(i);
			if (pSceneNode->IsVisible()) {
				// SNProjectile
				if (pSceneNode->IsInstanceOf("SNProjectile")) {
					// Draw the projectile
					DrawImage(cRenderer, "Data/Textures/2DGame/Projectile.png", pSceneNode->GetTransform().GetPosition() - Vector3(3.0f, 3.0f, 0.0f));

				// SNBomb
				} else if (pSceneNode->IsInstanceOf("SNBomb")) {
					// Draw the bomb (original image dimension: 188x18)
					char nFrame = static_cast<SNBomb*>(pSceneNode)->GetFrame();
					DrawImage(cRenderer, "Data/Textures/2DGame/Bomb.png", pSceneNode->GetTransform().GetPosition() - Vector3(8.0f, 8.0f, 0.0f), Vector2(16.0f, 16.0f),
							  Vector2(static_cast<float>(1+nFrame*17)/188.0f, 0.0f), Vector2(16.0f/188.0f, 1.0f));

				// SNUFO
				} else if (pSceneNode->IsInstanceOf("SNUFO")) {
					// Draw the UFO
					DrawImage(cRenderer, "Data/Textures/2DGame/UFO.png", pSceneNode->GetTransform().GetPosition() - Vector3(25.0f, 10.0f, 0.0f));

				// SNGun
				} else if (pSceneNode->IsInstanceOf("SNGun")) {
					// Draw the gun
					char nFrame = static_cast<SNGun*>(pSceneNode)->GetFrame();
					DrawImage(cRenderer, "Data/Textures/2DGame/Gun.png", pSceneNode->GetTransform().GetPosition() - Vector3(18.0f, 7.0f, 0.0f), Vector2(36.0f, 14.0f),
							  Vector2(static_cast<float>(1+nFrame*38)/495.0f, 0.0f), Vector2(36.0f/495.0f, 1.0f));
				}
			}
		}

		// Draw debug - if we want to visualize some debug information :)
		for (uint32 i=0; i<cSceneContainer.GetNumOfElements(); i++) {
			SceneNode *pSceneNode = cSceneContainer.GetByIndex(i);
			if (pSceneNode->IsVisible() && (pSceneNode->GetDebugFlags() & SceneNode::DebugEnabled) && (pSceneNode->GetDrawFunctionFlags() & SceneNode::UseDrawDebug))
				pSceneNode->DrawDebug(cRenderer);
		}

	// End 2D mode
	cDrawHelpers.End2DMode();

	// Get the font
	Font *pFont = reinterpret_cast<Font*>(cRenderer.GetFontManager().GetDefaultFontTexture());
	if (pFont) {
		// Setup render states
		cRenderer.GetRendererContext().GetEffectManager().Use();
		cRenderer.SetRenderState(RenderState::ZEnable,      false);
		cRenderer.SetRenderState(RenderState::ZWriteEnable, false);

		// Begin 2D mode
		cDrawHelpers.Begin2DMode();

			// Draw texts
			cDrawHelpers.DrawText(*pFont, PLT("Keys:"),						 Color4::White, Vector2(0.01f, 0.01f));
			cDrawHelpers.DrawText(*pFont, PLT("a/d = Gun control"),			 Color4::White, Vector2(0.06f, 0.03f));
			cDrawHelpers.DrawText(*pFont, PLT("Space = Start projectile"),   Color4::White, Vector2(0.06f, 0.05f));
			cDrawHelpers.DrawText(*pFont, PLT("r = Restart game"),			 Color4::White, Vector2(0.06f, 0.07f));
			cDrawHelpers.DrawText(*pFont, PLT("p = Toggle post processing"), Color4::White, Vector2(0.06f, 0.09f));

		// End 2D mode
		cDrawHelpers.End2DMode();
	}
}
