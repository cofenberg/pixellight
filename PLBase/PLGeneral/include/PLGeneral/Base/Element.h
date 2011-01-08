/*********************************************************\
 *  File: Element.h                                      *
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


#ifndef __PLGENERAL_ELEMENT_H__
#define __PLGENERAL_ELEMENT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/String/String.h"
#include "PLGeneral/Container/Array.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class AType> class ElementHandler;
template <class AType> class ElementManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Element template
*/
template <class AType> class Element {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ElementManager<AType>;
	friend class ElementHandler<AType>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Element name to set
		*  @param[in] pManager
		*    Element manager using this element, can be a null pointer
		*/
		Element(const String &sName = "", ElementManager<AType> *pManager = nullptr);

		/**
		*  @brief
		*    Returns the element manager using this element
		*
		*  @return
		*    Element manager using this element or a null pointer
		*/
		ElementManager<AType> *GetManager() const;

		/**
		*  @brief
		*   Returns the unique element name
		*
		*  @return
		*    Unique element name
		*
		*  @note
		*    - Because within a element manager a element is managed using
		*      it's name, this element name MUST be unique!
		*/
		String GetName() const;

		/**
		*  @brief
		*    Returns whether the element is protected or not
		*
		*  @return
		*    'true' if the element is protected, else 'false'
		*
		*  @note
		*    - Protected element are only removed if their manager is cleared!
		*/
		bool IsProtected() const;

		/**
		*  @brief
		*    Sets whether the element is protected or not
		*
		*  @param[in] bProtected
		*    Is the element protected?
		*
		*  @see
		*    - IsProtected()
		*/
		void SetProtected(bool bProtected = false);

		/**
		*  @brief
		*    Returns the ID of the element within the resouce manager
		*
		*  @return
		*    ID of the element within the element manager, -1 if there was an error
		*    (maybe this element is not within a element manager)
		*
		*  @note
		*    - The element ID isn't fixed, if you remove some elements from the manager
		*      it's possible that the element ID is changed!
		*/
		int GetID() const;

		//[-------------------------------------------------------]
		//[ Handler functions                                     ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of element handlers
		*
		*  @return
		*    The number of element handlers
		*
		*  @note
		*    - The handlers will be informed if the element was lost
		*/
		uint32 GetNumOfHandlers() const;

		/**
		*  @brief
		*    Returns a element handler
		*
		*  @param[in] nIndex
		*    Index of the element handler to return
		*
		*  @return
		*    The requested element handler, a null pointer on error
		*/
		ElementHandler<AType> *GetHandler(uint32 nIndex) const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destroys the element
		*
		*  @param[in] bProtectedToo
		*    Do also destroy the element if it is protected?
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the element is protected?)
		*
		*  @note
		*    - Whether the element is destroyed within this function or just added for
		*      instance to a kind of 'destruction list' is implementation dependand.
		*/
		virtual bool Delete(bool bProtectedToo = false);

		/**
		*  @brief
		*    Sets the element name
		*
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
		*    - Overload this function if it's for instance not allowed to change the name of the element
		*/
		virtual bool SetName(const String &sName);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    This instance
		*
		*  @note
		*    - Manager, handlers and name are not copied
		*/
		virtual Element<AType> &operator =(const Element<AType> &cSource);


	//[-------------------------------------------------------]
	//[ Private virtual functions                             ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Deletes the element
		*/
		virtual void DeleteElement();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Element();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		ElementManager<AType>			*m_pManager;	/**< Element manager, can be a null pointer */
		String							 m_sName;		/**< Resouce name */
		bool							 m_bProtected;	/**< Is the element protected? */
		Array<ElementHandler<AType>*>	 m_lstHandlers;	/**< Element handler list */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Base/Element.inl"


#endif // __PLGENERAL_ELEMENT_H__
