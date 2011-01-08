/*********************************************************\
 *  File: Polygon.h                                      *
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


#ifndef __PLMATH_POLYGON_H__
#define __PLMATH_POLYGON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include "PLMath/Plane.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A polygon is a set of vertices on a same plane. This is only a base class with
*    vertices... to add texture coords etc. to have to derive it!
*/
class Polygon {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Plane/point relation
		*/
		enum ESide {
			Behind     = -1,	/**< Behind the plane (distance < 0) */
			Coinciding =  0,	/**< Lies on the plane (distance = 0) */
			InFront    =  1,	/**< Is in front of the plane (distance > 0) */
			Spanning   =  2		/**< Spans the plane */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLMATH_API Polygon();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Polygon to copy
		*/
		PLMATH_API Polygon(const Polygon &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		PLMATH_API virtual ~Polygon();

		/**
		*  @brief
		*    Returns the plane the polygon is on
		*
		*  @return
		*    Plane the polygon is on
		*/
		PLMATH_API const Plane &GetPlane() const;

		/**
		*  @brief
		*    Computes and returns the plane the polygon is on
		*
		*  @return
		*    Plane the polygon is on
		*
		*  @note
		*    - For the plane calculation the first three vertices are used
		*/
		PLMATH_API const Plane &ComputePlane();

		/**
		*  @brief
		*    Checks whether all vertices are on the polygon plane or not
		*
		*  @return
		*    'true' if all vertices are on the polygon plane, else 'false'
		*/
		PLMATH_API bool CheckVerticesOnPlane() const;

		/**
		*  @brief
		*    Returns a list of all vertices
		*
		*  @return
		*    List of all vertices
		*
		*  @note
		*    - If vertices are changed to should call the ComputePlane()
		*      function to keep the polygon plane up to date!
		*/
		PLMATH_API PLGeneral::Array<Vector3> &GetVertexList();

		/**
		*  @brief
		*    Adds a vertex to the polygon
		*
		*  @param[in] vV
		*    Vertex to add
		*
		*  @return
		*    'true' if all went fine and the vertex was added, else 'false'
		*    (maybe the current last vertex is the same as the given one?)
		*/
		PLMATH_API bool AddVertex(const Vector3 &vV);

		/**
		*  @brief
		*    Splits the polygon
		*
		*  @param[in]  cSplitter
		*    Splitter plane
		*  @param[out] cFrontPolygon
		*    Polygon in front of the plane
		*  @param[out] cBackPolygon
		*    Polygon behind the plane
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLMATH_API bool Split(const Plane &cSplitter, Polygon &cFrontPolygon, Polygon &cBackPolygon);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		PLMATH_API Polygon &operator =(const Polygon &cSource);

		/**
		*  @brief
		*    Calculates the side the polygon is on
		*
		*  @return
		*    Plane side
		*/
		PLMATH_API ESide GetSide(const Plane &cPlane) const;

		/**
		*  @brief
		*    Checks whether the polygon is completly in front of the given plane
		*
		*  @return
		*    'true' if the polygon is completly in front of the given plane, else 'false'
		*/
		PLMATH_API bool IsInFront(const Plane &cPlane) const;

		/**
		*  @brief
		*    Checks whether the polygon is completly behind the given plane
		*
		*  @return
		*    'true' if the polygon is completly behind the given plane, else 'false'
		*/
		PLMATH_API bool IsBehind(const Plane &cPlane) const;

		/**
		*  @brief
		*    Clips the polygon against a plane
		*
		*  @param[in] cPlane
		*    Plane to clip this polygon against
		*
		*  @return
		*    The resulting clipped plane
		*/
		PLMATH_API Polygon Clip(const Plane &cPlane) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::Array<Vector3> m_lstVertices;	/**< The vertices (xyz) */
		Plane					  m_cPlane;			/**< Plane the polygon is on */


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Initializes the data of the splitted polygon
		*
		*  @param[out] cPolygon
		*    Polygon which should be initialized
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLMATH_API virtual bool CustomInit(Polygon &cPolygon);

		/**
		*  @brief
		*    Adds data to a polygon
		*
		*  @param[out] cPolygon
		*    Polygon the data should be added
		*  @param[in]  nID
		*    Current data ID
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Is called by Split() to get an custom split behaviour... a
		*      derived polygon could e.g. also have texture coordinates to be split or added!
		*/
		PLMATH_API virtual bool CustomAdd(Polygon &cPolygon, PLGeneral::uint32 nID);

		/**
		*  @brief
		*    Splits the polygon using the custom function
		*
		*  @param[out] cFrontPolygon
		*    Polygon in front of the plane
		*  @param[out] cBackPolygon
		*    Polygon behind the plane
		*  @param[in]  nID
		*    Current data ID
		*  @param[in]  fDistance
		*    Distance from nID-1 to the splitter plane intersection point
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @see
		*    - CustomAdd()
		*/
		PLMATH_API virtual bool CustomSplit(Polygon &cFrontPolygon, Polygon &cBackPolygon,
											PLGeneral::uint32 nID, float fDistance);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath


#endif // __PLMATH_POLYGON_H__
