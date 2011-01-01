/*********************************************************\
 *  File: Resource.h                                     *
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


#ifndef __PLCORE_RESOURCE_H__
#define __PLCORE_RESOURCE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/Array.h>
#include "PLCore/Tools/Loadable.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class AType> class ResourceHandler;
template <class AType> class ResourceManager;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Resource template
*/
template <class AType> class Resource : public Loadable {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ResourceManager<AType>;
	friend class ResourceHandler<AType>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Resource name to set
		*  @param[in] pManager
		*    Resource manager using this resource, can be NULL
		*/
		Resource(const PLGeneral::String &sName = "", ResourceManager<AType> *pManager = NULL);

		/**
		*  @brief
		*    Returns the resource manager using this resource
		*
		*  @return
		*    Resource manager using this resource or NULL
		*/
		ResourceManager<AType> *GetManager() const;

		/**
		*  @brief
		*   Returns the unique resource name
		*
		*  @return
		*    Unique resource name
		*
		*  @note
		*    - Because within a resource manager a resource is managed using
		*      it's name, this resource name MUST be unique!
		*/
		PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Returns whether the resource is protected or not
		*
		*  @return
		*    'true' if the resource is protected, else 'false'
		*
		*  @note
		*    - Protected resource are only removed if their manager is cleared!
		*/
		bool IsProtected() const;

		/**
		*  @brief
		*    Sets whether the resource is protected or not
		*
		*  @param[in] bProtected
		*    Is the resource protected?
		*
		*  @see
		*    - IsProtected()
		*/
		void SetProtected(bool bProtected = false);

		/**
		*  @brief
		*    Returns the ID of the resource within the resouce manager
		*
		*  @return
		*    ID of the resource within the resource manager, -1 if there was an error
		*    (maybe this resource is not within a resource manager)
		*
		*  @note
		*    - The resource ID isn't fixed, if you remove some resources from the manager
		*      it's possible that the resource ID is changed!
		*/
		int GetID() const;

		//[-------------------------------------------------------]
		//[ Handler functions                                     ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Returns the number of resource handlers
		*
		*  @return
		*    The number of resource handlers
		*
		*  @note
		*    - The handlers will be informed if the resource was lost
		*/
		PLGeneral::uint32 GetNumOfHandlers() const;

		/**
		*  @brief
		*    Returns a resource handler
		*
		*  @param[in] nIndex
		*    Index of the resource handler to return
		*
		*  @return
		*    The requested resource handler, NULL on error
		*/
		ResourceHandler<AType> *GetHandler(PLGeneral::uint32 nIndex) const;


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destroys the resource
		*
		*  @param[in] bProtectedToo
		*    Do also destroy the resource if it is protected?
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the resource is protected?)
		*
		*  @note
		*    - Whether the resource is destroyed within this function or just added for
		*      instance to a kind of 'destruction list' is implementation dependand.
		*/
		virtual bool Delete(bool bProtectedToo = false);

		/**
		*  @brief
		*    Sets the resource name
		*
		*  @param[in] sName
		*    New resource name
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe the name is already used)
		*
		*  @see
		*    - GetName()
		*
		*  @note
		*    - Overload this function if it's for instance not allowed to change the name of the resource
		*/
		virtual bool SetName(const PLGeneral::String &sName);

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
		virtual Resource<AType> &operator =(const Resource<AType> &cSource);


	//[-------------------------------------------------------]
	//[ Private virtual functions                             ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Deletes the resource
		*/
		virtual void DeleteResource();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Resource();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		ResourceManager<AType>						*m_pManager;		/**< Resource manager, can be NULL */
		PLGeneral::String							 m_sName;			/**< Resouce name */
		bool										 m_bProtected;		/**< Is the resource protected? */
		PLGeneral::Array<ResourceHandler<AType>*>	 m_lstHandlers;		/**< Resource handler list */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Tools/Resource.inl"


#endif // __PLCORE_RESOURCE_H__
