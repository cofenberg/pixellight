/*********************************************************\
 *  File: SkeletonAniLoaderMd5.h                         *
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


#ifndef __PLDEFAULTFILEFORMATS_DOOM3_SKELETONANILOADER_MD5_H__
#define __PLDEFAULTFILEFORMATS_DOOM3_SKELETONANILOADER_MD5_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMesh/Loader/SkeletonAniLoader.h>


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGeneral {
	class Tokenizer;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Skeleton animation loader implementation for Md5 (Doom3) version 6 and 10
*
*  @note
*    - The version 6 needs a reference skeleton, else the import will not work! This reference skeleton is
*      given to the load function by using a 'RefSkeleton' pointer parameter to the reference skeleton.
*/
class SkeletonAniLoaderMd5 : public PLMesh::SkeletonAniLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SkeletonAniLoaderMd5, "PLDefaultFileFormats", PLMesh::SkeletonAniLoader, "Skeleton animation loader implementation for Md5 (Doom3) version 6 and 10")
		// Properties
		pl_properties
			pl_property("Formats",	"md5anim,MD5ANIM")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Methods
		pl_method_2(Load,	pl_ret_type(bool),	PLMesh::Skeleton&,	PLGeneral::File&,	"Load method",	"")
		pl_method_2(Save,	pl_ret_type(bool),	PLMesh::Skeleton&,	PLGeneral::File&,	"Save method",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLMesh::Skeleton &cSkeleton, PLGeneral::File &cFile);
		bool Save(PLMesh::Skeleton &cSkeleton, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SkeletonAniLoaderMd5();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SkeletonAniLoaderMd5();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Md5 version 6 loader
		*
		*  @param[in] cSkeleton
		*    Used skeleton
		*  @param[in] cTokenizer
		*    Tokenizer with the data to read
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV6(PLMesh::Skeleton &cSkeleton, PLGeneral::Tokenizer &cTokenizer, PLMesh::Skeleton *pRefSkeleton) const;

		/**
		*  @brief
		*    Md5 version 10 loader
		*
		*  @param[in] cSkeleton
		*    Used skeleton
		*  @param[in] cTokenizer
		*    Tokenizer with the data to read
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool LoadV10(PLMesh::Skeleton &cSkeleton, PLGeneral::Tokenizer &cTokenizer) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_DOOM3_SKELETONANILOADER_MD5_H__
