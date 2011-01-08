/*********************************************************\
 *  File: SNText.h                                       *
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


#ifndef __PLSCENE_SCENENODE_TEXT_H__
#define __PLSCENE_SCENENODE_TEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract text scene node
*/
class SNText : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoCenter = 1<<10	/**< Do not center the text */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(NoCenter,	"Do not center the text")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNText, "PLScene", PLScene::SceneNode, "Abstract text scene node")
		pl_attribute(Text,		PLGeneral::String,		"",											ReadWrite,	GetSet,			"Text do draw",																						"")
		pl_attribute(Color,		PLGraphics::Color4,		PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Text color",																						"")
		pl_attribute(Font,		PLGeneral::String,		"",											ReadWrite,	GetSet,			"The used font, if empty the default font is used",													"")
		pl_attribute(FontSize,	PLGeneral::uint32,		0,											ReadWrite,	GetSet,			"The font size, if null the default font size is used - use scene node scale for dynamic scale",	"Max='100'")
		// Overwritten SceneNode variables
		pl_attribute(Flags,		pl_flag_type(EFlags),	0,											ReadWrite,	GetSet,			"Flags",																							"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual PLGeneral::String GetText() const;
		PLS_API virtual void SetText(const PLGeneral::String &sValue);
		PLS_API virtual PLGeneral::String GetFont() const;
		PLS_API virtual void SetFont(const PLGeneral::String &sValue);
		PLS_API virtual PLGeneral::uint32 GetFontSize() const;
		PLS_API virtual void SetFontSize(PLGeneral::uint32 nValue);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNText();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNText();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sText;		/**< Text do draw */
		PLGeneral::String m_sFont;		/**< The used font, if empty the default font is used */
		PLGeneral::uint32 m_nFontSize;	/**< The font size, if null the default font size is used - use scene node scale for dynamic scale */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_TEXT_H__
