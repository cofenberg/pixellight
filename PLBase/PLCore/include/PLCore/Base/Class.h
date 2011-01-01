/*********************************************************\
 *  File: Class.h                                        *
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


#ifndef __PLCORE_CLASS_H__
#define __PLCORE_CLASS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Container/HashMap.h>
#include <PLGeneral/Container/List.h>
#include <PLGeneral/String/String.h>
#include "PLCore/PLCore.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Module;
class Object;
class DynParams;
class MemberDesc;
class VarDesc;
class FuncDesc;
class EventDesc;
class EventHandlerDesc;
class ConstructorDesc;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Description and interface for classes
*/
class Class {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class MemberDesc;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nModuleID
		*    ID of owner module
		*  @param[in] sName
		*    Name
		*  @param[in] sDescription
		*    Description
		*  @param[in] sNamespace
		*    Namespace
		*  @param[in] sBaseClass
		*    Base class
		*/
		PLCORE_API Class(PLGeneral::uint32 nModuleID, const PLGeneral::String &sName, const PLGeneral::String &sDescription, const PLGeneral::String &sNamespace, const PLGeneral::String &sBaseClass);

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~Class();

		/**
		*  @brief
		*    Get module the class belongs to
		*
		*  @return
		*    Module (always valid)
		*/
		PLCORE_API const Module *GetModule() const;

		/**
		*  @brief
		*    Get full class name (with namespace)
		*
		*  @return
		*    Name of class and namespace
		*/
		PLCORE_API PLGeneral::String GetClassName() const;

		/**
		*  @brief
		*    Get full name of base class (with namespace)
		*
		*  @return
		*    Name of base class and namespace
		*/
		PLCORE_API PLGeneral::String GetBaseClassName() const;

		/**
		*  @brief
		*    Get class name (without namespace)
		*
		*  @return
		*    Name of class
		*/
		PLCORE_API PLGeneral::String GetName() const;

		/**
		*  @brief
		*    Get class description
		*
		*  @return
		*    Description
		*/
		PLCORE_API PLGeneral::String GetDescription() const;

		/**
		*  @brief
		*    Get namespace
		*
		*  @return
		*    Namespace
		*/
		PLCORE_API PLGeneral::String GetNamespace() const;

		/**
		*  @brief
		*    Get base class
		*
		*  @return
		*    Pointer to base class (can be NULL)
		*/
		PLCORE_API const Class *GetBaseClass() const;

		/**
		*  @brief
		*    Check if class is derived from another class
		*
		*  @param[in] cBaseClass
		*    Base class
		*
		*  @return
		*    'true' if class is derived from given base class, else 'false'
		*/
		PLCORE_API bool IsDerivedFrom(const Class &cBaseClass) const;

		/**
		*  @brief
		*    Check if class is derived from another class
		*
		*  @param[in] sBaseClass
		*    Base class name (with namespace)
		*
		*  @return
		*    'true' if class is derived from given base class, else 'false'
		*/
		PLCORE_API bool IsDerivedFrom(const PLGeneral::String &sBaseClass) const;

		/**
		*  @brief
		*    Get derived classes
		*
		*  @return
		*    List of derived classes
		*
		*  @remarks
		*    This method always returns all sub-classes of a class.
		*    If you want to search for classes with more specific search criteria,
		*    have a look at ClassManager::GetClasses().
		*/
		PLCORE_API const PLGeneral::List<const Class*> GetDerivedClasses() const;

		/**
		*  @brief
		*    Get properties
		*
		*  @return
		*    Hash map of properties (name -> value)
		*
		*  @remarks
		*    A property is a name/value pair of strings, that can be assigned to a class. Use this to
		*    transport additional information for your class, e.g.
		*      "PluginType"  -> "Widget"
		*      "FileFormats" -> "avi mpg mp4"
		*/
		PLCORE_API const PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> &GetProperties() const;

		/**
		*  @brief
		*    Get attributes
		*
		*  @return
		*    List of attribute descriptors
		*/
		PLCORE_API const PLGeneral::List<VarDesc*> &GetAttributes() const;

