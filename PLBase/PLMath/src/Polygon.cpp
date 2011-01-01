/*********************************************************\
 *  File: Polygon.cpp                                    *
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
#include "PLMath/Polygon.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Polygon::Polygon()
{
}

/**
*  @brief
*    Copy constructor
*/
Polygon::Polygon(const Polygon &cSource) :
	m_lstVertices(cSource.m_lstVertices),
	m_cPlane(cSource.m_cPlane)
{
}

/**
*  @brief
*    Destructor
*/
Polygon::~Polygon()
{
}

/**
*  @brief
*    Returns the plane the polygon is on
*/
const Plane &Polygon::GetPlane() const
{
	return m_cPlane;
}

/**
*  @brief
*    Computes and returns the plane the polygon is on
*/
const Plane &Polygon::ComputePlane()
{
	const Vector3 &vV1 = m_lstVertices[0];
	const Vector3 &vV2 = m_lstVertices[1];
	const Vector3 &vV3 = m_lstVertices[2];
	if (&vV1 == &Array<Vector3>::Null || &vV2 == &Array<Vector3>::Null || &vV3 == &Array<Vector3>::Null)
		return m_cPlane; // ARGH, there are not enough vertices to create a plane!!?

	// Compute the plane using the first 3 vertices
	return m_cPlane.ComputeND(vV1, vV2, vV3);
}

/**
*  @brief
*    Checks whether all vertices are on the polygon plane or not
*/
bool Polygon::CheckVerticesOnPlane() const
{
	for (uint32 i=0; i<m_lstVertices.GetNumOfElements(); i++) {
		if (Math::Abs(m_cPlane.GetDistance(m_lstVertices[i])) > Math::Epsilon)
			return false; // Not all vertices are on the polygon
	}

	// All vertices are on the polygon
	return true;
}

/**
*  @brief
*    Returns a list of all vertices
*/
Array<Vector3> &Polygon::GetVertexList()
{
	return m_lstVertices;
}

/**
*  @brief
*    Adds a vertex to the polygon
*/
bool Polygon::AddVertex(const Vector3 &vV)
{
	// Check whether we need to add this vertex
	if (m_lstVertices.GetNumOfElements()) {
		const Vector3 &vVOther = m_lstVertices[m_lstVertices.GetNumOfElements()-1];
		if (Math::Abs(vV.x-vVOther.x) < Math::Epsilon &&
			Math::Abs(vV.y-vVOther.y) < Math::Epsilon &&
			Math::Abs(vV.z-vVOther.z) < Math::Epsilon)
			return false; // Error - we do not need to add this vertex!
	}

	// Add the vertex
	m_lstVertices.Add(vV);

	// Done
	return true;
}

/**
*  @brief
*    Splits the polygon
*/
bool Polygon::Split(const Plane &cSplitter, Polygon &cFrontPolygon, Polygon &cBackPolygon)
{
	// Init splitted polygons
	cFrontPolygon.GetVertexList().Clear();
	 cBackPolygon.GetVertexList().Clear();

	// Call custom init function
	CustomInit(cFrontPolygon);
	CustomInit(cBackPolygon);

	// Loop through vertices
	if (m_lstVertices.GetNumOfElements()) {
		Vector3 *pV1		 = &m_lstVertices[m_lstVertices.GetNumOfElements()-1];
		float    fV1Distance = cSplitter.GetDistance(*pV1);
		for (uint32 i=0; i<m_lstVertices.GetNumOfElements(); i++) {
			Vector3 *pV2		 = &m_lstVertices[i];
			float    fV2Distance = cSplitter.GetDistance(*pV2);
			Vector3  vDelta		 = (*pV2)-(*pV1);
			float    fDistance   = fV1Distance/(Math::Abs(fV1Distance)+Math::Abs(fV2Distance));

			if (fV2Distance > Math::Epsilon) { // In front of splitter plane
				if (fV1Distance < Math::Epsilon) { // Line is splitted
					Vector3 vRes = (*pV1)+vDelta*(-fDistance);

					cFrontPolygon.GetVertexList().Add(vRes);
					 cBackPolygon.GetVertexList().Add(vRes);

					// Call custom split function
					CustomSplit(cFrontPolygon, cBackPolygon, i, -fDistance);
				}
				cFrontPolygon.GetVertexList().Add(*pV2);

				// Call custom add function
				CustomAdd(cFrontPolygon, i);
			} else if (fV2Distance < Math::Epsilon) { // Behind splitter plane
				if (fV1Distance > Math::Epsilon) { // Line is splitted
					Vector3 vRes = (*pV1)+vDelta*fDistance;

					cFrontPolygon.GetVertexList().Add(vRes);
					 cBackPolygon.GetVertexList().Add(vRes);

					// Call custom split function
					CustomSplit(cFrontPolygon, cBackPolygon, i, fDistance);
				}
				cBackPolygon.GetVertexList().Add(*pV2);

				// Call custom add function
				CustomAdd(cBackPolygon, i);
			} else {
				cFrontPolygon.GetVertexList().Add(*pV2);
				 cBackPolygon.GetVertexList().Add(*pV2);

				// Call custom add functions
				CustomAdd(cFrontPolygon, i);
				CustomAdd(cBackPolygon,  i);
			}

			pV1			= pV2;
			fV1Distance = fV2Distance;
		}
	}

	// Compute planes
	cFrontPolygon.ComputePlane();
	 cBackPolygon.ComputePlane();

	// Done
	return true;
}

