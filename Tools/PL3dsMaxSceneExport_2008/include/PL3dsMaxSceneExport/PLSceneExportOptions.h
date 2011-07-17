/*********************************************************\
 *  File: PLSceneExportOptions.h                         *
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


#ifndef __PL_SCENEEXPORTOPTIONS_H__
#define __PL_SCENEEXPORTOPTIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <string>
#include <vector>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PixelLight scene export options
*/
class PLSceneExportOptions {


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		static const int         MaxTexCoords = 4;			/**< Maximum number of texture coordinates (no engine limitation!) */
		static const int         MaxVertexWeights = 8;		/**< Maximum number of vertex weights (no engine limitation!) */
		static const std::string DefaultOptionsFilename;	/**< Default options filename */


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		std::string sFilename;						/**< Scene filename */
		std::string sFilenameOnly;					/**< Scene filename only without the path */
		bool		bRemoveSpaces;					/**< Remove spaces/tabs within names? */
		bool		bCorrectPortals;				/**< Correct portals if required? */
		bool		bOverwriteAmbientColor;			/**< Overwrite ambient color? */
		float		fOverwrittenAmbientColor[3];	/**< Overwritten RGB (0-1) ambient color, only used if 'bOverwriteAmbientColor' is true */
		bool		bAnimationPlayback;				/**< Automatic animation playback? */
		bool		bShowExportedScene;				/**< Show the exported scene after the export? */
		bool		bPublish;						/**< Pack everything together required for 'PLViewer'? */
		std::string sSceneContainer;				/**< Scene container */
		std::string sSceneRenderer;					/**< Scene renderer */
		std::string sViewer;						/**< Viewer */

	// Log
		bool bLog;		/**< Create log file? */
		bool bLogOpen;	/**< Open the log file after the export is done? */
		char nLogFlags;	/**< Log flags */

	// User properties
		bool bUserPropVariables;	/**< Use the variables within the user properties */
		bool bUserPropModifiers;	/**< Use the modifiers within the user properties */

	// Materials
		bool bExportMaterials;			/**< Export materials? */
		bool bCreateMaterials;			/**< Create materials? */
		bool bSmartMaterialParameters;	/**< Smart material parameters? */
		bool bCopyTextures;				/**< Copy textures? */
		bool bPLDirectories;			/**< PL directories? */
		bool bSubDirectories;			/**< Sub directories? */

	// Meshes
		bool bExportMeshes;						/**< Export meshes? */
		int  nTexCoordComponents[MaxTexCoords];	/**< Number of texture coordinate
													 components per texture coordinate layer */
		bool bNormals;							/**< Export vertex normals? */
		bool bTangents;							/**< Export vertex tangents? */
		bool bBinormals;						/**< Export vertex binormals? */

	// Other
		std::vector<std::string*> m_lstSceneContainers;	/**< Scene containers */
		std::vector<std::string*> m_lstSceneRenderers;	/**< Scene renderers */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		PLSceneExportOptions();
		~PLSceneExportOptions();
		void SetDefaultSettings();
		void WriteIntoLog();
		void Load(const std::string &sFilename = DefaultOptionsFilename);
		void Save(const std::string &sFilename = DefaultOptionsFilename);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns an absolut configuration filename
		*
		*  @param[in]  sFilename
		*    Filename to return the absolute version from
		*  @param[out] sAbsFilename
		*    Will receive the resulting absolute filename
		*/
		void GetAbsoluteFilename(const std::string &sFilename, std::string &sAbsFilename) const;

		/**
		*  @brief
		*    Clears all scene containers
		*/
		void ClearSceneContainers();

		/**
		*  @brief
		*    Clears all scene renderers
		*/
		void ClearSceneRenderers();

		/**
		*  @brief
		*    Adds default options if the options are empty (scene renderer and so on)
		*/
		void AddDefaultOptions();

		/**
		*  @brief
		*    Loader implementation for format version 2
		*
		*  @param[in] sFilename
		*    Configuration filename
		*/
		void LoadV2(const std::string &sFilename);

		/**
		*  @brief
		*    Loader implementation for format version 0 or version 1
		*
		*  @param[in] sFilename
		*    Configuration filename
		*/
		void LoadV0orV1(const std::string &sFilename);


};


//[-------------------------------------------------------]
//[ Variables                                             ]
//[-------------------------------------------------------]
extern PLSceneExportOptions g_SEOptions;


#endif // __PL_SCENEEXPORTOPTIONS_H__
