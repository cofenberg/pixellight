/*********************************************************\
 *  File: SkeletonAniLoaderMd5.cpp                       *
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


// [TODO] Fix problem with the relative animation frames for version 6 format


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/Tokenizer.h>
#include <PLGeneral/Log/Log.h>
#include <PLMath/EulerAngles.h>
#include <PLMesh/Skeleton.h>
#include "PLDefaultFileFormats/Doom3/SkeletonAniLoaderMd5.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Structures                                            ]
//[-------------------------------------------------------]
// Joint structure
class Md5Joint {
public:
	String sName;					// Joint name
	Array<float*> lstKeys;			// The frame keys for all animated components
									// (x, y, z, yaw, pitch, roll)
	Array<uint32> lstRangeStart;	// Range start for all animated components
	Array<uint32> lstRangeEnd;		// Range end for all animated components
	Md5Joint &operator =(const Md5Joint &cSource)
	{
		// We do not need an implementation in here...
		return *this;
	}
	bool operator ==(const Md5Joint &cJoint) const
	{
		// We do not need an implementation in here...
		return false;
	}
};


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SkeletonAniLoaderMd5)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool SkeletonAniLoaderMd5::Load(Skeleton &cSkeleton, File &cFile)
{
	// Is there a reference skeleton?
	// [TODO] New RTTI usage: Dynamic parameters
	Skeleton *pRefSkeleton = NULL;

	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n{}()[]=,;\"");
	cTokenizer.SetSingleChars("");
	cTokenizer.SetQuotes("");
	cTokenizer.SetCaseSensitive(true);

	// Get and check md5 version
	bool bResult = true; // No error by default
	uint32 nVersion = 0;
	if (cTokenizer.ExpectToken("MD5Version"))
		nVersion = cTokenizer.GetNextToken().GetInt();
	switch (nVersion) {
		case 6:  bResult = LoadV6 (cSkeleton, cTokenizer, pRefSkeleton); break;
		case 10: bResult = LoadV10(cSkeleton, cTokenizer); break;
	}
	cTokenizer.Stop();

	// Done
	return bResult;
}

bool SkeletonAniLoaderMd5::Save(Skeleton &cSkeleton, File &cFile)
{
	// [TODO] Implement me!
	return false; // Error!
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SkeletonAniLoaderMd5::SkeletonAniLoaderMd5() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
SkeletonAniLoaderMd5::~SkeletonAniLoaderMd5()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Md5 version 6 loader
*/
bool SkeletonAniLoaderMd5::LoadV6(Skeleton &cSkeleton, Tokenizer &cTokenizer, Skeleton *pRefSkeleton) const
{
	// [TODO] Fix me!

	// Check whether there is a reference skeleton
	if (!pRefSkeleton) {
		PL_LOG(Error, "The md5 version 6 loader needs a reference skeleton!")

		// Error!
		return false;
	}

	// Setup tokenizer
//	cTokenizer.SetSkippedChars(" \t\r\n{()[]=,;\"");
	cTokenizer.SetSingleChars("}");

	// Read in general information
	uint32 nNumChannels = 0;
	uint32 nReadInfo = 0;
	while (!nReadInfo && cTokenizer.GetNextToken().GetLength()) {
		// numchannels
		if (cTokenizer.CompareToken("numchannels")) {
			nNumChannels = cTokenizer.GetNextToken().GetInt();
			nReadInfo++;
		}
	}

	// Read in channels
	Array<Md5Joint*> lstJointsT;
	HashMap<String, Md5Joint*> mapJoints;
	uint32 nNumOfFrames = 0;
	for (uint32 nChannel=0; nChannel<nNumChannels; nChannel++) {
		Md5Joint *pJoint = NULL;
		char nAnimatedComponent = -1;
		while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("}")) {
			// joint
			if (cTokenizer.CompareToken("joint")) {
				// Get/create joint
				Md5Joint *pFoundJoint = mapJoints.Get(cTokenizer.GetNextToken());
				if (!pFoundJoint) {
					pJoint = new Md5Joint();
					pJoint->sName = cTokenizer.GetToken();
					pJoint->lstKeys.Resize(6);
					for (int i=0; i<6; i++)
						*pJoint->lstKeys[i] = NULL;
					pJoint->lstRangeStart.Resize(6);
					pJoint->lstRangeEnd.Resize(6);
					lstJointsT.Add(pJoint);
					mapJoints.Add(cTokenizer.GetToken(), pJoint);
				} else pJoint = pFoundJoint;
			} else {
				// attribute
				if (cTokenizer.CompareToken("attribute")) {
					cTokenizer.GetNextToken();
					if (cTokenizer.CompareToken("x"))		   nAnimatedComponent = 0;
					else if (cTokenizer.CompareToken("y"))	   nAnimatedComponent = 1;
					else if (cTokenizer.CompareToken("z"))	   nAnimatedComponent = 2;
					else if (cTokenizer.CompareToken("yaw"))   nAnimatedComponent = 3;
					else if (cTokenizer.CompareToken("pitch")) nAnimatedComponent = 4;
					else if (cTokenizer.CompareToken("roll"))  nAnimatedComponent = 5;
				} else {
					if (pJoint && nAnimatedComponent >= 0) {
						// range
						if (cTokenizer.CompareToken("range")) {
							pJoint->lstRangeStart[nAnimatedComponent] = cTokenizer.GetNextToken().GetInt();
							uint32 nEnd = pJoint->lstRangeEnd[nAnimatedComponent] = cTokenizer.GetNextToken().GetInt();
							if (nNumOfFrames < nEnd) nNumOfFrames = nEnd;

						// keys
						} else if (cTokenizer.CompareToken("keys")) {
							uint32 nKeys = cTokenizer.GetNextToken().GetInt();
							pJoint->lstKeys[nAnimatedComponent] = new float[nKeys];
							float *pKeys = pJoint->lstKeys[nAnimatedComponent];
							for (uint32 nKey=0; nKey<nKeys; nKey++)  {
								*pKeys = cTokenizer.GetNextToken().GetFloat();
								pKeys++;
							}
						}
					}
				}
			}
		}
	}

	// Allocate animation memory
	Array<Skeleton::AniJoint>  &lstJoints    = cSkeleton.GetJoints();
	Array<Skeleton::FrameKeys> &lstFrameKeys = cSkeleton.GetFrameKeys();
	lstJoints.Resize(lstJointsT.GetNumOfElements());
	lstFrameKeys.Resize(nNumOfFrames);
	cSkeleton.SetEndFrame(nNumOfFrames-1);
	cSkeleton.SetFlags(AnimationInfo::Loop);

	// Setup joints
	uint32 nUsedJoints = 0;
	for (uint32 nJoint=0; nJoint<pRefSkeleton->GetNumOfElements(); nJoint++) {
		Joint *pRefJoint = pRefSkeleton->Get(nJoint);
		Md5Joint *pJointT = mapJoints.Get(pRefJoint->GetName());
		if (pJointT) {
			Skeleton::AniJoint &cAniJoint = lstJoints[nUsedJoints];
			// Create the joint
			Joint *pJoint = cSkeleton.Create(pJointT->sName);
			// Set ID
			pJoint->SetID(nUsedJoints);
			// Set parent joint
			pJoint->SetParent(pRefJoint->GetParent()-(nJoint-nUsedJoints));
			// Animated components
			cAniJoint.nAnimatedComponents = Skeleton::AX | Skeleton::AY | Skeleton::AZ |
				Skeleton::AYaw | Skeleton::APitch | Skeleton::ARoll | Skeleton::AW;
			// Set base frame
			pJoint->SetTranslation(pRefJoint->GetTranslation());
			pJoint->SetTranslationAbsolute(pRefJoint->GetTranslationAbsolute());
			pJoint->SetRotation(pRefJoint->GetRotation());
			pJoint->SetRotationAbsolute(pRefJoint->GetRotationAbsolute());
			nUsedJoints++;
		}
	}
	lstJoints.Resize(nUsedJoints);

	// Set the parents of the joints
	for (uint32 nJoint=0; nJoint<lstJoints.GetNumOfElements(); nJoint++) {
		Joint *pJoint          = cSkeleton.Get(nJoint);
		Joint *pRefJoint       = pRefSkeleton->Get(pJoint->GetName());
		Joint *pRefParentJoint = pRefSkeleton->Get(pRefJoint->GetParent());
		if (pRefParentJoint) {
			Joint *pParentJoint = cSkeleton.Get(pRefParentJoint->GetName());
			pJoint->SetParent(pParentJoint->GetID());
		} else pJoint->SetParent(-1);
	}

	// Ok... now it's time to create the frame keys (uff :)
	Vector3 vTranslation, vTranslationR;
	Quaternion qRotation, qRotationR;
	for (uint32 nFrame=0; nFrame<lstFrameKeys.GetNumOfElements(); nFrame++) {
		Array<float> &lstFrameKeysT = lstFrameKeys[nFrame].lstFrameKeys;
		lstFrameKeysT.Resize(nUsedJoints*7);
		uint32 nKey = 0;
		for (uint32 nJoint=0; nJoint<lstJoints.GetNumOfElements(); nJoint++) {
			Joint  *pJoint  = cSkeleton.Get(nJoint);
			Md5Joint *pJointT = mapJoints.Get(pJoint->GetName());
			if (pJointT) {
				// Get joint data (x, y, z, yaw, pitch, roll)
				float fData[6];
				for (int i=0; i<6; i++) {
					if (nFrame < pJointT->lstRangeStart[i] || nFrame >= pJointT->lstRangeEnd[i])
						fData[i] = 0.0f;
					else fData[i] = pJointT->lstKeys[i][nFrame-pJointT->lstRangeStart[i]];
				}

				// Set translation
				vTranslation.SetXYZ(fData[0], fData[1], fData[2]);

				// [TODO] Check this
				// Get current joint rotation quaternion
	//			qRotation.FromEulerAnglesXYZ(float(fData[3]*Math::DegToRad), float(fData[4]*Math::DegToRad), float(fData[5]*Math::DegToRad));
				EulerAngles::ToQuaternion(float(fData[5]*Math::DegToRad), float(fData[4]*Math::DegToRad), float(fData[3]*Math::DegToRad), qRotation);
				qRotation.UnitInvert();

				// Make the joint relative to the base frame
				Quaternion qQP = pJoint->GetRotationAbsolute();
				qQP.UnitInvert();
				// Set translation
				vTranslationR = qQP*(vTranslation-pJoint->GetTranslationAbsolute());
				// Set rotation
				qRotationR = qRotation*qQP;

				// Now, at last, set the frame keys of this joint
				lstFrameKeysT[nKey++] = vTranslationR.x;
				lstFrameKeysT[nKey++] = vTranslationR.y;
				lstFrameKeysT[nKey++] = vTranslationR.z;
				lstFrameKeysT[nKey++] = qRotationR.x;
				lstFrameKeysT[nKey++] = qRotationR.y;
				lstFrameKeysT[nKey++] = qRotationR.z;
				lstFrameKeysT[nKey++] = qRotationR.w;
	/*
				lstFrameKeysT[nKey++] = vTranslation.x;
				lstFrameKeysT[nKey++] = vTranslation.y;
				lstFrameKeysT[nKey++] = vTranslation.z;
				lstFrameKeysT[nKey++] = qRotation.x;
				lstFrameKeysT[nKey++] = qRotation.y;
				lstFrameKeysT[nKey++] = qRotation.z;
				lstFrameKeysT[nKey++] = qRotation.w;
				*/
			}
		}
	}

	// Cleanup
	for (uint32 nJoint=0; nJoint<lstJoints.GetNumOfElements(); nJoint++) {
		Md5Joint *pJoint = lstJointsT[nJoint];
		for (int i=0; i<6; i++) {
			if (*pJoint->lstKeys[i])
				delete [] pJoint->lstKeys[i];
		}
		delete pJoint;
	}

	// Done
	return true;
}

