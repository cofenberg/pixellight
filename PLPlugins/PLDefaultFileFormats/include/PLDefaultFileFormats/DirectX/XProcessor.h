/*********************************************************\
 *  File: XProcessor.h                                   *
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


#ifndef __PLDEFAULTFILEFORMATS_DIRECTX_XPROCESSOR_H__
#define __PLDEFAULTFILEFORMATS_DIRECTX_XPROCESSOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/PLGeneral.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class XNode;


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
/**
*  @brief
*    DirectX file header
*/
struct XFileHeader {
	char nSignature[4];		/**< Magic number (required) "xof" */
	char nMinor[2];			/**< Minor version "03" */
	char nMajor[2];			/**< Major version "02" */
	char nType[4];			/**< Format type (required)
								"txt " text file
								"bin " binary file
								"tzip" MSZip compressed text file
								"bzip" MSZip compressed binary file */
	char nAccuracy[4];		/**< Float accuracy "0032" 32 bit or "0064" 64 bit */
};

/**
*  @brief
*    DirectX vector template (GUID: <3D82AB5E-62DA-11CF-AB39-0020AF71E433>)
*/
struct XVector {
	float x;	/**< x component */
	float y;	/**< y component */
	float z;	/**< z component */
};

/**
*  @brief
*    DirectX 2D (texture) coordinate template (GUID: <F6F23F44-7686-11CF-8F52-0040333594A3>)
*
*  @remarks
*    A two dimensional vector used to define a mesh's texture coordinates.
*/
struct XCoords2d {
	float u;	/**< u component */
	float v;	/**< v component */
};

/**
*  @brief
*    DirectX quaternion template (GUID: <10DD46A3-775B-11cf-8F52-0040333594A3>)
*/
struct XQuaternion {
	XVector v;	/**< Vector */
	float   s;	/**< Scalar */
};

/**
*  @brief
*    DirectX 4x4 matrix template (GUID: <F6F23F45-7686-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines a 4×4 matrix. This is used as a frame transformation matrix.
*/
struct XMatrix4x4 {
	float f[16];
};

/**
*  @brief
*    DirectX RGB color template (GUID: <D3E16E81-7835-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines the basic RGB color object.
*/
struct XColorRGB {
	float fRed;		/**< Red component */
	float fGreen;	/**< Green component */
	float fBlue;	/**< Blue component */
};

/**
*  @brief
*    DirectX RGBA color template (GUID: <35FF44E0-6C7C-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines a color object with an alpha component. This is used for the face
*    color in the material template definition.
*/
struct XColorRGBA {
	float fRed;		/**< Red component */
	float fGreen;	/**< Green component */
	float fBlue;	/**< Blue component */
	float fAlpha;	/**< Alpha component */
};

/**
*  @brief
*    DirectX indexed (vertex) color template (GUID: <1630B820-7842-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template consists of an index parameter and an RGBA color and is used for defining
*    mesh vertex colors. The index defines the vertex to which the color is applied.
*/
struct XIndexedColor {
	PLGeneral::uint32 nIndex;	/**< Index of the vertex this color is for */
	XColorRGBA        sColor;	/**< RGBA color for the indexed vertex */
};

/**
*  @brief
*    DirectX boolean template (GUID: <537DA6A0-CA37-11D0-941C-0080C80CFA7B>)
*
*  @remarks
*    Defines a simple boolean type. This template should be set to 0 or 1.
*/
struct XBoolean {
	PLGeneral::uint32 nValue;	/**< 0 for false or 1 for true */
};

/**
*  @brief
*    DirectX 2D boolean template (GUID: <4885AE63-78E8-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines a set of two XBoolean values used in the XMeshFaceWraps template to
*    define the texture topology of an individual face.
*/
struct XBoolean2d {
	XBoolean u;	/**< u boolean */
	XBoolean v;	/**< v boolean */
};

/**
*  @brief
*    DirectX texture filename template (GUID: <A42790E1-7810-11cf-8F52-0040333594A3>)
*
*  @remarks
*    This template allows you to specify the filename of a texture to apply to a mesh or a face.
*    This template should appear within a material object.
*/
struct XTextureFilename {
	char *pszName;	/**< Null terminated string (always valid!) */
};

