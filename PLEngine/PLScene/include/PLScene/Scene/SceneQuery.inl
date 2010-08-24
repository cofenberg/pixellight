/*********************************************************\
 *  File: SceneQuery.inl                                 *
 *      Scene query inline implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the scene container this query operates on
*/
inline SceneContainer &SceneQuery::GetSceneContainer() const
{
	return *m_pSceneContainer;
}

/**
*  @brief
*    Returns the flags
*/
inline PLGeneral::uint32 SceneQuery::GetFlags() const
{
	return m_nFlags;
}

/**
*  @brief
*    Sets the flags
*/
inline void SceneQuery::SetFlags(PLGeneral::uint32 nFlags)
{
	m_nFlags = nFlags;
}

/**
*  @brief
*    Stops the currently running query
*/
inline void SceneQuery::Stop()
{
	m_nFlags |= StopQuery;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
