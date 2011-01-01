/*********************************************************\
 *  File: SNCellPortal.h                                 *
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


#ifndef __PLSCENE_CELLPORTAL_H__
#define __PLSCENE_CELLPORTAL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLScene/Scene/SNPortal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class SCCell;
class SceneNodeHandler;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Cell-portal scene node
*
*  @remarks
*    A cell-portal allows the viewer to look from one into another cell.
*/
class SNCellPortal : public SNPortal {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoSeeThrough  = 1<<10,	/**< It's not possible to 'see through' this cell-portal into the target cell (example usage: closed door) */
			NoPassThrough = 1<<11	/**< It's not possible to 'pass through' this cell-portal into the target cell (example usage: window) */
		};
		pl_enum(EFlags)
			pl_enum_base(SNPortal::EFlags)
			pl_enum_value(NoSeeThrough,		"It's not possible to 'see through' this cell-portal into the target cell (example usage: closed door)")
			pl_enum_value(NoPassThrough,	"It's not possible to 'pass through' this cell-portal into the target cell (example usage: window)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNCellPortal, "PLScene", PLScene::SNPortal, "Cell-portal scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(TargetCell,	PLGeneral::String,		"",	ReadWrite,	GetSet,	"Name of the cell this cell-portal links to (for instance 'Parent.Cell2')",	"")
		// Overwritten SceneNode variables
		pl_attribute(Flags,			pl_flag_type(EFlags),	0,	ReadWrite,	GetSet,	"Flags",																	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetTargetCell() const;
		PLS_API void SetTargetCell(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNCellPortal();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNCellPortal();

		/**
		*  @brief
		*    Returns the cell the cell-portal links to
		*
		*  @return
		*    The cell the cell-portal links to, NULL on error
		*    (maybe there's no node with the cell name or this node is no cell)
		*/
		PLS_API SCCell *GetTargetCellInstance();

		/**
		*  @brief
		*    Returns the warp matrix
		*
		*  @return
		*    The warp matrix
		*
		*  @remarks
		*    The warp matrix transforms from this cell space into target cell space.
		*
		*  @note
		*    - Is updated automatically
		*/
		PLS_API const PLMath::Matrix3x4 &GetWarpMatrix();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Flags which hold ínternal portal information (SNPortal flags extension)
		*/
		enum EInternalPortalFlags {
			// Recalculate
			RecalculateWarpMatrix = 1<<1	/**< Recalculation of warp matrix required */
		};


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the target cell container, position, rotation or scale changed
		*/
		void NotifyCellContainerPositionRotationScale();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerCellContainerPositionRotationScale;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String  m_sTargetCell;	/**< Name of the cell this cell-portal links to (for instance 'Parent.Cell2') */
		PLMath::Matrix3x4  m_mWarp;			/**< This cell space into target cell space */
		SceneNodeHandler  *m_pTargetCell;	/**< Target cell (ALWAYS valid!) */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_CELLPORTAL_H__
