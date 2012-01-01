/*********************************************************\
 *  File: PLSceneSpline.cpp                              *
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
#include <PLCore/Xml/Xml.h>
#include <IGame/IGame.h>
#include <splshape.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneSpline.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneSpline::PLSceneSpline(PLSceneContainer &cContainer, IGameNode &cIGameNode, const std::string &sName) :
	PLSceneNode(&cContainer, &cIGameNode, sName, TypeSpline, "")
{
}

/**
*  @brief
*    Destructor
*/
PLSceneSpline::~PLSceneSpline()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneNode functions                 ]
//[-------------------------------------------------------]
void PLSceneSpline::WriteToFile(XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir)
{
	// Do NOT save it as scene node, it's just a 'resource'

	// Get path filename
	const std::string sFilename = sApplicationDrive + sApplicationDir + PLTools::GetResourceFilename(PLTools::ResourcePath, GetName() + ".path");

	// Get the IGame spline object of the given IGame node
	IGameObject *pIGameObject = GetIGameNode()->GetIGameObject();
	if (pIGameObject) {
		// Check the type of the IGame object
		if (pIGameObject->GetIGameType() == IGameObject::IGAME_SPLINE && pIGameObject->InitializeData()) {
			IGameSpline &cIGameSpline = *static_cast<IGameSpline*>(pIGameObject);
			if (cIGameSpline.GetNumberOfSplines () > 0) {
				// We only support spline 0
				IGameSpline3D *pIGameSpline3D = cIGameSpline.GetIGameSpline3D(0);
				if (pIGameSpline3D) {
					// Get the local transform matrix
					GMatrix mTransform = cIGameSpline.GetIGameObjectTM();

					// Get the 3ds Max shape object
					ShapeObject *pMaxShapeObject = static_cast<ShapeObject*>(pIGameObject->GetMaxObject()->ConvertToType(TIME_PosInfinity, Class_ID(GENERIC_SHAPE_CLASS_ID, 0)));
					if (pMaxShapeObject != nullptr && pMaxShapeObject->NumberOfCurves() == cIGameSpline.GetNumberOfSplines()) {
						// Create XML document
						XmlDocument cDocument;

						// Add declaration
						XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "ISO-8859-1", "");
						cDocument.LinkEndChild(*pDeclaration);

						// Add path
						XmlElement *pPathElement = new XmlElement("Path");

						// Setup attributes
						pPathElement->SetAttribute("Version", "1");
						pPathElement->SetAttribute("Closed",  String::Format("%d", pMaxShapeObject->CurveClosed(0, 0)));

						// Add all nodes
						for (int nKnot=0; nKnot<pIGameSpline3D->GetIGameKnotCount(); nKnot++) {
							IGameKnot *pIGameKnot = pIGameSpline3D->GetIGameKnot(nKnot);
							if (pIGameKnot) {
								// Get knot point in object space (although it is not documented it looks like object space...)
								Point3 cPoint = pIGameKnot->GetKnotPoint();

								// We really need to flip the coordinates to OpenGL style, IGame is not doing this automatically...
								cPoint = PLTools::Convert3dsMaxVectorToOpenGLVector(cPoint);

								// Transform to world space
								cPoint = cPoint*mTransform;

								// If there's a parent container, make the position of this scene node relative to it
								PLSceneContainer *pContainer = GetContainer();
								if (pContainer)
									cPoint -= pContainer->GetWorldSpaceCenter();

								// Add node
								XmlElement *pNodeElement = new XmlElement("Node");
								pNodeElement->SetAttribute("Name",     String::Format("%d",       nKnot));
								pNodeElement->SetAttribute("Position", String::Format("%f %f %f", cPoint.x, cPoint.y, cPoint.z));

								// Link general element
								pPathElement->LinkEndChild(*pNodeElement);
							}
						}

						// Link material element
						cDocument.LinkEndChild(*pPathElement);

						// Save settings
						if (cDocument.Save(sFilename.c_str()))
							g_pLog->LogFLine(PLLog::Hint, "Created '%s'", sFilename.c_str());
						else
							g_pLog->LogFLine(PLLog::Error, "Can't create '%s'!", sFilename.c_str());
					}
				}
			}
		} else {
			g_pLog->LogFLine(PLLog::Error, "%s: IGame object is no known spline object!", GetIGameNode()->GetName());
		}

		// Release the IGame object
		GetIGameNode()->ReleaseIGameObject();
	} else {
		g_pLog->LogFLine(PLLog::Error, "%s: IGame node has no IGame object!", GetIGameNode()->GetName());
	}
}