/**
*  @brief
*    Md5 version 10 loader
*/
bool SkeletonAniLoaderMd5::LoadV10(Skeleton &cSkeleton, Tokenizer &cTokenizer) const
{
	// Read in general information
	uint32 nNumFrames = 0;
	uint32 nNumJoints = 0;
	uint32 nNumAnimatedComponents = 0;
	uint32 nReadInfo = 0;
	while (nReadInfo < 4 && cTokenizer.GetNextToken().GetLength()) {
		// numFrames
		if (cTokenizer.CompareToken("numFrames")) {
			nNumFrames = cTokenizer.GetNextToken().GetInt();
			nReadInfo++;

		// numJoints
		} else if (cTokenizer.CompareToken("numJoints")) {
			nNumJoints = cTokenizer.GetNextToken().GetInt();
			nReadInfo++;

		// frameRate
		} else if (cTokenizer.CompareToken("frameRate")) {
			cSkeleton.SetFrameRate(cTokenizer.GetNextToken().GetFloat());
			nReadInfo++;

		// numAnimatedComponents
		} else if (cTokenizer.CompareToken("numAnimatedComponents")) {
			nNumAnimatedComponents = cTokenizer.GetNextToken().GetInt();
			nReadInfo++;
		}
	}

	// Allocate animation memory
	Array<Skeleton::AniJoint>  &lstJoints    = cSkeleton.GetJoints();
	Array<Skeleton::FrameKeys> &lstFrameKeys = cSkeleton.GetFrameKeys();
	lstJoints.Resize(nNumJoints);
	lstFrameKeys.Resize(nNumFrames);
	cSkeleton.SetEndFrame(nNumFrames-1);
	cSkeleton.SetFlags(AnimationInfo::Loop);

	// Read in animation
	while (cTokenizer.GetNextToken().GetLength()) {
		// hierarchy
		if (cTokenizer.CompareToken("hierarchy")) {
			for (uint32 i=0; i<nNumJoints; i++) {
				Skeleton::AniJoint &cAniJoint = lstJoints[i];
				// Name
				String sName = cTokenizer.GetNextToken();
				// Create the joint
				Joint *pJoint = cSkeleton.Create(sName);
				// Set ID
				pJoint->SetID(i);
				// Set parent joint
				pJoint->SetParent(cTokenizer.GetNextToken().GetInt());
				// Animated components
				cAniJoint.nAnimatedComponents = (uint8)cTokenizer.GetNextToken().GetInt();
				// First key (ignored)
				cTokenizer.GetNextToken();
			}

		// bounds
		} else if (cTokenizer.CompareToken("bounds")) {
			for (uint32 i=0; i<nNumFrames; i++) {
				// Min
				float fX = cTokenizer.GetNextToken().GetFloat();
				float fY = cTokenizer.GetNextToken().GetFloat();
				float fZ = cTokenizer.GetNextToken().GetFloat();
//				lstBounds[i2++]->SetXYZ(fX, fY, fZ);
				// Max
				fX = cTokenizer.GetNextToken().GetFloat();
				fY = cTokenizer.GetNextToken().GetFloat();
				fZ = cTokenizer.GetNextToken().GetFloat();
//				lstBounds[i2++]->SetXYZ(fX, fY, fZ);
			}

		// baseframe
		} else if (cTokenizer.CompareToken("baseframe")) {
			for (uint32 i=0; i<nNumJoints; i++) {
				Joint *pJoint = cSkeleton.Get(i);
				// Pos
				float fX = cTokenizer.GetNextToken().GetFloat();
				float fY = cTokenizer.GetNextToken().GetFloat();
				float fZ = cTokenizer.GetNextToken().GetFloat();
				pJoint->SetTranslationAbsolute(Vector3(fX, fY, fZ));
				// Rot
				fX = cTokenizer.GetNextToken().GetFloat();
				fY = cTokenizer.GetNextToken().GetFloat();
				fZ = cTokenizer.GetNextToken().GetFloat();
				// Compute last component (w) of the quaternion
				float fTerm = 1.0f - (fX*fX) - (fY*fY) - (fZ*fZ);
				float fW    = fTerm < 0.0f ? 0.0f : -Math::Sqrt(fTerm);
				pJoint->SetRotationAbsolute(Quaternion(fW, fX, fY, fZ));
			}

		// frame
		} else if (cTokenizer.CompareToken("frame")) {
			// Read frame ID
			uint32 nFrameID = cTokenizer.GetNextToken().GetInt();
			Array<float> &lstFrameKeysT = lstFrameKeys[nFrameID].lstFrameKeys;
			lstFrameKeysT.Resize(nNumAnimatedComponents);
			for (uint32 i=0; i<lstFrameKeysT.GetNumOfElements(); i++)
				lstFrameKeysT[i] = cTokenizer.GetNextToken().GetFloat();
			if (nFrameID >= nNumFrames-1)
				break;
		}
	}

	// Make the base joints relative
	for (uint32 i=0; i<cSkeleton.GetNumOfElements(); i++) {
		// Get this joint
		Joint *pJoint = cSkeleton.Get(i);

		// Get parent of this joint
		Joint *pParentJoint = cSkeleton.Get(pJoint->GetParent());
		if (pParentJoint) {
			// Get relative joint state
			Quaternion q = pParentJoint->GetRotationAbsolute();
			q.UnitInvert();
			pJoint->SetTranslation(q*(pJoint->GetTranslationAbsolute()-pParentJoint->GetTranslationAbsolute()));
			pJoint->SetRotation(pJoint->GetRotationAbsolute()*q);
		} else {
			pJoint->SetTranslation(pJoint->GetTranslationAbsolute());
			pJoint->SetRotation(pJoint->GetRotationAbsolute());
		}
	}

	// Make the frame joints relative to each other and to the base frame
	Vector3 vTranslationAbsolute, vTranslation, vTranslationR;
	Quaternion qRotationAbsolute, qRotation, qRotationR;
	for (uint32 nFrame=0; nFrame<nNumFrames; nFrame++) {
		Array<float> &lstFrameKeysT = lstFrameKeys[nFrame].lstFrameKeys;
		uint32 nKey = 0;
		for (uint32 i=0; i<cSkeleton.GetNumOfElements(); i++) {
			// Get this joint
			Skeleton::AniJoint &cAniJoint = lstJoints[i];
			Joint *pJoint = cSkeleton.Get(i);

			// Get parent of this joint
			Joint *pParentJoint = cSkeleton.Get(pJoint->GetParent());

			// Get joint absolute translation and rotation
			uint32 nAnimatedComponents = cAniJoint.nAnimatedComponents;
			// Translation
			if (nAnimatedComponents & Skeleton::AX)
				vTranslationAbsolute.x = lstFrameKeysT[nKey++];
			else vTranslationAbsolute.x = pJoint->GetTranslationAbsolute().x;
			if (nAnimatedComponents & Skeleton::AY)
				vTranslationAbsolute.y = lstFrameKeysT[nKey++];
			else vTranslationAbsolute.y = pJoint->GetTranslationAbsolute().y;
			if (nAnimatedComponents & Skeleton::AZ)
				vTranslationAbsolute.z = lstFrameKeysT[nKey++];
			else vTranslationAbsolute.z = pJoint->GetTranslationAbsolute().z;

			// Rotation
			if (nAnimatedComponents & Skeleton::AYaw)
				qRotationAbsolute.x = lstFrameKeysT[nKey++];
			else qRotationAbsolute.x = pJoint->GetRotationAbsolute().x;
			if (nAnimatedComponents & Skeleton::APitch)
				qRotationAbsolute.y = lstFrameKeysT[nKey++];
			else qRotationAbsolute.y = pJoint->GetRotationAbsolute().y;
			if (nAnimatedComponents & Skeleton::ARoll)
				qRotationAbsolute.z = lstFrameKeysT[nKey++];
			else qRotationAbsolute.z = pJoint->GetRotationAbsolute().z;
			if (nAnimatedComponents & Skeleton::AW)
				qRotationAbsolute.w = lstFrameKeysT[nKey++];
			else {
				// Compute last component (w) of the quaternion
				float fSqw = 1.0f - qRotationAbsolute.x*qRotationAbsolute.x -
									qRotationAbsolute.y*qRotationAbsolute.y -
									qRotationAbsolute.z*qRotationAbsolute.z;
				qRotationAbsolute.w = fSqw <= 0.0f ? 0.0f : -Math::Sqrt(fSqw);
			}

			// Get relative translation and rotation
			if (pParentJoint) {
				Quaternion q = pParentJoint->GetRotationAbsolute();
				q.UnitInvert();
				vTranslation = q*(vTranslationAbsolute-pParentJoint->GetTranslationAbsolute());
				qRotation    = qRotationAbsolute*q;
			} else {
				vTranslation = vTranslationAbsolute;
				qRotation    = qRotationAbsolute;
			}

			// Make the joint relative to the base frame
			Quaternion qQP = pJoint->GetRotation();
			qQP.UnitInvert();
			// Set translation
			vTranslationR = qQP*(vTranslation-pJoint->GetTranslation());
			// Set rotation
			qRotationR = qRotation*qQP;

			// Set the new frame keys
			uint32 nKeyT = nKey;
			nKey--;
			// Rotation
			if (nAnimatedComponents & Skeleton::AW)
				lstFrameKeysT[nKey--] = qRotationR.w;
			if (nAnimatedComponents & Skeleton::ARoll)
				lstFrameKeysT[nKey--] = qRotationR.z;
			if (nAnimatedComponents & Skeleton::APitch)
				lstFrameKeysT[nKey--] = qRotationR.y;
			if (nAnimatedComponents & Skeleton::AYaw)
				lstFrameKeysT[nKey--] = qRotationR.x;
			// Translation
			if (nAnimatedComponents & Skeleton::AZ)
				lstFrameKeysT[nKey--] = vTranslationR.z;
			if (nAnimatedComponents & Skeleton::AY)
				lstFrameKeysT[nKey--] = vTranslationR.y;
			if (nAnimatedComponents & Skeleton::AX)
				lstFrameKeysT[nKey--] = vTranslationR.x;
			nKey = nKeyT;
		}
	}

	// Done
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