		/**
		*  @brief
		*    Get attribute
		*
		*  @param[in] sName
		*    Attribute name
		*
		*  @return
		*    Attribute descriptor (can be NULL, if no member with that name could be found)
		*/
		PLCORE_API const VarDesc *GetAttribute(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Get methods
		*
		*  @return
		*    List of method descriptors
		*/
		PLCORE_API const PLGeneral::List<FuncDesc*> &GetMethods() const;

		/**
		*  @brief
		*    Get method
		*
		*  @param[in] sName
		*    Method name
		*
		*  @return
		*    Method descriptor (can be NULL, if no member with that name could be found)
		*/
		PLCORE_API const FuncDesc *GetMethod(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Get signals
		*
		*  @return
		*    List of signal descriptors
		*/
		PLCORE_API const PLGeneral::List<EventDesc*> &GetSignals() const;

		/**
		*  @brief
		*    Get signal
		*
		*  @param[in] sName
		*    Signal name
		*
		*  @return
		*    Signal descriptor (can be NULL, if no member with that name could be found)
		*/
		PLCORE_API const EventDesc *GetSignal(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Get slot
		*
		*  @return
		*    List of slot descriptors
		*/
		PLCORE_API const PLGeneral::List<EventHandlerDesc*> &GetSlots() const;

		/**
		*  @brief
		*    Get slot
		*
		*  @param[in] sName
		*    Slot name
		*
		*  @return
		*    Slot descriptor (can be NULL, if no member with that name could be found)
		*/
		PLCORE_API const EventHandlerDesc *GetSlot(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Check if class has any constructors
		*
		*  @return
		*    'true' if class has at least one constructor, else 'false'
		*/
		PLCORE_API bool HasConstructor() const;

		/**
		*  @brief
		*    Check if class has a default constructors
		*
		*  @return
		*    'true' if class has a default constructor, else 'false'
		*/
		PLCORE_API bool HasDefaultConstructor() const;

		/**
		*  @brief
		*    Get constructors
		*
		*  @return
		*    List of constructor descriptors
		*/
		PLCORE_API const PLGeneral::List<ConstructorDesc*> &GetConstructors() const;

		/**
		*  @brief
		*    Get constructor
		*
		*  @param[in] sName
		*    Constructor name
		*
		*  @return
		*    Constructor descriptor (can be NULL, if no member with that name could be found)
		*/
		PLCORE_API const ConstructorDesc *GetConstructor(const PLGeneral::String &sName) const;

		/**
		*  @brief
		*    Create object
		*
		*  @return
		*    Pointer to created object (can be NULL)
		*
		*  @remarks
		*    This function will call the default constructor of the class.
		*    If the class has no default constructor, the function will fail and return NULL.
		*/
		PLCORE_API Object *Create() const;

		/**
		*  @brief
		*    Create object
		*
		*  @param[in] cParams
		*    Constructor parameters
		*
		*  @return
		*    Pointer to created object (can be NULL)
		*
		*  @remarks
		*    This function will search for a constructor that matches the signature of the given parameters.
		*    If no such contructor can be found, the function will fail and return NULL.
		*/
		PLCORE_API Object *Create(const DynParams &cParams) const;

		/**
		*  @brief
		*    Create object
		*
		*  @param[in] sName
		*    Constructor name
		*  @param[in] cParams
		*    Constructor parameters
		*
		*  @return
		*    Pointer to created object (can be NULL)
		*
		*  @remarks
		*    This function will search for a constructor with the specified name. If no such contructor can be found, or
		*    the given parameters do not match the signature of the constructor, the function will fail and return NULL.
		*/
		PLCORE_API Object *Create(const PLGeneral::String &sName, const DynParams &cParams) const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Add member
		*
		*  @param[in] pMemberDesc
		*    Member descriptor
		*/
		PLCORE_API void AddMember(MemberDesc *pMemberDesc);

		/**
		*  @brief
		*    Add property
		*
		*  @param[in] sName
		*    Property name
		*  @param[in] sValue
		*    Property value
		*/
		PLCORE_API void AddProperty(const PLGeneral::String &sName, const PLGeneral::String &sValue);

		/**
		*  @brief
		*    Initialize class and class members
		*
		*  @remarks
		*    This function is called automatically when it is necessary, e.g. the first time
		*    any members are being accessed. It will search for the base class of the class
		*    and initialize all members. If later a class is changed (e.g. a new member is
		*    registered at one of the base classes), that class and all derived classes will
		*    destroy their information and must be initialized again.
		*/
		PLCORE_API void InitClass() const;

		/**
		*  @brief
		*    De-Initialize class and class members
		*
		*  @remarks
		*    This function destroyes all data about the class and it's members. See
		*    InitClass() for more information about why this is necessary and when.
		*/
		PLCORE_API void DeInitClass() const;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		// Class information
		PLGeneral::String												 m_sName;				/**< Name of class */
		PLGeneral::String												 m_sNamespace;			/**< Namespace of class */
		PLGeneral::String												 m_sClassName;			/**< Name of class (with namespace) */
		PLGeneral::String												 m_sDescription;		/**< Description of class */
		PLGeneral::String												 m_sBaseClass;			/**< Name of base class (with namespace) */

		// Own data (does not include data from base classes)
		PLGeneral::List<MemberDesc*>									 m_lstOwnMembers;		/**< List of members */
		PLGeneral::HashMap<PLGeneral::String, PLGeneral::String>		 m_mapOwnProperties;	/**< Hash map of properties (name -> value) */

		// Runtime data
		mutable PLGeneral::uint32										 m_nModuleID;			/**< ID of owner module */
		mutable bool													 m_bInitialized;		/**< Is the class initialized? */
		mutable const Class												*m_pBaseClass;			/**< Pointer to base class */

		// Member lists (also including the members from base classes)
		mutable PLGeneral::HashMap<PLGeneral::String, PLGeneral::String> m_mapProperties;		/**< Hash map of properties (name -> value) */
		mutable PLGeneral::HashMap<PLGeneral::String, MemberDesc*>		 m_mapMembers;			/**< Hash map of names -> members */
		mutable PLGeneral::List<VarDesc*>								 m_lstAttributes;		/**< List of attributes */
		mutable PLGeneral::List<FuncDesc*>								 m_lstMethods;			/**< List of methods */
		mutable PLGeneral::List<EventDesc*>								 m_lstSignals;			/**< List of signals */
		mutable PLGeneral::List<EventHandlerDesc*>						 m_lstSlots;			/**< List of slots */
		mutable PLGeneral::List<ConstructorDesc*>						 m_lstConstructors;		/**< List of constructors */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CLASS_H__