/**
*  @brief
*    DirectX mesh face template (GUID: <3D82AB5F-62DA-11CF-AB39-0020AF71E433>)
*
*  @remarks
*    This template is used by the XMesh template to define a mesh's faces. Each element
*    of the pnFaceVertexIndices array references a mesh vertex used to build the face.
*/
struct XMeshFace {
	PLGeneral::uint32  nNumFaceVertexIndices;	/**< Number of face vertex indices */
	PLGeneral::uint32 *pnFaceVertexIndices;		/**< Face vertex indices */
};

/**
*  @brief
*    DirectX mesh face wraps template (GUID: <ED1EC5C0-C0A8-11D0-941C-0080C80CFA7B>)
*
*  @remarks
*    This template is used to define the texture topology of each face in a wrap. The value of
*    the nFaceWrapValues member should be equal to the number of faces in a mesh.
*/
struct XMeshFaceWraps {
	PLGeneral::uint32  nFaceWrapValues;		/**< Face wrap values */
	XBoolean2d        *psFaceWrapValues;	/**< Face wrap values */
};

/**
*  @brief
*    DirectX mesh texture coordinates template (GUID: <F6F23F40-7686-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines a mesh's texture coordinates.
*/
struct XMeshTextureCoords {
	PLGeneral::uint32  nTextureCoords;	/**< Number of texture coordinates */
	XCoords2d         *psTextureCoords;	/**< Texture coordinates */
};

/**
*  @brief
*    DirectX mesh normals template (GUID: <F6F23F43-7686-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines normals for a mesh. The first array of vectors is the normal vectors
*    themselves, and the second array is an array of indexes specifying which normals should be
*    applied to a given face. The value of the nFaceNormals member should be equal to the number
*    of faces in a mesh.
*/
struct XMeshNormals {
	PLGeneral::uint32  nNormals;		/**< Number of vertex normals */
	XVector           *psNormals;		/**< Vertex normals */
	PLGeneral::uint32  nFaceNormals;	/**< Number of face normals */
	XMeshFace         *psFaceNormals;	/**< Face normals */
};

/**
*  @brief
*    DirectX mesh vertex colors template (GUID: <1630B821-7842-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template specifies vertex colors for a mesh, instead of applying a material per face or per mesh.
*/
struct XMeshVertexColors {
	PLGeneral::uint32  nVertexColors;	/**< Number of vertex colors */
	XIndexedColor     *psVertexColors;	/**< Vertex colors */
};

/**
*  @brief
*    DirectX mesh material list template (GUID: <F6F23F42-7686-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template is used in a mesh object to specify which material applies to which faces.
*    The nMaterials member specifies how many materials are present, and materials specify which
*    material to apply.
*/
struct XMeshMaterialList {
	PLGeneral::uint32  nMaterials;		/**< Number of available materials */
	PLGeneral::uint32  nFaceIndexes;	/**< Number of face indices */
	PLGeneral::uint32 *pnFaceIndexes;	/**< Zero-based face material indices */
	XNode             *pcFirstMaterial;	/**< First material */
};

/**
*  @brief
*    DirectX frame transform matrix template (GUID: <F6F23F41-7686-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines a local transform for a frame (and all its child objects).
*/
struct XFrameTransformMatrix {
	XMatrix4x4 sFrameMatrix;	/**< Frame matrix */
};

/**
*  @brief
*    DirectX float keys template (GUID: <10DD46A9-775B-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines an array of floating-point numbers (floats) and the number of floats
*    in that array. This is used for defining sets of animation keys.
*/
struct XFloatKeys {
	PLGeneral::uint32  nValues;		/**< Number of values */
	float             *pfValues;	/**< Values */
};

/**
*  @brief
*    DirectX timed float keys template (GUID: <F406B180-7B3B-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines a set of floats and a positive time used in animations.
*/
struct XTimedFloatKeys {
	PLGeneral::uint32  nTime;		/**< Number of time keys */
	XFloatKeys        *psTimeKeys;	/**< Time keys */
};

