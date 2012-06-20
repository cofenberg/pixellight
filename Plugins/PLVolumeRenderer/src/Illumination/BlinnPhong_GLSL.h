/*********************************************************\
 *  File: BlinnPhong_GLSL.h                              *
 *      Fragment shader source code - GLSL (OpenGL 3.3 ("#version 330")
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


//[-------------------------------------------------------]
//[ Define helper macro                                   ]
//[-------------------------------------------------------]
#define STRINGIFY(ME) #ME


static const PLCore::String sSourceCode_Fragment = STRINGIFY(
// Uniforms
uniform vec3 LightColor;	// Light color

/**
*  @brief
*    Illumination
*
*  @param[in] SurfaceColor
*    Surface color
*  @param[in] SurfaceNormal
*    Normalized surface normal
*  @param[in] ViewingDirection
*    Normalized viewing direction
*  @param[in] LightDirection
*    Normalized light direction
*
*  @return
*    Illumination result
*/
vec3 Illumination(vec3 SurfaceColor, vec3 SurfaceNormal, vec3 ViewingDirection, vec3 LightDirection)
{
	// [TODO] Cleanup (from the book "Real-Time Volume Graphics")

	// material properties
	vec3 Kd = SurfaceColor; // diffuse
	vec3 Ks = vec3(0.2, 0.2, 0.2); // specular
	float shininess = 100.0; // shininess

	// Calculate halfway vector
	vec3 H = normalize(LightDirection + ViewingDirection);

	// Compute the diffuse term
	float diffuseLight = max(dot(LightDirection, SurfaceNormal), 0);
	vec3 diffuse = Kd * LightColor * diffuseLight;

	// Compute the specular term
	float specularLight = pow(max(dot(H, SurfaceNormal), 0), shininess);
	if (diffuseLight <= 0) specularLight = 0;
	vec3 specular = Ks * LightColor * specularLight;
	return diffuse + specular;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
