/*********************************************************\
 *  File: SceneLoaderPL.cpp                              *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGeneral/Xml/Xml.h>
#include <PLGeneral/Tools/Stopwatch.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/Log/Log.h>
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneNodeModifier.h"
#include "PLScene/Scene/SceneLoader/SceneLoaderPL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneLoaderPL)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool SceneLoaderPL::Load(SceneContainer &cContainer, File &cFile)
{
	// Load XML document
	XmlDocument cDocument;
	if (cDocument.Load(cFile)) {
		// Get scene element
		const XmlElement *pSceneElement = cDocument.GetFirstChildElement("Scene");
		if (pSceneElement) {
			// Get the format version
			const int nVersion = pSceneElement->GetAttribute("Version").GetInt();

			// Unkown
			if (nVersion > 1) {
				PL_LOG(Error, cDocument.GetValue() + ": " + UnknownFormatVersion)

			// 1 (current)
			} else if (nVersion == 1) {
				return LoadV1(cContainer, *pSceneElement, cFile);

			// ""/0 (same format as 1)
			} else if (nVersion == 0) {
				// [DEPRECATED]
				PL_LOG(Warning, cDocument.GetValue() + ": " + DeprecatedFormatVersion)
				return LoadV1(cContainer, *pSceneElement, cFile);

			// No longer supported format version
			} else if (nVersion >= 0) {
				PL_LOG(Warning, cDocument.GetValue() + ": " + NoLongerSupportedFormatVersion)

			// Invalid format version (negative!)
			} else {
				PL_LOG(Error, cDocument.GetValue() + ": " + InvalidFormatVersion)
			}
		} else {
			PL_LOG(Error, "Can't find 'Scene' element")
		}
	} else {
		PL_LOG(Error, cDocument.GetValue() + ": " + cDocument.GetErrorDesc())
	}

	// Error!
	return false;
}

bool SceneLoaderPL::Save(SceneContainer &cContainer, File &cFile)
{
	return SaveParams(cContainer, cFile, true);
}

bool SceneLoaderPL::SaveParams(SceneContainer &cContainer, File &cFile, bool bNoDefault)
{
	// Start the stopwatch
	Stopwatch cStopwatch;
	cStopwatch.Start();

	// Create XML document
	XmlDocument cDocument;

	// Add declaration
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "", "");
	cDocument.LinkEndChild(*pDeclaration);

	// Initializes the statistics
	SInstance sInstance;
	sInstance.nTotalNumOfContainers = 0;
	sInstance.nTotalNumOfNodes      = 0;
	sInstance.nTotalNumOfModifiers  = 0;

	// Add scene
	XmlElement *pScene = new XmlElement("Scene");
	pScene->SetAttribute("Version", "1");
	cContainer.GetValuesXml(*pScene, bNoDefault ? NoDefault : WithDefault);
	SaveRec(sInstance, cContainer, *pScene, bNoDefault);
	cDocument.LinkEndChild(*pScene);

	// Save scene
	cDocument.Save(cFile);

	// Stop the stopwatch
	cStopwatch.Stop();

	// Show statistics within the log
	PL_LOG(Debug, "\n")
	PL_LOG(Debug, "Scene statistics of '" + cFile.GetUrl().GetNativePath() + '\'')
	PL_LOG(Debug, "Saving time: " + String::Format("%g", cStopwatch.GetSeconds()) + " sec");
	PL_LOG(Debug, String("Total number of containers within the scene: (without the root container itself) ") + int(sInstance.nTotalNumOfContainers))
	PL_LOG(Debug, String("Total number of nodes (without containers) within the scene: ") + int(sInstance.nTotalNumOfNodes))
	PL_LOG(Debug, String("Total number of modifiers within the scene: ") + int(sInstance.nTotalNumOfModifiers))
	PL_LOG(Debug, "\n")

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SceneLoaderPL::SceneLoaderPL() :
	MethodLoad(this),
	MethodSave(this),
	MethodSaveParams(this)
{
}

/**
*  @brief
*    Destructor
*/
SceneLoaderPL::~SceneLoaderPL()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Loader implementation for format version 1
*/
bool SceneLoaderPL::LoadV1(SceneContainer &cContainer, const XmlElement &cSceneElement, File &cFile) const
{
	// Start the stopwatch
	Stopwatch cStopwatch;
	cStopwatch.Start();

	// Get first and last scene row
	uint32 nFirstSceneRow = 0, nLastSceneRow = 0;
	const XmlNode *pNode = cSceneElement.GetFirstChild();
	if (pNode)
		nFirstSceneRow = nLastSceneRow = pNode->GetRow();
	pNode = cSceneElement.GetLastChild();
	while (pNode) {
		nLastSceneRow = pNode->GetRow();
		pNode = pNode->GetLastChild();
	}

	// Setup scene container variables
	String sParameters, sName;
	const XmlAttribute *pAttribute = cSceneElement.GetFirstAttribute();
	while (pAttribute) {
		// Is this the name?
		if (pAttribute->GetName() == "Name")
			sName = pAttribute->GetValue();

		// Add parameter
		sParameters += pAttribute->GetName();
		sParameters += "=\"";
		sParameters += pAttribute->GetValue();
		sParameters += "\" ";

		// Get the next attribute
		pAttribute = pAttribute->GetNext();
	}
	if (sParameters.GetLength())
		cContainer.SetValues(sParameters);

	// Deactivate the container during loading
	const bool bActive = cContainer.IsActive();
	cContainer.SetActive(false);

	// Initializes the statistics
	SInstance sInstance;
	sInstance.pContainer			= &cContainer;
	sInstance.nTotalNumOfContainers = 0;
	sInstance.nTotalNumOfNodes      = 0;
	sInstance.nTotalNumOfModifiers  = 0;

	// Recursive loading
	if (!LoadRec(sInstance, cContainer, cSceneElement, nFirstSceneRow, nLastSceneRow)) {
		PL_LOG(Error, "Error during scene loading!")

		// Error!
		return false;
	}

	// Emit >100% load progress to inform that we're done
	cContainer.EventLoadProgress.Emit(1.1f);

	// Reset container active state
	cContainer.SetActive(bActive);

	// Stop the stopwatch
	cStopwatch.Stop();

	// Show statistics within the log
	PL_LOG(Debug, "\n")
	PL_LOG(Debug, "Scene statistics of '" + cFile.GetUrl().GetNativePath() + '\'')
	PL_LOG(Debug, "Loading time: " + String::Format("%g", cStopwatch.GetSeconds()) + " sec");
	PL_LOG(Debug, String("Total number of containers within the scene: (without the root container itself) ") + int(sInstance.nTotalNumOfContainers))
	PL_LOG(Debug, String("Total number of nodes (without containers) within the scene: ") + int(sInstance.nTotalNumOfNodes))
	PL_LOG(Debug, String("Total number of modifiers within the scene: ") + int(sInstance.nTotalNumOfModifiers))
	PL_LOG(Debug, "\n")

	// Done
	return true;
}

