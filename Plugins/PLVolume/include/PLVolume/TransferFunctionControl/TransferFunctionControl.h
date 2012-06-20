/*********************************************************\
 *  File: TransferFunctionControl.h                      *
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


#ifndef __PLVOLUME_TRANSFERFUNCTIONCONTROL_H__
#define __PLVOLUME_TRANSFERFUNCTIONCONTROL_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLVolume/TransferFunction.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector2;
}
namespace PLGraphics {
	class Color3;
}
namespace PLVolume {
	class TransferFunctionChannel;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLVolume {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Transfer function control
*/
class TransferFunctionControl : public TransferFunction {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class TransferFunctionChannel;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLVOLUME_API TransferFunctionControl();

		/**
		*  @brief
		*    Destructor
		*/
		PLVOLUME_API virtual ~TransferFunctionControl();

		/**
		*  @brief
		*    Adds a transfer function channel
		*
		*  @return
		*    Reference to the added transfer function channel
		*/
		PLVOLUME_API TransferFunctionChannel &AddChannel();

		/**
		*  @brief
		*    Removes all transfer function channels
		*/
		PLVOLUME_API void RemoveAllChannels();

		/**
		*  @brief
		*    Returns the list of transfer function channels
		*
		*  @return
		*    The list of transfer function channels
		*
		*  @note
		*    - This method marks derived data to be dirty, use the constant method version of this method whenever possible to avoid unnecessary recalculations
		*/
		inline PLCore::Array<TransferFunctionChannel*> &GetChannels();

		/**
		*  @brief
		*    Returns the list of transfer function channels
		*
		*  @return
		*    The list of transfer function channels
		*/
		inline const PLCore::Array<TransferFunctionChannel*> &GetChannels() const;

		//[-------------------------------------------------------]
		//[ Helper                                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Sets the default transfer function configuration
		*/
		PLVOLUME_API void SetDefaultConfiguration();

		/**
		*  @brief
		*    Moves a transfer control point and performs the required security checks while doing so
		*
		*  @param[in] nChannel
		*    Channel
		*  @param[in] nControlPoint
		*    Control point to move
		*  @param[in] vDelta
		*    Movement delta
		*/
		PLVOLUME_API void MoveTransferControlPoint(PLCore::uint32 nChannel, PLCore::uint32 nControlPoint, const PLMath::Vector2 &vDelta);

		//[-------------------------------------------------------]
		//[ Image                                                 ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Adds the final transfer function values to an image representation, bins along the x axis, values along the y-axis
		*
		*  @param[in,out] cDestinationImage
		*    Image were to add the additional visualization to, must be RGBA byte
		*  @param[in]     nChannel
		*    Channel
		*  @param[in]     cColor
		*    Color to use for the visualization
		*
		*  @note
		*    - For debugging and visualization
		*/
		PLVOLUME_API void AddToImage(PLGraphics::Image &cDestinationImage, PLCore::uint32 nChannel, const PLGraphics::Color3 &cColor);

		/**
		*  @brief
		*    Adds the control points to an image representation, bins along the x axis, values along the y-axis
		*
		*  @param[in,out] cDestinationImage
		*    Image were to add the additional visualization to, must be RGBA byte
		*  @param[in]     nChannel
		*    Channel
		*  @param[in]     cColor
		*    Color to use for the visualization
		*  @param[in]     cLineColor
		*    Line color to use for the visualization, "PLGraphics::Color3::Null" to draw no connection lines
		*  @param[in]     nSelectedControlPoint
		*    Selected control point, <0 if nothing selected
		*
		*  @note
		*    - For debugging and visualization
		*/
		PLVOLUME_API void AddControlPointsToImage(PLGraphics::Image &cDestinationImage, PLCore::uint32 nChannel, const PLGraphics::Color3 &cColor, const PLGraphics::Color3 &cLineColor, int nSelectedControlPoint = -1);

		/**
		*  @brief
		*    Finds the control point closest to a given coordinate, bins along the x axis, values along the y-axis
		*
		*  @param[in]  nChannel
		*    Channel
		*  @param[in]  nHeight
		*    Image height
		*  @param[in]  nX
		*    X coordinate [0,bins-1]
		*  @param[in]  nY
		*    Y coordinate [0,nHeight-1]
		*  @param[out] pfDistance
		*    If not a null pointer, receives the distance from the given coordinate to the coordinate to the selected control point
		*
		*  @return
		*    The control point closest to a given coordinate, <0 if nothing was found
		*/
		PLVOLUME_API int GetControlPointOnImage(PLCore::uint32 nChannel, PLCore::uint32 nHeight, int nX, int nY, float *pfDistance = nullptr) const;


	//[-------------------------------------------------------]
	//[ Public virtual TransferFunction functions             ]
	//[-------------------------------------------------------]
	public:
		PLVOLUME_API virtual PLGraphics::Image &GetImage() override;
		PLVOLUME_API virtual const PLGraphics::Image &GetConstImage() override;


	//[-------------------------------------------------------]
	//[ Public virtual PLCore::Loadable functions             ]
	//[-------------------------------------------------------]
	public:
		PLVOLUME_API virtual bool Unload() override;


	//[-------------------------------------------------------]
	//[ Private static data                                   ]
	//[-------------------------------------------------------]
	private:
		static const int MinIsoValueDistance;	/**< Minimum allowed distance between two iso-values */
		static const int CircleRadiusDraw;		/**< Circle radius for drawing */
		static const int CircleRadiusSelection;	/**< Circle radius for selection */


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::Array<TransferFunctionChannel*> m_lstTransferControlChannels;	/**< Transfer control channels */
		bool									m_bImageDirty;					/**< Is the image holding the transfer function marked to be dirty? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLVolume


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLVolume/TransferFunctionControl/TransferFunctionControl.inl"


#endif // __PLVOLUME_TRANSFERFUNCTIONCONTROL_H__
