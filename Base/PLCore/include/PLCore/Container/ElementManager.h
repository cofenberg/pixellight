/*********************************************************\
 *  File: ElementManager.h                               *
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


#ifndef __PLCORE_ELEMENT_MANAGER_H__
#define __PLCORE_ELEMENT_MANAGER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"
#include "PLCore/Container/Array.h"
#include "PLCore/Container/HashMap.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class AType> class Element;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract element manager template
*/
template <class AType> class ElementManager {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Element<AType>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the name of the manager
		*
		*  @return
		*    Name of the manager
		*
		*  @note
		*    - The manager name has no special usage, it's just for completeness
		*/
		String GetManagerName() const;

		/**
		*  @brief
		*    Sets the name of the manager
		*
		*  @param[in] sName
		*    New manager name
		*
		*  @return
		*    'true' if all went fine else 'false'
		*
		*  @see
		*    - GetManagerName()
		*/
		bool SetManagerName(const String &sName = "");

		/**
		*  @brief
		*   Clear the manager, delete all elements
		*
		*  @param[in] bProtectedToo
		*    Delete protected elements, too?
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool Clear(bool bProtectedToo = true);

		/**
		*  @brief
		*    Creates a new element
		*
		*  @param[in] sName
		*    Element name, if "" an unused name is set automatically
		*
		*  @return
		*    Pointer to the created element, a null pointer if there was an error
		*
		*  @note
		*    - If there's already a element with this name, this element is returned
		*/
		AType *Create(const String &sName = "");

		/**
		*  @brief
		*    Adds a element
		*
		*  @param[in] cElement
		*    Element to add
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (maybe element is already within another manager)
		*/
		bool Add(AType &cElement);

		/**
		*  @brief
		*    Unload a element
		*
		*  @param[in] cElement
		*    Element which should be unloaded
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - Protected elements are NOT unloaded!
		*/
		bool Unload(AType &cElement);

		/**
		*  @brief
		*    Removes a element
		*
		*  @param[in] cElement
		*    Element to remove
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe element is not within the manager)
		*
		*  @note
		*    - This function will only remove the element from the manager, but
		*      NOT deleting it!
		*/
		bool Remove(AType &cElement);

		/**
		*  @brief
		*    Unload unused elements
		*
		*  @return
		*    Number of unloaded elements
		*
		*  @see
		*    - Unload()
		*/
		uint32 UnloadUnused();

		/**
		*  @brief
		*    Returns whether unused element are unloaded automatically or not
		*
		*  @return
		*    'true' if unused elements are unloaded automatically, else 'false'
		*/
		bool GetUnloadUnused() const;

		/**
		*  @brief
		*    Sets whether unused element are unloaded automatically or not
		*
		*  @param[in] bUnloadUnused
		*    Unload unused elements automatically?
		*/
		void SetUnloadUnused(bool bUnloadUnused = false);

		/**
		*  @brief
		*    Get the standard element
		*
		*  @return
		*    The standard element, a null pointer if there's no such element
		*
		*  @note
		*    - There should always be a standard element!
		*    - It is recommended that you protect your standard element
		*/
		AType *GetStandard() const;

		/**
		*  @brief
		*    Set the standard element
		*
		*  @param[in] pElement
		*    Element which should be the standard element, a null pointer to set no such element
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe invalid element)
		*
		*  @see
		*    - GetStandard()
		*/
		bool SetStandard(AType *pElement = nullptr);

		/**
		*  @brief
		*    Returns the number of elements within the manager
		*
		*  @return
		*    Number of elements within the manager
		*/
		uint32 GetNumOfElements() const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Initializes the manager
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Init();

		/**
		*  @brief
		*    De-initializes the manager
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool DeInit();

		/**
		*  @brief
		*    Updates the manager
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		virtual bool Update();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This instance
		*/
		virtual ElementManager<AType> &operator =(const ElementManager<AType> &cSource);

		/**
		*  @brief
		*    Returns the element at the given index
		*
		*  @param[in] nIndex
		*    Index of the element
		*
		*  @return
		*    The corresponding object, a null pointer if there's no match
		*/
		virtual AType *GetByIndex(uint32 nIndex = 0) const;

		/**
		*  @brief
		*    Returns the index of the given element
		*
		*  @param[in] cElement
		*    The element for which the index should be retreived
		*
		*  @return
		*    The index position, <0 on failure (e.g. the element is no member of this manager)
		*/
		virtual int GetIndex(AType &cElement) const;

		/**
		*  @brief
		*    Moves an element within the element list
		*
		*  @param[in] nFromIndex
		*    The index of the element which should be moved
		*  @param[in] nToIndex
		*    The index to which the element should be moved
		*
		*  @note
		*    - This methods assumes, that both index values are within 0 and GetNumOfElements()-1
		*/
		virtual void MoveElement(uint32 nFromIndex, uint32 nToIndex);

		/**
		*  @brief
		*    Returns the element with the given name
		*
		*  @param[in] sName
		*    Element name
		*
		*  @return
		*    The corresponding element, a null pointer if there's no match
		*
		*  @note
		*    - You can overload this function to specialize the behavior. This is done
		*      for instance within SceneContainer to be able to use 'absolute names'
		*      like 'Root.MyScene.MyNode', too.
		*/
		virtual AType *GetByName(const String &sName) const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		ElementManager();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ElementManager();

		/**
		*  @brief
		*    Sets the element name
		*
		*  @param[in] cElement
		*    Element to set the name
		*  @param[in] sName
		*    New element name
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the name is already used)
		*
		*  @see
		*    - GetName()
		*
		*  @note
		*    - You can overload this function if there are 'reserved' names which are NOT
		*      allowed to be used or if special characters are not allowed.
		*/
		bool SetElementName(AType &cElement, const String &sName);


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Creates a new element
		*
		*  @param[in] sName
		*    Element name
		*
		*  @return
		*    Pointer to the created element, a null pointer if there was an error
		*
		*  @note
		*    - This function is used inside the function Create(). If AType is an abstract
		*      class you have to overwrite this function to create an instance of the class.
		*/
		virtual AType *CreateElement(const String &sName = "") = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		String					 m_sManagerName;		/**< Manager name */
		AType					*m_pStandardElement;	/**< Standard element, can be a null pointer */
		bool					 m_bUnloadUnused;		/**< Unload unused resources? */
		Array<AType*>			 m_lstElements;			/**< Element list */
		HashMap<String, AType*>	 m_mapElements;			/**< Element map */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Container/ElementManager.inl"


#endif // __PLCORE_ELEMENT_MANAGER_H__