/**
*  @brief
*    DirectX animation key template (GUID: <10DD46A8-775B-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template defines a set of animation keys. The nKeyType member specifies whether the
*    keys are rotation, scale or position keys:
*
*      Key        Data      Number        Data
*     Number      Type     of values      type
*    -----------------------------------------------
*       0     rotation        4         quaternion
*       1     scaling         3         vector
*       2     translation     3         vector
*       3     matrix          16        matrix
*/
struct XAnimationKeys {
	PLGeneral::uint32  nKeyType;	/**< Key type */
	PLGeneral::uint32  nKeys;		/**< Number of keys */
	XTimedFloatKeys   *psKeys;		/**< Keys */
};

/**
*  @brief
*    DirectX animation options template (GUID: <E2BF56C0-840F-11CF-8F52-0040333594A3>)
*
*  @remarks
*    This template enables you to set the XAnimation options. The nOpenClosed member can be
*    either 0 for a closed or 1 for an open animation. The nPositionQuality member is used to
*    set the position quality for any position keys specified and can either be 0 for spline
*    positions or 1 for linear positions. By default, an animation is closed.
*/
struct XAnimationOptions {
	PLGeneral::uint32 nOpenClosed;		/**< 0 for a closed or 1 for an open animation */
	PLGeneral::uint32 nPositionQuality;	/**< 0 for spline positions or 1 for linear positions */
};


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    DirectX node base
*/
class XNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XRoot;
	friend class XRootBinary;


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Node type
		*/
		enum EType {
			Root,
			Reference,
			Header,
			Material,
			Mesh,
			Frame,
			Animation,
			AnimationSet
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the node type
		*
		*  @return
		*    The node type
		*/
		EType GetType() const;

		/**
		*  @brief
		*    Returns the next node
		*
		*  @return
		*    The next node, NULL if there's no next node
		*/
		XNode *GetNextNode() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nType
		*    Node type
		*/
		XNode(EType nType);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XNode();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		EType  m_nType;			/**< Node type */
		XNode *m_pcNextNode;	/**< Next node, can be NULL */


};

/**
*  @brief
*    DirectX root
*/
class XRoot : public XNode {


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Statistics
		*/
		struct Statistics {
			PLGeneral::uint32 nNumOfMeshes;			/**< Number of meshes */
			PLGeneral::uint32 nNumOfMeshVertices;	/**< Number of mesh vertices */
			PLGeneral::uint32 nNumOfMeshFaces;		/**< Number of mesh faces */
			bool			  bTextureCoords;		/**< Are there any texture coordinates? */
			bool			  bNormals;				/**< Are there any normals? */
		};


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XRoot();

		/**
		*  @brief
		*    Returns the first child node
		*
		*  @return
		*    The first child node, NULL if there's no first child node
		*/
		XNode *GetFirstChildNode() const;

		/**
		*  @brief
		*    Returns the statistics
		*
		*  @return
		*    Statistics
		*/
		const Statistics &GetStatistics() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		XRoot();


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		XNode      *m_pcFirstNode;	/**< First node, can be NULL */
		Statistics  m_sStatistics;	/**< Statistics */


};

/**
*  @brief
*    DirectX reference
*
*  @remarks
*    Holds the name of for instance a referenced material or mesh.
*/
class XReference : public XNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XRootBinary;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		char *pszName;	/**< Name of the referenced data, can be NULL */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		XReference();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XReference();


};

/**
*  @brief
*    DirectX header template (GUID: <3D82AB43-62DA-11CF-AB39-0020AF71E433>)
*/
class XHeader : public XNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XRootBinary;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		PLGeneral::uint16 nMajor;	/**< Major version */
		PLGeneral::uint16 nMinor;	/**< Minor version */
		PLGeneral::uint32 nFlags;	/**< Flags */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		XHeader();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XHeader();


};

