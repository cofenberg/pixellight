/*********************************************************\
 *  File: XProcessor.cpp                                 *
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
#include "PLDefaultFileFormats/DirectX/XProcessor.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ XNode implementation                                  ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the node type
*/
XNode::EType XNode::GetType() const
{
	return m_nType;
}

/**
*  @brief
*    Returns the next node
*/
XNode *XNode::GetNextNode() const
{
	return m_pcNextNode;
}

//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XNode::XNode(EType nType) :
	m_nType(nType),
	m_pcNextNode(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
XNode::~XNode()
{
	if (m_pcNextNode)
		delete m_pcNextNode;
}


//[-------------------------------------------------------]
//[ XRoot implementation                                  ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XRoot::XRoot() : XNode(Root),
	m_pcFirstNode(nullptr)
{
	// Initialize the statistics
	m_sStatistics.nNumOfMeshes		 = 0;
	m_sStatistics.nNumOfMeshVertices = 0;
	m_sStatistics.nNumOfMeshFaces	 = 0;
	m_sStatistics.bTextureCoords	 = false;
	m_sStatistics.bNormals			 = false;
}

/**
*  @brief
*    Destructor
*/
XRoot::~XRoot()
{
	if (m_pcFirstNode)
		delete m_pcFirstNode;
}

/**
*  @brief
*    Returns the first child node
*/
XNode *XRoot::GetFirstChildNode() const
{
	return m_pcFirstNode;
}

/**
*  @brief
*    Returns the statistics
*/
const XRoot::Statistics &XRoot::GetStatistics() const
{
	return m_sStatistics;
}


//[-------------------------------------------------------]
//[ XReference implementation                             ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XReference::XReference() : XNode(Reference),
	pszName(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
XReference::~XReference()
{
	if (pszName)
		delete [] pszName;
}


//[-------------------------------------------------------]
//[ XHeader implementation                                ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XHeader::XHeader() : XNode(Header)
{
}

/**
*  @brief
*    Destructor
*/
XHeader::~XHeader()
{
}


//[-------------------------------------------------------]
//[ XMaterial implementation                              ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XMaterial::XMaterial() : XNode(Material),
	pszName(nullptr),
	psTextureFilename(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
XMaterial::~XMaterial()
{
	if (pszName)
		delete [] pszName;
	if (psTextureFilename)
		delete psTextureFilename;
}


//[-------------------------------------------------------]
//[ XMesh implementation                                  ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XMesh::XMesh() : XNode(Mesh),
	pszName(nullptr),
	nVertices(0),
	psVertices(nullptr),
	nFaces(0),
	psFaces(nullptr),
	psFaceWraps(nullptr),
	psTextureCoords(nullptr),
	psNormals(nullptr),
	psVertexColors(nullptr),
	psMaterialList(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
XMesh::~XMesh()
{
	if (pszName)
		delete [] pszName;
	if (psVertices)
		delete [] psVertices;
	if (psFaces) {
		XMeshFace *psMeshFace    = psFaces;
		XMeshFace *psMeshFaceEnd = &psFaces[nFaces];
		for (; psMeshFace<psMeshFaceEnd; psMeshFace++)
			delete [] psMeshFace->pnFaceVertexIndices;
		delete [] psFaces;
	}
	if (psFaceWraps) {
		if (psFaceWraps->psFaceWrapValues)
			delete [] psFaceWraps->psFaceWrapValues;
		delete psFaceWraps;
	}
	if (psTextureCoords) {
		if (psTextureCoords->psTextureCoords)
			delete [] psTextureCoords->psTextureCoords;
		delete psTextureCoords;
	}
	if (psNormals) {
		if (psNormals->psNormals)
			delete [] psNormals->psNormals;
		delete psNormals;
	}
	if (psVertexColors) {
		if (psVertexColors->psVertexColors)
			delete [] psVertexColors->psVertexColors;
		delete psVertexColors;
	}
	if (psMaterialList) {
		if (psMaterialList->pnFaceIndexes)
			delete [] psMaterialList->pnFaceIndexes;
		delete psMaterialList;
	}
}


//[-------------------------------------------------------]
//[ XFrame implementation                                 ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the first child node
*/
XNode *XFrame::GetFirstChildNode() const
{
	return m_pcFirstNode;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XFrame::XFrame() : XNode(Frame),
	pszName(nullptr),
	psTransformMatrix(nullptr),
	m_pcFirstNode(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
XFrame::~XFrame()
{
	if (pszName)
		delete [] pszName;
	if (psTransformMatrix)
		delete psTransformMatrix;
}


//[-------------------------------------------------------]
//[ XAnimation implementation                             ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XAnimation::XAnimation() : XNode(Animation)
{
}

/**
*  @brief
*    Destructor
*/
XAnimation::~XAnimation()
{
}


//[-------------------------------------------------------]
//[ XAnimationSet implementation                          ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
XAnimationSet::XAnimationSet() : XNode(AnimationSet)
{
}

/**
*  @brief
*    Destructor
*/
XAnimationSet::~XAnimationSet()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
