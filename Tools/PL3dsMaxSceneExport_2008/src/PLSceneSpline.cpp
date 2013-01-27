/*********************************************************\
 *  File: PLSceneSpline.cpp                              *
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
PLSceneSpline::PLSceneSpline(PLSceneContainer &cContainer, IGameNode &cIGameNode, const String &sName) :
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
void PLSceneSpline::WriteToFile(XmlElement &cSceneElement, const String &sApplicationDrive, const String &sApplicationDir)
{
	// Do NOT save it as scene node, it's just a 'resource'

	// Get path filename
	const String sFilename = sApplicationDrive + sApplicationDir + PLTools::GetResourceFilename(PLTools::ResourcePath, GetName() + ".path");

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
						if (cDocument.Save(sFilename))
							g_pLog->LogFLine(PLLog::Hint, "Created '%s'", sFilename.GetASCII());
						else
							g_pLog->LogFLine(PLLog::Error, "Can't create '%s'!", sFilename.GetASCII());
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