/**
*  @brief
*    Recursive part of the load function
*/
bool SceneLoaderPL::LoadRec(SInstance &sInstance, SceneContainer &cContainer, const XmlElement &cParent, uint32 nFirstSceneRow, uint32 nLastSceneRow) const
{
	// Iterate through all children
	const XmlElement *pElement = cParent.GetFirstChildElement();
	while (pElement) {
		// Emit load progress
		sInstance.pContainer->EventLoadProgress.Emit(float(pElement->GetRow()-nFirstSceneRow)/float(nLastSceneRow-nFirstSceneRow));

		// Check value
		const String sValue = pElement->GetValue();
		if (sValue.GetLength()) {
			// Node
			if (sValue == "Node") {
				// Create scene node
				SceneNode *pSceneNode = LoadNode(sInstance, cContainer, *pElement, false);
				if (pSceneNode) {
					// Add modifiers
					const XmlElement *pModifierElement = pElement->GetFirstChildElement();
					while (pModifierElement) {
						if (pModifierElement->GetValue() == "Modifier")
							LoadModifier(sInstance, *pModifierElement, *pSceneNode);

						// Next modifier, please
						pModifierElement = pModifierElement->GetNextSiblingElement();
					}

					// Update the statistics
					sInstance.nTotalNumOfNodes++;
				}

			// Container
			} else if (sValue == "Container") {
				// Create scene node
				SceneNode *pSceneNode = LoadNode(sInstance, cContainer, *pElement, true);

				// Check whether the scene node is really a scene container
				if (pSceneNode && pSceneNode->IsContainer()) {
					LoadRec(sInstance, (SceneContainer&)*pSceneNode, *pElement, nFirstSceneRow, nLastSceneRow);
				} else {
					// Get scene node class name
					const String sClass = pElement->GetAttribute("Class");

					// Error message
					if (sClass.GetLength())
						PL_LOG(Error, "Node class '" + sClass + "' is NO scene container!")
				}

				// Update the statistics
				sInstance.nTotalNumOfContainers++;

			// Modifier
			} else if (sValue == "Modifier") {
				LoadModifier(sInstance, *pElement, cContainer);
			}
		}

		// Next element, please
		pElement = pElement->GetNextSiblingElement();
	}

	// Done
	return true;
}