/**
*  @brief
*    DirectX material template (GUID: <3D82AB4D-62DA-11CF-AB39-0020AF71E433>)
*
*  @remarks
*    This template defines a basic material color that can be applied to either a complete mesh
*    or a mesh's individual faces. The power is the specular exponent of the material. Note that
*    the ambient color requires an alpha component.
*    XTextureFilename is an optional data object. If this object is not present, the face is untextured.
*/
class XMaterial : public XNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XRootBinary;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		char             *pszName;				/**< Material name, can be NULL */
		XColorRGBA        sFaceColor;			/**< Face color */
		float             fPower;				/**< Power (specular exponent) */
		XColorRGB         sSpecularColor;		/**< Specular color */
		XColorRGB         sEmissiveColor;		/**< Emissive color */
		XTextureFilename *psTextureFilename;	/**< Texture filename, can be NULL */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		XMaterial();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XMaterial();


};

/**
*  @brief
*    DirectX mesh template (GUID: <3D82AB44-62DA-11CF-AB39-0020AF71E433>)
*
*  @remarks
*    This template defines a simple mesh. The first array is a list of vertices, and the second
*    array defines the faces of the mesh by indexing into the vertex array.
*
*  @remarks
*    Optional data elements:
*    - XMeshFaceWraps      If this is not present, wrapping for both u and v defaults to false
*    - XMeshTextureCoords  If this is not present, there are no texture coordinates
*    - XMeshNormals        If this is not present, normals are generated automatically
*    - XMeshVertexColors   If this is not present, the colors default to white
*    - XMeshMaterialList   If this is not present, the material defaults to white
*/
class XMesh : public XNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XFrame;
	friend class XRootBinary;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		char               *pszName;			/**< Mesh name, can be NULL */
		PLGeneral::uint32   nVertices;			/**< Number of vertices */
		XVector            *psVertices;			/**< Vertices */
		PLGeneral::uint32   nFaces;				/**< Number of faces */
		XMeshFace          *psFaces;			/**< Faces */
		// Optional data elements
		XMeshFaceWraps     *psFaceWraps;		/**< Can be NULL */
		XMeshTextureCoords *psTextureCoords;	/**< Can be NULL */
		XMeshNormals       *psNormals;			/**< Can be NULL */
		XMeshVertexColors  *psVertexColors;		/**< Can be NULL */
		XMeshMaterialList  *psMaterialList;		/**< Can be NULL */


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		XMesh();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XMesh();


};

/**
*  @brief
*    DirectX frame template (GUID: <3D82AB46-62DA-11CF-AB39-0020AF71E433>)
*
*  @remarks
*    This template defines a frame. The frame can contain objects of the type XFrameTransformMatrix and a XMesh.
*
*  @remarks
*    Optional data elements:
*    - XFrameTransformMatrix  If this element is not present, no local transform is applied to the frame
*    - XMesh                  Any number of mesh objects that become children of the frame - these objects can be specified inline or by reference
*/
class XFrame : public XNode {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class XRootBinary;


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		char				  *pszName;				/**< Frame name, can be NULL */
		XFrameTransformMatrix *psTransformMatrix;	/**< Can be NULL */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the first child node
		*
		*  @return
		*    The first child node, NULL if there's no first child node
		*/
		XNode *GetFirstChildNode() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		XFrame();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XFrame();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		XNode *m_pcFirstNode;	/**< First node, can be NULL */


};

/**
*  @brief
*    DirectX animation template (GUID: <3D82AB4F-62DA-11CF-AB39-0020AF71E433>)
*
*  @remarks
*    This template contains animations referencing a previous frame. It should contain one
*    reference to a frame and at least one set of XAnimationKeys. It also can contain an
*    XAnimationOptions data object.
*
*    Optional data elements:
*    - AnimationKey      An animation is meaningless without XAnimationKeys
*    - AnimationOptions  If this element is not present, an animation is closed
*/
class XAnimation : public XNode {
	// [TODO]


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		XAnimation();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XAnimation();


};

/**
*  @brief
*    DirectX animation set template (GUID: <3D82AB50-62DA-11CF-AB39-0020AF71E433>)
*
*  @remarks
*    An XAnimationSet template contains one or more XAnimation objects. This means each animation
*    within an animation set has the same time at any given point. Increasing the animation set's
*    time will increase the time for all the animations it contains.
*/
class XAnimationSet : public XNode {
	// [TODO]


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		XAnimationSet();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~XAnimationSet();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_DIRECTX_XPROCESSOR_H__
