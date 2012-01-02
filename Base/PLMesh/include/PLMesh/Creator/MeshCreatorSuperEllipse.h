/*********************************************************\
 *  File: MeshCreatorSuperEllipse.h                      *
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


#ifndef __PLMESH_MESHCREATOR_SUPERELLIPSE_H__
#define __PLMESH_MESHCREATOR_SUPERELLIPSE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLMesh/Creator/MeshCreator.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMesh {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Super ellipse mesh creator class
*
*  @remarks
*    The super ellipsoid is a versatile primitive that is controlled by two parameters.
*    As special cases it can represent a sphere, square box, and closed cylindrical.
*    It should be noted that there are some numerical issues with both very small or very large
*    values of these parameters. Typically, for safety, they should be in the range of 0.1 to about 5.\n
*
*    Examples: (Power1/Power2)\n
*    1.0/1.0 = sphere\n
*    0.1/1.0 = rounded cylinder\n
*    0.1/0.1 = rounded box\n
*    1.0/0.1 = similar to a rounded box\n
*/
class MeshCreatorSuperEllipse : public MeshCreator {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLMESH_RTTI_EXPORT, MeshCreatorSuperEllipse, "PLMesh", PLMesh::MeshCreator, "Super ellipse mesh creator class")
		// Attributes
		pl_attribute(Power1,	float,				0.5f,					ReadWrite,	DirectValue,	"Control parameter 1",	"")
		pl_attribute(Power2,	float,				0.1f,					ReadWrite,	DirectValue,	"Control parameter 2",	"")
		pl_attribute(Detail,	PLCore::uint32,		10,						ReadWrite,	DirectValue,	"Detail",				"")
		pl_attribute(Offset,	PLMath::Vector3,	PLMath::Vector3::Zero,	ReadWrite,	DirectValue,	"Offset to center",		"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLMESH_API MeshCreatorSuperEllipse();

		/**
		*  @brief
		*    Destructor
		*/
		PLMESH_API virtual ~MeshCreatorSuperEllipse();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal helper function
		*/
		void EvalSuperEllipse(float fT1, float fT2, float fP1, float fP2, PLMath::Vector3 *pV) const;


	//[-------------------------------------------------------]
	//[ Private virtual MeshCreator functions                 ]
	//[-------------------------------------------------------]
	private:
		virtual Mesh *Create(Mesh &cMesh, PLCore::uint32 nLODLevel = 0, bool bStatic = true) const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMesh


#endif // __PLMESH_MESHCREATOR_SUPERELLIPSE_H__