/**
*  @brief
*    Copy operator
*/
Polygon &Polygon::operator =(const Polygon &cSource)
{
	// Copy data
	m_lstVertices = cSource.m_lstVertices;
	m_cPlane	  = cSource.m_cPlane;

	// Return this
	return *this;
}

/**
*  @brief
*    Calculates the side the polygon is on
*/
Polygon::ESide Polygon::GetSide(const Plane &cPlane) const
{
	uint32 nNumInFront = 0, nNumBehind = 0;

	for (uint32 i=0; i<m_lstVertices.GetNumOfElements(); i++) {
		float fDistance = cPlane.GetDistance(m_lstVertices[i]);
			 if (fDistance >  0.00001) nNumInFront++;
		else if (fDistance < -0.00001) nNumBehind++;
	}

	// Return plane side the polygon is on
	if (nNumInFront && !nNumBehind)  return InFront;
	if (!nNumInFront && nNumBehind)  return Behind;
	if (!nNumInFront && !nNumBehind) return Coinciding;
	else							 return Spanning;
}

/**
*  @brief
*    Checks whether the polygon is completly in front of the given plane
*/
bool Polygon::IsInFront(const Plane &cPlane) const
{
	for (uint32 i=0; i<m_lstVertices.GetNumOfElements(); i++) {
		if (cPlane.GetSide(m_lstVertices[i]) != Plane::InFront)
			return false; // Not in front
	}

	// In front of the given plane
	return true;
}

/**
*  @brief
*    Checks whether the polygon is completly behind the given plane
*/
bool Polygon::IsBehind(const Plane &cPlane) const
{
	for (uint32 i=0; i<m_lstVertices.GetNumOfElements(); i++) {
		if (cPlane.GetSide(m_lstVertices[i]) != Plane::Behind)
			return false; // Not behind
	}

	// Behind the given plane
	return true;
}

/**
*  @brief
*    Clips the polygon against a plane
*/
Polygon Polygon::Clip(const Plane &cPlane) const
{
	uint32 nNumOfVertices = m_lstVertices.GetNumOfElements();
	Polygon cClipped;

	// Loop through all vertices of this polygon
	for (uint32 i=0; i<nNumOfVertices; i++) {
		// The 2 vertices of an edge
		const Vector3 &vA = m_lstVertices[i];
		const Vector3 &vB = m_lstVertices[(i+1) % nNumOfVertices];

		// Check on which side of the plane the vertices are on
		Plane::ESide nSideA = cPlane.GetSide(vA);
		Plane::ESide nSideB = cPlane.GetSide(vB);

		// Clip
		if (nSideA == Plane::InFront || nSideA == Plane::Coinciding) {
			cClipped.AddVertex(vA);
			if (nSideB == Plane::Behind) cClipped.AddVertex(cPlane.ClipEdge(vA, vB));
		} else if (nSideB == Plane::InFront) {
			cClipped.AddVertex(cPlane.ClipEdge(vA, vB));
			cClipped.AddVertex(vB);
		}

	}

	// Return the clipped polygon
	return cClipped;
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initializes the data of the splitted polygon
*/
bool Polygon::CustomInit(Polygon &cPolygon)
{
	// Done
	return true;
}

/**
*  @brief
*    Adds data to a polygon
*/
bool Polygon::CustomAdd(Polygon &cPolygon, uint32 nID)
{
	// Done
	return true;
}

/**
*  @brief
*    Splits the polygon using the custom function
*/
bool Polygon::CustomSplit(Polygon &cFrontPolygon, Polygon &cBackPolygon, uint32 nID, float fDistance)
{
	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
