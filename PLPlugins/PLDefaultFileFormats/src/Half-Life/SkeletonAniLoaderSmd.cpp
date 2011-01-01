/*********************************************************\
 *  File: SkeletonAniLoaderSmd.cpp                       *
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


// [TODO] Fix problem with the relative animation frames


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/String/Tokenizer.h>
#include <PLGeneral/Log/Log.h>
#include <PLMath/EulerAngles.h>
#include <PLMesh/Skeleton.h>
#include "PLDefaultFileFormats/Half-Life/SkeletonAniLoaderSmd.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLMesh;
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SkeletonAniLoaderSmd)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool SkeletonAniLoaderSmd::Load(Skeleton &cSkeleton, File &cFile)
{
	// Setup skeleton
	cSkeleton.Clear();
	cSkeleton.SetFrameRate(24.0f);

	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.Start(cFile);
	cTokenizer.SetDelimiters(" \t\r\n()[]=,;{}\"");
	cTokenizer.SetSingleChars(":");
	cTokenizer.SetCaseSensitive(true);

	// First at all, check the version number
	if (cTokenizer.GetNextToken() != "version" || cTokenizer.GetNextToken().GetInt() != 1) {
		PL_LOG(Error, "Invalid version number!")
		cTokenizer.Stop();

		// Error!
		return false;
	}

	// Read file
	while (cTokenizer.GetNextToken().GetLength()) {
		// nodes
		if (cTokenizer.CompareToken("nodes")) {
			Array<Skeleton::AniJoint> &lstJoints = cSkeleton.GetJoints();
			while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("end")) {
				uint32 nNum    = cTokenizer.GetToken().GetInt();
				String sName   = cTokenizer.GetNextToken();
				int    nParent = cTokenizer.GetNextToken().GetInt();

				Joint *pJoint = cSkeleton.Create(sName);
				pJoint->SetID(nNum);
				pJoint->SetParent(nParent);

				lstJoints.Resize(nNum+1);
				Skeleton::AniJoint &cAniJoint = lstJoints[nNum];
				cAniJoint.nAnimatedComponents = Skeleton::AX | Skeleton::AY |
					Skeleton::AZ | Skeleton::AYaw | Skeleton::APitch |
					Skeleton::ARoll | Skeleton::AW;
			}

		// skeleton
		} else if (cTokenizer.CompareToken("skeleton")) {
			// Parse joint base translation/rotation (we only read the base frame at time 0!)
			while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("end") && !cTokenizer.CompareToken("time")) {
				uint32 nNode = cTokenizer.GetToken().GetInt();
				Vector3 vTranslation(cTokenizer.GetNextToken().GetFloat(),
									 cTokenizer.GetNextToken().GetFloat(),
									 cTokenizer.GetNextToken().GetFloat());
				float roll  = cTokenizer.GetNextToken().GetFloat();
				float pitch = cTokenizer.GetNextToken().GetFloat();
				float yaw   = cTokenizer.GetNextToken().GetFloat();

				Joint *pJoint = cSkeleton.Get(nNode);
				if (pJoint) {
					pJoint->SetTranslation(vTranslation);
					// [TODO] The result is wrong...
					Quaternion qRotation;
					EulerAngles::ToQuaternion(float(roll*Math::RadToDeg), float(pitch*Math::RadToDeg), float(yaw*Math::RadToDeg), qRotation);
					qRotation.Invert();
					pJoint->SetRotation(qRotation);
				}
			}

			// Update skeleton
			cSkeleton.UpdateJointInformation();

			// Loop through all root joints
			for (uint32 i=0; i<cSkeleton.GetRootJoints().GetNumOfElements(); i++) {
				Joint *pJoint = cSkeleton.Get(cSkeleton.GetRootJoints()[i]);
				RecCalculateStates(cSkeleton, *pJoint, NULL);
			}
			if (!cTokenizer.CompareToken("end")) {
				// Read frame keys
				Array<Skeleton::FrameKeys> &lstFrameKeys = cSkeleton.GetFrameKeys();
				uint32 nAnimatedComponents = 7*cSkeleton.GetNumOfElements();
				uint32 nNumOfFrames = 1;
				do {
					lstFrameKeys.Resize(nNumOfFrames);
					Array<float> &lstFrameKeysT = lstFrameKeys[nNumOfFrames-1].lstFrameKeys;
					lstFrameKeysT.Resize(nAnimatedComponents);

					// Skip time number
					cTokenizer.GetNextToken();

					// Load joint translation/rotation of this frame
					uint32 nKey = 0;
					while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("end") && !cTokenizer.CompareToken("time")) {
						// Read joint information
						uint32 nNode = cTokenizer.GetToken().GetInt();
						Vector3 vTranslation(cTokenizer.GetNextToken().GetFloat(),
											 cTokenizer.GetNextToken().GetFloat(),
											 cTokenizer.GetNextToken().GetFloat());
						float roll  = cTokenizer.GetNextToken().GetFloat();
						float pitch = cTokenizer.GetNextToken().GetFloat();
						float yaw   = cTokenizer.GetNextToken().GetFloat();

						Joint *pJoint = cSkeleton.Get(nNode);
						if (pJoint) {
							// Make the animation frame relative to the base frame
							Quaternion qQP = pJoint->GetRotation();
							qQP.Invert();

							// Set translation
							Vector3 vV = qQP*(vTranslation-pJoint->GetTranslation());
							lstFrameKeysT[nKey] = vV.x;
							nKey++;
							lstFrameKeysT[nKey] = vV.y;
							nKey++;
							lstFrameKeysT[nKey] = vV.z;
							nKey++;

							// Set rotation
							// [TODO] Check this
							Quaternion qRotation;
							EulerAngles::ToQuaternion(float(roll*Math::RadToDeg), float(pitch*Math::RadToDeg), float(yaw*Math::RadToDeg), qRotation);
							qRotation.Invert();
							qRotation = qRotation*qRotation;
							lstFrameKeysT[nKey] = qRotation.x;
							nKey++;
							lstFrameKeysT[nKey] = qRotation.y;
							nKey++;
							lstFrameKeysT[nKey] = qRotation.z;
							nKey++;
							lstFrameKeysT[nKey] = qRotation.w;
							nKey++;
						}
					}
					nNumOfFrames++;
				} while (!cTokenizer.CompareToken("end") && cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("end"));
				cSkeleton.SetEndFrame(nNumOfFrames-1);
				cSkeleton.SetFlags(PLRenderer::AnimationInfo::Loop);
			}

		// triangles
		} else if (cTokenizer.CompareToken("triangles")) {
			// Read all faces
			while (cTokenizer.GetNextToken().GetLength() && !cTokenizer.CompareToken("end"))
				; // Do nothing
		}
	}
	cTokenizer.Stop();

	// Done
	return true;
}

bool SkeletonAniLoaderSmd::Save(Skeleton &cSkeleton, File &cFile)
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
SkeletonAniLoaderSmd::SkeletonAniLoaderSmd() :
	MethodLoad(this),
	MethodSave(this)
{
}

/**
*  @brief
*    Destructor
*/
SkeletonAniLoaderSmd::~SkeletonAniLoaderSmd()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Recursive joint state calculations
*/
void SkeletonAniLoaderSmd::RecCalculateStates(const Skeleton &cSkeleton, Joint &cJoint, Joint *pParentJoint) const
{
	// Check and calculate states of this joint
	if (pParentJoint) {
		// Transform relative state with the absolute state of the parent
		cJoint.SetTranslationAbsolute(pParentJoint->GetRotationAbsolute()*cJoint.GetTranslation()+
									  pParentJoint->GetTranslationAbsolute());
		cJoint.SetRotationAbsolute(cJoint.GetRotation()*pParentJoint->GetRotationAbsolute());
	} else {
		// If there's no parent the absolute states are equal to the relative states
		cJoint.SetTranslationAbsolute(cJoint.GetTranslation());
		cJoint.SetRotationAbsolute(cJoint.GetRotation());
	}

	// Set joint space data
	Quaternion qQ = cJoint.GetRotationAbsolute();
	qQ.Invert();
	cJoint.SetTranslationJointSpace(qQ*(-cJoint.GetTranslationAbsolute()));
	cJoint.SetRotationJointSpace(qQ);

	// Transform children
	for (uint32 i=0; i<cJoint.GetChildren().GetNumOfElements(); i++)
		RecCalculateStates(cSkeleton, *cSkeleton.Get(cJoint.GetChildren()[i]), &cJoint);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats
