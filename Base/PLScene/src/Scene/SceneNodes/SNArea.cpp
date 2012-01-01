/*********************************************************\
 *  File: SNArea.cpp                                     *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Log/Log.h>
#include <PLCore/String/Tokenizer.h>
#include "PLScene/Scene/SceneNodes/SNArea.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNArea)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNArea::GetBox() const
{
	return m_sBox;
}

void SNArea::SetBox(const String &sValue)
{
	if (m_sBox != sValue) {
		m_sBox = sValue;
		CheckBox();
	}
}

String SNArea::GetPlanes() const
{
	return m_sPlanes;
}

void SNArea::SetPlanes(const String &sValue)
{
	if (m_sPlanes != sValue) {
		m_sPlanes = sValue;
		CheckPlanes();
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNArea::SNArea() :
	Box(this),
	Planes(this),
	m_sBox("-0.5 -0.5 -0.5 0.5 0.5 0.5")
{
}

/**
*  @brief
*    Destructor
*/
SNArea::~SNArea()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Check if an box should be created
*/
void SNArea::CheckBox()
{
	if (m_sBox.GetLength()) {
		Tokenizer cTokenizer;
		float fBB[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

		// Get box
		cTokenizer.Start(m_sBox);
		for (int i=0; i<6 && cTokenizer.GetNextToken().GetLength(); i++)
			fBB[i] = cTokenizer.GetToken().GetFloat();
		cTokenizer.Stop();

		// Set box
		CreateBox(Vector3(fBB[0], fBB[1], fBB[2]),
				  Vector3(fBB[3], fBB[4], fBB[5]));
	}
}

/**
*  @brief
*    Check if planes should be added to the area
*/
void SNArea::CheckPlanes()
{
	if (m_sPlanes.GetLength()) {
		// Clear old plane set
		Clear();

		// Add planes
		Tokenizer cTokenizer;
		cTokenizer.Start(m_sPlanes);
		for (int i=0; cTokenizer.GetNextToken().GetLength(); i++) {
			Plane *pPlane = Create();
			if (!pPlane)
				break;
			for (int j=0; j<4; j++) {
				pPlane->fVector[j] = cTokenizer.GetToken().GetFloat();
				if (j < 3 && !cTokenizer.GetNextToken().GetLength())
					PL_LOG(Error, GetName() + String::Format(": Area plane %d, parameter %d missed!", i+1, j+1))
			}
		}
		cTokenizer.Stop();
	}
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNode functions                 ]
//[-------------------------------------------------------]
void SNArea::InitFunction()
{
	// Call base implementation
	SceneNode::InitFunction();

	// Check if an box should be created
	CheckBox();

	// Check if planes should be added to the area
	CheckPlanes();
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
