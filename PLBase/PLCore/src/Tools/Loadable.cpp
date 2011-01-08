/*********************************************************\
 *  File: Loadable.cpp                                   *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/File/Url.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/Log/Log.h>
#include "PLCore/Tools/Loader.h"
#include "PLCore/Tools/LoadableType.h"
#include "PLCore/Tools/LoadableManager.h"
#include "PLCore/Tools/Loadable.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
namespace PLCore {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the filename this loadable was given to loaded from
*/
String Loadable::GetFilename() const
{
	return m_sFilename;
}

/**
*  @brief
*    Returns the absolute filename this loadable was loaded from
*/
String Loadable::GetUrl() const
{
	return m_sUrl;
}


//[-------------------------------------------------------]
//[ Public virtual functions                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loads the loadable from a file given by filename
*/
bool Loadable::Load(const String &sFilename, const String &sParams, const String &sMethod)
{
	// Check the given filename
	if (sFilename.GetLength()) {
		// Get file extension
		const String sExtension = Url(sFilename).GetExtension();
		if (sExtension.GetLength()) {
			// Get loadable type
			const LoadableType *pLoadableType = LoadableManager::GetInstance()->GetType(GetLoadableTypeName());
			if (pLoadableType) {
				// Get loader
				Loader *pLoader = pLoadableType->GetLoader(sExtension);
				if (pLoader) {
					if (pLoader->IsInstanceOf(pLoadableType->GetClass())) {
						if (pLoader->CanLoad()) {
							// Open the file
							File cFile;
							if (pLoader->OpenFile(cFile, sFilename, false)) {
								// Because 'm_sAbsFilename' is reset before loading within the Unload()-function,
								// and 'sFilename' can be a reference to this string, we need to duplicate the string!
								const String sFilenameT = String(sFilename);

								// Unload the loadable
								Unload();

								// Get method name
								static const String sLoad = "Load";
								static const String sLoadParams = "LoadParams";
								String sMethodName = sMethod;
								if (!sMethodName.GetLength())
									sMethodName = sParams.GetLength() ? sLoadParams : sLoad;

								// Load the loadable
								const bool bResult = CallLoadable(cFile, *pLoader, sMethodName, sParams);
								if (bResult) {
									// Backup filenames
									m_sFilename	= sFilenameT;
									m_sUrl		= cFile.GetUrl().GetUrl();
								}

								// Done
								return bResult;
							} else PL_LOG(Error, "Can't open the file '" + sFilename + "' to load in the loadable '" + GetLoadableTypeName() + "'!")
						} else PL_LOG(Error, "Can't load the loadable '" + GetLoadableTypeName() + "' from '" + sFilename + "' because loading of this file format is not supported!")
					} else PL_LOG(Error, "Can't load the loadable '" + GetLoadableTypeName() + "' from '" + sFilename + "' because the file format is no valid '" + GetLoadableTypeName() + "' format!")
				} else PL_LOG(Error, "Can't load the loadable '" + GetLoadableTypeName() + "' from '" + sFilename + "' because the file format is not supported!")
			} else PL_LOG(Error, "Can't load '" + sFilename + "' because the loadable type '" + GetLoadableTypeName() + "' is unknown!")
		} else PL_LOG(Error, "Can't load the loadable '" + GetLoadableTypeName() + "' from '" + sFilename + "' because there's no filename extension!")
	} else PL_LOG(Error, "Can't load the loadable '" + GetLoadableTypeName() + "' because there's no given filename!")

	// Error!
	return false;
}

/**
*  @brief
*    Loads the loadable from a file given by a pointer
*/
bool Loadable::Load(File &cFile, const String &sParams, const String &sMethod)
{
	// Check whether file reading is allowed
	if (cFile.IsReadable()) {
		// Get the filename of the given file
		Url	cUrl = cFile.GetUrl();

		// Get file extension
		String sExtension = cUrl.GetExtension();
		if (sExtension.GetLength()) {
			// Get loadable type
			const LoadableType *pLoadableType = LoadableManager::GetInstance()->GetType(GetLoadableTypeName());
			if (pLoadableType) {
				// Get loader
				Loader *pLoader = pLoadableType->GetLoader(sExtension);
				if (pLoader) {
					if (pLoader->IsInstanceOf(pLoadableType->GetClass())) {
						if (pLoader->CanLoad()) {
							// Unload the loadable
							Unload();

							// Get method name
							static const String sLoad = "Load";
							static const String sLoadParams = "LoadParams";
							String sMethodName = sMethod;
							if (!sMethodName.GetLength())
								sMethodName = sParams.GetLength() ? sLoadParams : sLoad;

							// Load the loadable
							bool bResult = CallLoadable(cFile, *pLoader, sMethodName, sParams);
							if (bResult) {
								// Backup filenames
								m_sUrl		= cUrl.GetUrl();
								m_sFilename	= cUrl.GetFilename();
							}

							// Done
							return bResult;
						} else PL_LOG(Error, "Can't load the loadable '" + GetLoadableTypeName() + "' from '" + cUrl.GetNativePath() + "' because loading of this file format is not supported!")
					} else PL_LOG(Error, "Can't load the loadable '" + GetLoadableTypeName() + "' from '" + cUrl.GetNativePath() + "' because the file format is no valid '" + GetLoadableTypeName() + "' format!")
				} else PL_LOG(Error, "Can't load the loadable '" + GetLoadableTypeName() + "' from '" + cUrl.GetNativePath() + "' because the file format is not supported!")
			} else PL_LOG(Error, "Can't load '" + cUrl.GetNativePath() + "' because the loadable type '" + GetLoadableTypeName() + "' is unknown!")
		} else PL_LOG(Error, "Can't load the loadable '" + GetLoadableTypeName() + "' from '" + cUrl.GetNativePath() + "' because there's no filename extension!")
	} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' because the given file is not readable!")

	// Error!
	return false;
}

