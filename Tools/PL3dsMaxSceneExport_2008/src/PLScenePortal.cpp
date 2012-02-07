/*********************************************************\
 *  File: PLScenePortal.cpp                              *
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
#include <IGame/IGame.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLScenePortal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLScenePortal::PLScenePortal(PLSceneContainer &cContainer, IGameNode &cIGameNode, const std::string &sName, EType nType, const std::string &sClassName) :
	PLSceneNode(&cContainer, &cIGameNode, sName, nType, sClassName),
	m_vCenter(0.0f, 0.0f, 0.0f),
	m_vNormal(0.0f, 0.0f, 0.0f)
{
	// Get the IGame mesh object of the given IGame node
	IGameObject *pIGameObject = cIGameNode.GetIGameObject();
	if (pIGameObject) {
		// Check the type of the IGame object
		if (pIGameObject->GetIGameType() == IGameObject::IGAME_MESH) {
			IGameMesh &cIGameMesh = *static_cast<IGameMesh*>(pIGameObject);

			// Initialize the IGame mesh
			if (cIGameMesh.InitializeData()) {
				// Get the number of polygons
				int nNumOfPolys = cIGameMesh.GetNumberOfPolygons();
				if (nNumOfPolys == 1 && cIGameMesh.GetNumberOfFaces()) {
					// Get the portal vertices
					Tab<INT> lstVertices = cIGameMesh.GetPolygonVertices(0);
					int nNumOfVertices = lstVertices.Count();
					if (nNumOfVertices >= 3) {
						m_lstVertices.resize(nNumOfVertices);

						// Get 'world space -> node space' transform matrix. 'IGameMesh.GetVertex()' can
						// give us the vertices directly in object space, but then it can happen that the transform
						// is not correctly and I can't figure out how to fix that. (some kind of mysterious object offset...)
						// So, I request the vertices in 'world space' and then I transform them into 'node space' and all
						// is fine...
						GMatrix mTransform = PLTools::Inverse(cIGameNode.GetWorldTM());

						// Get the portal vertices and center
						for (std::vector<Point3>::size_type i=0; i<static_cast<std::vector<Point3>::size_type>(nNumOfVertices); i++) {
							// Get polygon vertex in 'world space'
							Point3 &vVertex = m_lstVertices[i];
							cIGameMesh.GetVertex(lstVertices[i], vVertex);

							// Sum up the center
							m_vCenter += vVertex;

							// Transform polygon vertex into 'node space'
							vVertex = vVertex*mTransform;
						}

						// Calculate the final center in 'world space'
						m_vCenter /= static_cast<float>(nNumOfVertices);

						// Get the portal normal in 'world space'
						cIGameMesh.GetNormal(0, 0, m_vNormal);
					} else {
						g_pLog->LogFLine(PLLog::Error, "%s: There must be at least 3 vertices within the polygon!", cIGameNode.GetName());
					}
				} else {
					g_pLog->LogFLine(PLLog::Error, "%s: There are '%d' polygons, but a portal is only allowed to have 1 polygon!", cIGameNode.GetName(), nNumOfPolys);
				}
			} else {
				g_pLog->LogFLine(PLLog::Error, "%s: Failed to initialize the IGame mesh!", cIGameNode.GetName());
			}
		} else {
			g_pLog->LogFLine(PLLog::Error, "%s: IGame object is no mesh object!", cIGameNode.GetName());
		}

		// Release the IGame object
		cIGameNode.ReleaseIGameObject();
	} else {
		g_pLog->LogFLine(PLLog::Error, "%s: IGame node has no IGame object!", cIGameNode.GetName());
	}
}

/**
*  @brief
*    Destructor
*/
PLScenePortal::~PLScenePortal()
{
}