/**
*  @brief
*    Loads a scene node and returns it
*/
SceneNode *SceneLoaderPL::LoadNode(SInstance &sInstance, SceneContainer &cContainer, const XmlElement &cNode, bool bContainer) const
{
	// Get scene node class name
	const String sClass = cNode.GetAttribute("Class");
	if (sClass.GetLength()) {
		// Setup variables
		String sParameters, sName;
		const XmlAttribute *pAttribute = cNode.GetFirstAttribute();
		while (pAttribute) {
			// Is this the name?
			if (pAttribute->GetName() == "Name")
				sName = pAttribute->GetValue();

			// Add parameter
			sParameters += pAttribute->GetName();
			sParameters += "=\"";
			sParameters += pAttribute->GetValue();
			sParameters += "\" ";

			// Get the next attribute
			pAttribute = pAttribute->GetNext();
		}

		// Create the scene node and return it
		SceneNode *pSceneNode = cContainer.Create(sClass, sName, sParameters);
		if (!pSceneNode) {
			// Write an error into the log
			PL_LOG(Error, cNode.GetValue() + " at row " + cNode.GetRow() + " column " + cNode.GetColumn() + " has an unknown class name! ('" + sClass + "')")

			// We're unable to create the scene node, so let's create an 'unkown'-dummy
			pSceneNode = cContainer.Create(bContainer ? "PLScene::SCUnknown" : "PLScene::SNUnknown", sName);
		}

		// Return the scene node
		return pSceneNode;
	} else {
		// Write an error into the log
		PL_LOG(Error, cNode.GetValue() + " at row " + cNode.GetRow() + " column " + cNode.GetColumn() + " has no class name!")
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Loads a scene node modifier and returns it
*/
SceneNodeModifier *SceneLoaderPL::LoadModifier(SInstance &sInstance, const XmlElement &cNode, SceneNode &cSceneNode) const
{
	// Get scene node modifier class name
	const String sClass = cNode.GetAttribute("Class");
	if (sClass.GetLength()) {
		// Setup variables
		String sParameters;
		const XmlAttribute *pAttribute = cNode.GetFirstAttribute();
		while (pAttribute) {
			// Add parameter
			sParameters += pAttribute->GetName();
			sParameters += "=\"";
			sParameters += pAttribute->GetValue();
			sParameters += "\" ";

			// Get the next attribute
			pAttribute = pAttribute->GetNext();
		}

		// Update the statistics
		sInstance.nTotalNumOfModifiers++;

		// Add the scene node modifier and return it
		SceneNodeModifier *pSceneNodeModifier = cSceneNode.AddModifier(sClass, sParameters);
		if (!pSceneNodeModifier) {
			// Write an error into the log
			PL_LOG(Error, cNode.GetValue() + " at row " + cNode.GetRow() + ", column " + cNode.GetColumn()+ " has an unknown class name! ('" + sClass + "')")

			// We're unable to add the scene node modifier, so let's create an 'unkown'-dummy
			pSceneNodeModifier = cSceneNode.AddModifier("PLScene::SNMUnknown");
		}

		// Return the scene node modifier
		return pSceneNodeModifier;
	} else {
		// Write an error into the log
		PL_LOG(Error, cNode.GetValue() + " at row " + cNode.GetRow() + ", column " + cNode.GetColumn()+ " has no class name!")
	}

	// Error!
	return NULL;
}

/**
*  @brief
*    Recursive part of the save function
*/
bool SceneLoaderPL::SaveRec(SInstance &sInstance, const SceneContainer &cContainer, XmlElement &cParent, bool bNoDefault) const
{
	// Add modifiers
	SaveModifiers(sInstance, cParent, cContainer, bNoDefault);

	// Loop through all nodes
	for (uint32 i=0; i<cContainer.GetNumOfElements(); i++) {
		// Get scene node
		const SceneNode *pSceneNode = cContainer.Get(i);

		// Valid and save this scene node?
		if (pSceneNode && !(pSceneNode->GetFlags() & SceneNode::Automatic)) {
			// Is this a container?
			if (pSceneNode->IsContainer()) {
				XmlElement *pNode = new XmlElement("Container");
				pNode->SetAttribute("Class", pSceneNode->GetClass()->GetClassName());
				pSceneNode->GetValuesXml(*pNode, bNoDefault ? NoDefault : WithDefault);
				SaveRec(sInstance, *((const SceneContainer*)pSceneNode), *pNode);
				cParent.LinkEndChild(*pNode);

				// Update the statistics
				sInstance.nTotalNumOfContainers++;
			} else {
				XmlElement *pNode = new XmlElement("Node");
				pNode->SetAttribute("Class", pSceneNode->GetClass()->GetClassName());
				pSceneNode->GetValuesXml(*pNode, bNoDefault ? NoDefault : WithDefault);
				SaveModifiers(sInstance, *pNode, *pSceneNode, bNoDefault);
				cParent.LinkEndChild(*pNode);

				// Update the statistics
				sInstance.nTotalNumOfNodes++;
			}
		}
	}

	// Done
	return true;
}

/**
*  @brief
*    Modifiers part of the save function
*/
bool SceneLoaderPL::SaveModifiers(SInstance &sInstance, XmlElement &cParent, const SceneNode &cSceneNode, bool bNoDefault) const
{
	// Save all modifiers of this scene node
	for (uint32 i=0; i<cSceneNode.GetNumOfModifiers(); i++) {
		// Get the modifier
		const SceneNodeModifier *pModifier = cSceneNode.GetModifier("", i);

		// Valid and save this scene node modifier?
		if (pModifier && !(pModifier->GetFlags() & SceneNodeModifier::Automatic)) {
			// Save
			XmlElement *pModifierElement = new XmlElement("Modifier");
			pModifierElement->SetAttribute("Class", ((Object*)pModifier)->GetClass()->GetClassName());
			((Object*)pModifier)->GetValuesXml(*pModifierElement, bNoDefault ? NoDefault : WithDefault);
			cParent.LinkEndChild(*pModifierElement);

			// Update the statistics
			sInstance.nTotalNumOfModifiers++;
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
