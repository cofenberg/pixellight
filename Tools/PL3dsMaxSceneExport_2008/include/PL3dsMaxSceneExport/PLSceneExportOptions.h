/*********************************************************\
 *  File: PLSceneExportOptions.h                         *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PL_SCENEEXPORTOPTIONS_H__
#define __PL_SCENEEXPORTOPTIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <vector>
#include <PLCore/String/String.h>


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
		static const int			MaxTexCoords = 4;		/**< Maximum number of texture coordinates (no engine limitation!) */
		static const int			MaxVertexWeights = 8;	/**< Maximum number of vertex weights (no engine limitation!) */
		static const PLCore::String DefaultOptionsFilename;	/**< Default options filename */


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		PLCore::String sFilename;					/**< Scene filename */
		PLCore::String sFilenameOnly;				/**< Scene filename only without the path */
		bool		   bRemoveSpaces;				/**< Remove spaces/tabs within names? */
		bool		   bCorrectPortals;				/**< Correct portals if required? */
		bool		   bPLDirectories;				/**< PL directories? */
		bool		   bSubdirectories;				/**< Subdirectories? (do only use this option in case 'bPLDirectories' is 'true') */
		bool		   bOverwriteAmbientColor;		/**< Overwrite ambient color? */
		float		   fOverwrittenAmbientColor[3];	/**< Overwritten RGB (0-1) ambient color, only used if 'bOverwriteAmbientColor' is true */
		bool		   bAnimationPlayback;			/**< Automatic animation playback? */
		bool		   bShowExportedScene;			/**< Show the exported scene after the export? */
		bool		   bPublish;					/**< Pack everything together required for 'PLViewer'? */
		PLCore::String sSceneContainer;				/**< Scene container */
		PLCore::String sSceneRenderer;				/**< Scene renderer */
		PLCore::String sViewer;						/**< Viewer */

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

	// Meshes
		bool bExportMeshes;						/**< Export meshes? */
		int  nTexCoordComponents[MaxTexCoords];	/**< Number of texture coordinate
													 components per texture coordinate layer */
		bool bNormals;							/**< Export vertex normals? */
		bool bTangents;							/**< Export vertex tangents? */
		bool bBinormals;						/**< Export vertex binormals? */

	// Other
		std::vector<PLCore::String*> m_lstSceneContainers;	/**< Scene containers */
		std::vector<PLCore::String*> m_lstSceneRenderers;	/**< Scene renderers */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		PLSceneExportOptions();
		~PLSceneExportOptions();
		void SetDefaultSettings();
		void WriteIntoLog();
		void Load(const PLCore::String &sFilename = DefaultOptionsFilename);
		void Save(const PLCore::String &sFilename = DefaultOptionsFilename);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns an absolute configuration filename
		*
		*  @param[in]  sFilename
		*    Filename to return the absolute version from
		*  @param[out] sAbsFilename
		*    Will receive the resulting absolute filename
		*/
		void GetAbsoluteFilename(const PLCore::String &sFilename, PLCore::String &sAbsFilename) const;

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
		void LoadV2(const PLCore::String &sFilename);

		/**
		*  @brief
		*    Loader implementation for format version 0 or version 1
		*
		*  @param[in] sFilename
		*    Configuration filename
		*/
		void LoadV0orV1(const PLCore::String &sFilename);


};


//[-------------------------------------------------------]
//[ Variables                                             ]
//[-------------------------------------------------------]
extern PLSceneExportOptions g_SEOptions;


#endif // __PL_SCENEEXPORTOPTIONS_H__
