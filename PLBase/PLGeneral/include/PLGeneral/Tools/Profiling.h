/*********************************************************\
 *  File: Profiling.h                                    *
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


#ifndef __PLGENERAL_PROFILING_H__
#define __PLGENERAL_PROFILING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Base/Element.h"
#include "PLGeneral/Base/Singleton.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
class Profiling;
PLGENERAL_TEMPLATE template class PLGENERAL_API Singleton<Profiling>;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Profiling group element
*/
class ProfileGroupElement : public Element<ProfileGroupElement> {


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
		*    Element manager using this element, can be NULL
		*/
		PLGENERAL_API ProfileGroupElement(const String &sName = "", ElementManager<ProfileGroupElement> *pManager = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~ProfileGroupElement();

		/**
		*  @brief
		*    Returns the text of the element
		*
		*  @return
		*    Text of the element
		*/
		PLGENERAL_API String GetText() const;

		/**
		*  @brief
		*    Sets the element text
		*
		*  @param[in] sText
		*    Text to be set
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGENERAL_API bool SetText(const String &sText);

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
		PLGENERAL_API ProfileGroupElement &operator =(const ProfileGroupElement &cSource);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		ProfileGroupElement(const ProfileGroupElement &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String m_sText;	/**< Text to be shown */


};

/**
*  @brief
*    Profiling group
*/
class ProfileGroup : public Element<ProfileGroup>, public ElementManager<ProfileGroupElement> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Profiling;


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
		*    Element manager using this element, can be NULL
		*/
		PLGENERAL_API ProfileGroup(const String &sName = "", ElementManager<ProfileGroup> *pManager = NULL);

		/**
		*  @brief
		*    Destructor
		*/
		PLGENERAL_API virtual ~ProfileGroup();

		/**
		*  @brief
		*    Returns the text of the element group
		*
		*  @return
		*    Text of the element group
		*/
		PLGENERAL_API String GetText() const;

		/**
		*  @brief
		*    Sets the element group text
		*
		*  @param[in] sText
		*    Text to be set
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLGENERAL_API bool SetText(const String &sText);

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
		PLGENERAL_API ProfileGroup &operator =(const ProfileGroup &cSource);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		ProfileGroup(const ProfileGroup &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String m_sText;	/**< Text to be shown */


	//[-------------------------------------------------------]
	//[ Private virtual ElementManager functions              ]
	//[-------------------------------------------------------]
	private:
		virtual ProfileGroupElement *CreateElement(const String &sName);


};

/**
*  @brief
*    PixelLight profiling system
*
*  @remarks
*    The PL API profiling tool is extreme useful to acquire information about certain code
*    parts and their performance. If the profiling is activated with Profiling::GetInstance()->SetActive()
*    it displays you information like current FPS, triangle count, number of scene nodes, scene
*    update time etc. With this information you are able to find out were your performance is
*    burned. The profiling information are subdivided in groups like general, scene, textures
*    etc. containing elements were you could ’browse’ through using offered functions like
*    Profiling::GetInstance()->SelectNextGroup().
*    By default the PL console offers all required commands to handle the profiling tool in a
*    comfortable way therefore there’s no real need to use the profiling browse functions offered
*    by the profiling interface. :)\n
*
*    Adding own groups and elements:\n
*    The profiling information could be expand with own information you maybe want to add
*    to inspect the runtime behavior of certain codes. In fact that’s much easier as it may
*    sound first... in real it’s only ONE function called Profiling::GetInstance()->Set() you need to
*    use to customize the PL profiling tool!!\n
*    Example:\n
*    // Add profiling information\n
*    Profiling::GetInstance()->Set("MyProfilingGroup", "Name: " + sName);\n
*    Profiling::GetInstance()->Set("MyProfilingGroup", String("Current level: ") + nLevel);\n
*    This will add the defined elements to the own profiling group ’MyProfilingGroup’.
*    If this group doesn’t exist yet it’s created automatically, therefore you done have to be
*    interested in the stuff behind all! If you want to do more that only the described above it’s
*    still possible because you have FULL access to all required to remove groups etc. (because
*    the profiling class is derived from ElementManager)
*
*  @note
*    - You can manipulate each element by hand, but it's recommended
*      to use the helper functions provided by the profiling system
*/
class Profiling : public ElementManager<ProfileGroup>, public Singleton<Profiling> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Singleton<Profiling>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether the profiling system is active or not
		*
		*  @return
		*    'true' if the profiling system is active, else 'false'
		*
		*  @note
		*    - If the profiling system is active the current profile group
		*      information will be shown automatically
		*/
		PLGENERAL_API bool IsActive() const;

		/**
		*  @brief
		*    Sets whether the profiling system is active or not
		*
		*  @param[in] bActive
		*    Should the profiling system be active?
		*/
		PLGENERAL_API void SetActive(bool bActive = false);

		/**
		*  @brief
		*    Returns the name of the current selected profile group
		*
		*  @return
		*    Name of the current selected profile group
		*/
		PLGENERAL_API String GetSelectedGroup() const;

		/**
		*  @brief
		*    Selects a profile group
		*
		*  @param[in] sName
		*    Name of the profile group which should be the current one
		*    If "" general profile information are shown.
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (maybe there's no group with this name??)
		*/
		PLGENERAL_API bool SelectGroup(const String &sName = "");

		/**
		*  @brief
		*    Selects the next profile group
		*
		*  @return
		*    Name of the current selected profile group
		*/
		PLGENERAL_API String SelectNextGroup();

		/**
		*  @brief
		*    Selects the previous profile group
		*
		*  @return
		*    Name of the current selected profile group
		*/
		PLGENERAL_API String SelectPreviousGroup();

		/**
		*  @brief
		*    Sets the element text
		*
		*  @param[in] sGroup
		*    Group name
		*  @param[in] sElement
		*    Element name
		*  @param[in] sText
		*    Text to be set
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*    (maybe the profiling is deactivated??)
		*
		*  @note
		*    - The group/element is created automatically
		*    - If the profiling system is currently deactivated this
		*      function makes nothing
		*/
		PLGENERAL_API bool Set(const String &sGroup, const String &sElement, const String &sText);

		/**
		*  @brief
		*    Returns the element text
		*
		*  @param[in] sGroup
		*    Group name
		*  @param[in] sElement
		*    Element name
		*
		*  @return
		*    The text of the element, empty if there was an error
		*/
		PLGENERAL_API String GetText(const String &sGroup, const String &sElement) const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		Profiling();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Profiling(const Profiling &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Profiling();

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
		Profiling &operator =(const Profiling &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool   m_bActive;		/**< Is the profiling system active? */
		String m_sGroupName;	/**< Name of the current selected profile group */


	//[-------------------------------------------------------]
	//[ Private virtual ElementManager functions              ]
	//[-------------------------------------------------------]
	private:
		virtual ProfileGroup *CreateElement(const String &sName);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


#endif // __PLGENERAL_PROFILING_H__
