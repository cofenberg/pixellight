/*********************************************************\
 *  File: ClassDummy.h                                   *
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


#ifndef __PLCORE_CLASS_DUMMY_H__
#define __PLCORE_CLASS_DUMMY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/ClassImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Dummy 'Class' implementation
*/
class ClassDummy : public ClassImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ClassManager;


	//[-------------------------------------------------------]
	//[ Protected virtual ClassImpl functions                 ]
	//[-------------------------------------------------------]
	protected:
		virtual bool IsDummy() const;
		virtual void InitClass() const;
		virtual void DeInitClass() const;
		virtual const PLGeneral::List<VarDesc*> &GetAttributes() const;
		virtual const VarDesc *GetAttribute(const PLGeneral::String &sName) const;
		virtual const PLGeneral::List<FuncDesc*> &GetMethods() const;
		virtual const FuncDesc *GetMethod(const PLGeneral::String &sName) const;
		virtual const PLGeneral::List<EventDesc*> &GetSignals() const;
		virtual const EventDesc *GetSignal(const PLGeneral::String &sName) const;
		virtual const PLGeneral::List<EventHandlerDesc*> &GetSlots() const;
		virtual const EventHandlerDesc *GetSlot(const PLGeneral::String &sName) const;
		virtual bool HasConstructor() const;
		virtual bool HasDefaultConstructor() const;
		virtual const PLGeneral::List<ConstructorDesc*> &GetConstructors() const;
		virtual const ConstructorDesc *GetConstructor(const PLGeneral::String &sName) const;
		virtual Object *Create() const;
		virtual Object *Create(const DynParams &cParams) const;
		virtual Object *Create(const PLGeneral::String &sName, const DynParams &cParams) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
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
		*  @param[in] bHasConstructor
		*    Class has any constructors?
		*  @param[in] bHasDefaultConstructor
		*    Class has a default constructor?
		*/
		ClassDummy(PLGeneral::uint32 nModuleID, const PLGeneral::String &sName, const PLGeneral::String &sDescription, const PLGeneral::String &sNamespace, const PLGeneral::String &sBaseClass, bool bHasConstructor, bool bHasDefaultConstructor);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~ClassDummy();

		/*
		*  @brief
		*    Requests the real class implementation
		*
		*  @return
		*    The real class implementation if all went fine, else a null pointer
		*
		*  @note
		*    - Please note that it's not valid to use this dummy class implementation after this method was call because it may have been killed!
		*/
		ClassImpl *GetRealClassImpl() const;


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		// Member lists (also including the members from base classes) - static because those are just dummies in here
		static PLGeneral::HashMap<PLGeneral::String, MemberDesc*> m_mapMembers;			/**< Hash map of names -> members */
		static PLGeneral::List<VarDesc*>						  m_lstAttributes;		/**< List of attributes */
		static PLGeneral::List<FuncDesc*>						  m_lstMethods;			/**< List of methods */
		static PLGeneral::List<EventDesc*>						  m_lstSignals;			/**< List of signals */
		static PLGeneral::List<EventHandlerDesc*>				  m_lstSlots;			/**< List of slots */
		static PLGeneral::List<ConstructorDesc*>				  m_lstConstructors;	/**< List of constructors */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bHasConstructor;			/**< Class has any constructors? */
		bool m_bHasDefaultConstructor;	/**< Class has a default constructor? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CLASS_DUMMY_H__