/**
*  @brief
*    Saves the loadable to a file given by filename
*/
bool Loadable::Save(const String &sFilename, const String &sParams, const String &sMethod)
{
	// Check the given filename
	if (sFilename.GetLength()) {
		// Get file extension
		const Url &cUrl = sFilename;
		String sExtension = cUrl.GetExtension();
		if (sExtension.GetLength()) {
			// Get loadable type
			const LoadableType *pLoadableType = LoadableManager::GetInstance()->GetType(GetLoadableTypeName());
			if (pLoadableType) {
				// Get loader
				Loader *pLoader = pLoadableType->GetLoader(sExtension);
				if (pLoader) {
					if (pLoader->IsInstanceOf(pLoadableType->GetClass())) {
						if (pLoader->CanSave()) {
							// Open the file
							File cFile;
							if (pLoader->OpenFile(cFile, sFilename, true)) {
								// Get method name
								static const String sSave = "Save";
								static const String sSaveParams = "SaveParams";
								String sMethodName = sMethod;
								if (!sMethodName.GetLength())
									sMethodName = sParams.GetLength() ? sSaveParams : sSave;

								// Save
								return CallLoadable(cFile, *pLoader, sMethodName, sParams);
							} else PL_LOG(Error, "Can't open the file '" + sFilename + "' to save the loadable '" + GetLoadableTypeName() + "'!")
						} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' to '" + sFilename + "' because saving of this file format is not supported!")
					} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' to '" + sFilename + "' because the file format is no valid '" + GetLoadableTypeName() + "' format!")
				} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' to '" + sFilename + "' because the file format is not supported!")
			} else PL_LOG(Error, "Can't save '" + sFilename + "' because the loadable type '" + GetLoadableTypeName() + "' is unknown!")
		} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' to '" + sFilename + "' because there's no filename extension!")
	} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' because there's no given filename!")

	// Error!
	return false;
}

/**
*  @brief
*    Saves the loadable to a file given by pointer
*/
bool Loadable::Save(File &cFile, const String &sParams, const String &sMethod)
{
	// Check whether file writing is allowed
	if (cFile.IsWritable()) {
		// Get the filename of the given file
		const Url &cUrl = cFile.GetUrl();

		// Check parameter
		if (cUrl.GetNativePath().GetLength()) {
			// Get file extension
			String sExtension = cUrl.GetExtension();
			if (sExtension.GetLength()) {
				// Get loadable type
				const LoadableType *pLoadableType = LoadableManager::GetInstance()->GetType(GetLoadableTypeName());
				if (pLoadableType) {
					// Get loader
					Loader *pLoader = pLoadableType->GetLoader(sExtension);
					if (pLoader) {
						if (pLoader->IsInstanceOf(pLoadableType->GetClass())) {
							if (pLoader->CanSave()) {
								// Get method name
								static const String sSave = "Save";
								static const String sSaveParams = "SaveParams";
								String sMethodName = sMethod;
								if (!sMethodName.GetLength())
									sMethodName = sParams.GetLength() ? sSaveParams : sSave;

								// Save
								return CallLoadable(cFile, *pLoader, sMethodName, sParams);
							} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' to '" + cUrl.GetNativePath() + "' because saving of this file format is not supported!")
						} else PL_LOG(Error, "Can't save the image to '" + cUrl.GetNativePath() + "' because the file format is no valid '" + GetLoadableTypeName() + "'  format!")
					} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' to '" + cUrl.GetNativePath() + "' because the file format is not supported!")
				} else PL_LOG(Error, "Can't save '" + cUrl.GetNativePath() + "' because the loadable type '" + GetLoadableTypeName() + "' is unknown!")
			} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' to '" + cUrl.GetNativePath() + "' because there's no filename extension!")
		} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' because there's no given filename!")
	} else PL_LOG(Error, "Can't save the loadable '" + GetLoadableTypeName() + "' because the given file is not writable!")

	// Error!
	return false;
}

/**
*  @brief
*    Reloads the loadable
*/
bool Loadable::Reload()
{
	// Any URL set?
	if (m_sUrl.GetLength()) {
		// Backup the current URL in case that it is reset during loading -> because we pass a reference to this
		// string the loading will fail in this situation!
		String sUrl = m_sUrl;

		// Load
		return Load(sUrl);
	}

	// Done
	return true;
}

/**
*  @brief
*    Unloads the loadable
*/
bool Loadable::Unload()
{
	// Reset the filenames
	m_sFilename	= "";
	m_sUrl		= "";

	// Done
	return true;
}

/**
*  @brief
*    Returns the loadable type name
*/
String Loadable::GetLoadableTypeName() const
{
	return "";
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Loadable::Loadable()
{
}

/**
*  @brief
*    Destructor
*/
Loadable::~Loadable()
{
	// Unload the loadable
	Unload();
}


//[-------------------------------------------------------]
//[ Private virtual Loadable functions                    ]
//[-------------------------------------------------------]
bool Loadable::CallLoadable(File &cFile, Loader &cLoader, const String &sMethod, const String &sParams)
{
	if (sParams.GetLength()) {
		cLoader.CallMethod(sMethod, "Param0=\"" + Type<Loadable&>::ConvertToString(*this) + "\" Param1=\"" + Type<File&>::ConvertToString(cFile) + "\" " + sParams);
		return true;
	} else {
		Params<bool, Loadable&, File&> cParams(*this, cFile);
		cLoader.CallMethod(sMethod, cParams);
		return cParams.Return;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore
