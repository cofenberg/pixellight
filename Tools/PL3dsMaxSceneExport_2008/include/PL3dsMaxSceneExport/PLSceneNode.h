/*********************************************************\
 *  File: PLSceneNode.h                                  *
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


#ifndef __PL_SCENENODE_H__
#define __PL_SCENENODE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <max.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class PLScene;
class IGameNode;
class PLSceneContainer;
namespace PLCore {
	class Chunk;
	class String;
	class XmlElement;
}


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract exported PixelLight scene node
*
*  @remarks
*    The transform, bounding box etc. are in world space because for instance at the time
*    the node is 'created' the container it's in may not have the final position, bounding box
*    and so on. The data is made relative internally before it's saved.
*/
class PLSceneNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLScene;
	friend class PLSceneCell;
	friend class PLSceneContainer;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node type
		*/
		enum EType {
			TypeContainer  = 0,	/**< SNContainer */
			TypeScene      = 1,	/**< SNContainer - the scene root */
			TypeCell       = 2,	/**< SCCell */
			TypeCellPortal = 3,	/**< SNCellPortal */
			TypeAntiPortal = 4,	/**< SNAntiPortal */
			TypeCamera     = 5,	/**< SNCamera */
			TypeLight      = 6,	/**< SNSpotLight */
			TypeObject     = 7,	/**< SNMesh */
			TypeSpline     = 8,	/**< Path */
			TypeHelper     = 9,	/**< Helper node type */
			TypeUnknown    = 10	/**< Unknown node type */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the root scene container
		*
		*  @return
		*    The root scene container, can be a reference to this node if this is the root :)
		*/
		PLScene &GetScene() const;

		/**
		*  @brief
		*    Returns the container this node is in
		*
		*  @return
		*    The container this node is in, a null pointer if this is the root container of the scene
		*/
		PLSceneContainer *GetContainer() const;

		/**
		*  @brief
		*    Returns the 3ds Max node this scene node represents
		*
		*  @return
		*    The 3ds Max node this scene node represents, a null pointer if there's no such 3ds Max node
		*    (true for this types: TypeScene, TypeContainer, TypeCell)
		*/
		INode *GetMaxNode() const;

		/**
		*  @brief
		*    Returns the IGame node this scene node represents
		*
		*  @return
		*    The IGame node this scene node represents, a null pointer if there's no such IGame node
		*    (true for this types: TypeScene, TypeContainer, TypeCell)
		*/
		IGameNode *GetIGameNode() const;

		/**
		*  @brief
		*    Returns the type of the scene node
		*
		*  @return
		*    The type of the scene node
		*/
		EType GetType() const;

		/**
		*  @brief
		*    Returns the name of this scene node which is normally a substring of the given 3ds Max node
		*
		*  @return
		*    The name of this scene node
		*/
		const std::string &GetName() const;

		/**
		*  @brief
		*    Returns the PixelLight class name of this scene node
		*
		*  @return
		*    The PixelLight class name of this scene node (can be empty)
		*/
		const std::string &GetClassName() const;

		/**
		*  @brief
		*    Adds a flag
		*
		*  @param[in] sFlag
		*    Flag to add
		*/
		void AddFlag(const std::string &sFlag);

		/**
		*  @brief
		*    Returns the world space bounding box of the scene node
		*
		*  @return
		*    The world space bounding box of the scene node
		*/
		const Box3 &GetBoundingBox() const;

		/**
		*  @brief
		*    Is the rotation of this node flipped?
		*
		*  @return
		*    'true' if the rotation of this node is flipped, else 'false'
		*
		*  @remarks
		*    If this is a 'target spot', 'target camera' or 'target directional light' we have to flip the rotation...
		*/
		bool IsRotationFlipped();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pContainer
		*    Container this node is in, a null pointer if this is the root container of the scene
		*  @param[in] pIGameNode
		*    IGame node this scene node represents, can be a null pointer
		*  @param[in] sName
		*    Name of this scene node
		*  @param[in] nType
		*    Scene node type
		*  @param[in] sClassName
		*    PixelLight class name of this scene node
		*/
		PLSceneNode(PLSceneContainer *pContainer, IGameNode *pIGameNode, const std::string &sName, EType nType, const std::string &sClassName);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLSceneNode();

		/**
		*  @brief
		*    Writes the scene node position, rotation, scale, bounding box and flags into a file
		*
		*  @param[in] cSceneElement
		*    Node XML element to insert into
		*/
		void WriteToFilePosRotScaleBoxFlags(PLCore::XmlElement &cNodeElement) const;

		/**
		*  @brief
		*    Writes the flexible scene node variables
		*
		*  @param[in] cSceneElement
		*    Node XML element to insert into
		*/
		void WriteVariables(PLCore::XmlElement &cNodeElement) const;

		/**
		*  @brief
		*    Writes the scene node modifiers
		*
		*  @param[in] cSceneElement
		*    Scene XML element to insert into
		*  @param[in] sApplicationDrive
		*    Application drive
		*  @param[in] sApplicationDir
		*    Application directory
		*/
		void WriteModifiers(PLCore::XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir);

		/**
		*  @brief
		*    Writes a target rotation scene node modifier
		*
		*  @param[in] cSceneElement
		*    Scene XML element to insert into
		*  @param[in] cTarget
		*    3ds Max target node
		*  @param[in] bFlip
		*    Flip look at direction?
		*/
		void WriteTargetRotationModifier(PLCore::XmlElement &cSceneElement, INode &cTarget, bool bFlip) const;


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Writes the scene node into a file
		*
		*  @param[in] cSceneElement
		*    Scene XML element to insert into
		*  @param[in] sApplicationDrive
		*    Application drive
		*  @param[in] sApplicationDir
		*    Application directory
		*/
		virtual void WriteToFile(PLCore::XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir) = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		Box3 m_cBoundingBox;	/**< World space bounding box */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the position, rotation and scale of the scene node at a given time
		*
		*  @param[out] vPos
		*    Receives the position
		*  @param[out] vRot
		*    Receives the rotation
		*  @param[out] vScale
		*    Receives the scale
		*  @param[in]  nTime
		*    Time
		*/
		void GetPosRotScale(Point3 &vPos, Point3 &vRot, Point3 &vScale, TimeValue nTime = TIME_NegInfinity);

		/**
		*  @brief
		*    Returns the position, rotation and scale of the scene node at a given time
		*
		*  @param[out] vPos
		*    Receives the position
		*  @param[out] qRot
		*    Receives the rotation quaternion
		*  @param[out] vScale
		*    Receives the scale
		*  @param[in]  nTime
		*    Time
		*/
		void GetPosRotScale(Point3 &vPos, Quat &qRot, Point3 &vScale, TimeValue nTime = TIME_NegInfinity);

		/**
		*  @brief
		*    Saves a chunk
		*
		*  @param[in] cChunk
		*    Chunk to save
		*  @param[in] cAbsFilename
		*    Absolute filename of the file to save the chunk into
		*/
		bool SaveChunk(const PLCore::Chunk &cChunk, const PLCore::String &cAbsFilename) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLSceneContainer *m_pContainer;			/**< Container this node is in, a null pointer if this is the root container of the scene */
		IGameNode		 *m_pIGameNode;			/**< IGame node this scene node represents, can be a null pointer */
		std::string		  m_sName;				/**< Name of this scene node */
		EType			  m_nType;				/**< Scene node type */
		std::string		  m_sClassName;			/**< PixelLight class name of this scene node */
		std::string		  m_sFlags;				/**< Flags string */
		Point3			  m_vPos;				/**< World space position */
		Point3			  m_vRot;				/**< World space rotation (in degree) */
		Point3			  m_vScale;				/**< World space scale */
		int				  m_nIsRotationFlipped;	/**< Is the rotation of this node flipped? */


};


#endif // __PL_SCENENODE_H__
