/*********************************************************\
 *  File: ScriptManager.inl                              *
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


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns a list of the names of the supported script languages
*/
inline const Array<String> &ScriptManager::GetScriptLanguages()
{
	RegisterClasses();
	return m_lstScriptLanguages;
}

/**
*  @brief
*/
inline String ScriptManager::GetScriptLanguageByExtension(const String &sExtension)
{
	RegisterClasses();
	return m_mapScriptLanguagesByExtension.Get(sExtension);
}

/**
*  @brief
*    Checks whether or not a given script language is supported
*/
inline bool ScriptManager::IsSupported(const String &sScriptLanguage)
{
	RegisterClasses();
	return (m_mapScriptLanguages.Get(sScriptLanguage) != nullptr);
}

/**
*  @brief
*    Returns a list of all script binding instances
*/
inline const Array<ScriptBinding*> &ScriptManager::GetScriptBindings()
{
	RegisterClasses();
	return m_lstScriptBindings;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Register a class
*/
inline void ScriptManager::OnClassLoaded(const Class *pClass)
{
	// Just put the new class on the queue - because we can't assume that this class is or can be initialized
	// already, we can't even expect "IsDerivedFrom" to work, so, just REALLY note this class in here!
	m_lstNewClasses.Add(pClass);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
