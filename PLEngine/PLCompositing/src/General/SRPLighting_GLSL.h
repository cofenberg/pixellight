/*********************************************************\
 *  File: SRPLighting_GLSL.h                             *
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


// GLSL vertex shader source code (the depreciated "attribute" and "varying" instead of "in" and "out" are used because some GPU drivers produced errors when using "in"/"out", beside this, we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sDiffuseOnly_GLSL_VS = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// In attributes\n\
attribute highp vec4 VertexPosition;			// Object space vertex position input\n\
#ifdef VS_TEXCOORD0\n\
	attribute highp vec2 VertexTexCoord0;		// Vertex texture coordinate 0 input\n\
#endif\n\
#ifdef VS_NORMAL\n\
	attribute highp vec3 VertexNormal;			// Object space vertex normal input\n\
	#ifdef VS_TANGENT_BINORMAL\n\
		attribute highp vec3 VertexTangent;		// Object space vertex tangent input\n\
		attribute highp vec3 VertexBinormal;	// Object space vertex binormal input\n\
	#endif\n\
#endif\n\
\n\
// Out attributes\n\
#ifdef VS_TEXCOORD0\n\
	varying highp vec2 VertexTexCoordVS;		// Vertex texture coordinate 0 output\n\
#endif\n\
varying highp vec3 VertexPositionVS;			// View space vertex position output\n\
#ifdef VS_NORMAL\n\
	varying highp vec3 VertexNormalVS;			// View space vertex normal output\n\
	#ifdef VS_TANGENT_BINORMAL\n\
		varying highp vec3 VertexTangentVS;		// View space vertex tangent output\n\
		varying highp vec3 VertexBinormalVS;	// View space vertex binormal output\n\
		#ifdef VS_PARALLAXMAPPING\n\
			varying highp vec3 EyeVecVS;		// Tangent space vector pointing from the pixel to the eye point\n\
		#endif\n\
	#endif\n\
#endif\n\
\n\
// Uniforms\n\
#if defined(VS_NORMAL) && defined(VS_TWOSIDEDLIGHTING)\n\
	uniform highp float NormalScale;					// Normal scale (negative to flip normals)\n\
#endif\n\
uniform highp mat4 ObjectSpaceToViewSpaceMatrix;		// Object space to view space matrix\n\
uniform highp mat4 ObjectSpaceToClipSpaceMatrix;		// Object space to clip space matrix\n\
#if defined(VS_NORMAL) && defined(VS_TANGENT_BINORMAL) && defined(VS_PARALLAXMAPPING)\n\
	uniform highp vec3 EyePos;							// Object space eye position\n\
#endif\n\
\n\
// Programs\n\
void main()\n\
{\n\
	// Calculate the clip space vertex position\n\
	gl_Position = ObjectSpaceToClipSpaceMatrix*VertexPosition;\n\
\n\
#ifdef VS_TEXCOORD0\n\
	// Pass through the vertex texture coordinate 0\n\
	VertexTexCoordVS = VertexTexCoord0;\n\
#endif\n\
\n\
	// Transform vertex position to view space\n\
	highp vec4 viewSpacePosition = ObjectSpaceToViewSpaceMatrix*VertexPosition;\n\
	VertexPositionVS = viewSpacePosition.xyz;\n\
\n\
#ifdef VS_NORMAL\n\
	// Transform vertex normal to view space\n\
	VertexNormalVS = mat3(ObjectSpaceToViewSpaceMatrix)*VertexNormal;\n\
\n\
	#ifdef VS_TWOSIDEDLIGHTING\n\
		// Allow vertex normal flip if required for proper two sided lighting\n\
		VertexNormalVS *= NormalScale;\n\
	#endif\n\
\n\
	#ifdef VS_TANGENT_BINORMAL\n\
		// Transform vertex tangent and binormal to view space\n\
		VertexTangentVS  = mat3(ObjectSpaceToViewSpaceMatrix)*VertexTangent;\n\
		VertexBinormalVS = mat3(ObjectSpaceToViewSpaceMatrix)*VertexBinormal;\n\
\n\
		#ifdef VS_PARALLAXMAPPING\n\
			// Calculate the tangent space vector pointing from the pixel to the eye point for parallax mapping	\n\
			EyeVecVS = mat3(VertexTangent, VertexBinormal, VertexNormal)*(EyePos - VertexPosition.xyz);\n\
		#endif\n\
	#endif\n\
#endif\n\
}";


// GLSL fragment shader source code - divided into two parts because I got the following VC compiler error: "error C2026: string too big, trailing characters truncated" (the depreciated "varying" instead of "in" is used because some GPU drivers produced errors when using "in", beside this, we want to stay compatible to OpenGL ES 2.0)
static const PLGeneral::String sDiffuseOnly_GLSL_FS_Part1 = "\
// GLSL preprocessor directives\n\
// #version 100	// OpenGL ES 2.0 requires 100, but modern OpenGL doesn't support 100, so we just don't define the version...\n\
\n\
// Attributes\n\
#ifdef FS_TEXCOORD0\n\
	varying highp vec2 VertexTexCoordVS;		// Vertex texture coordinate 0 from vertex shader\n\
#endif\n\
	varying highp vec3 VertexPositionVS;		// View space vertex position from vertex shader\n\
#ifdef FS_NORMAL\n\
	varying highp vec3 VertexNormalVS;			// View space vertex normal from vertex shader\n\
	#ifdef FS_TANGENT_BINORMAL\n\
		varying highp vec3 VertexTangentVS;		// View space vertex tangent from vertex shader\n\
		varying highp vec3 VertexBinormalVS;	// View space vertex binormal from vertex shader\n\
		#ifdef FS_PARALLAXMAPPING\n\
			varying highp vec3 EyeVecVS;		// Tangent space vector pointing from the pixel to the eye point from vertex shader\n\
		#endif\n\
	#endif\n\
#endif\n\
\n\
// Uniforms\n\
uniform lowp vec3 DiffuseColor;\n\
#ifdef FS_DIFFUSEMAP\n\
	uniform lowp sampler2D DiffuseMap;\n\
	#ifdef FS_ALPHATEST\n\
		uniform lowp float AlphaReference;\n\
	#endif\n\
#endif\n\
#ifdef FS_DIFFUSERAMPMAP\n\
     uniform highp sampler1D DiffuseRampMap;\n\
#endif\n\
#ifdef FS_REFLECTION\n\
	uniform lowp vec3  ReflectionColor;\n\
	uniform lowp float Reflectivity;\n\
	#ifdef FS_REFLECTIVITYMAP\n\
		uniform lowp sampler2D ReflectivityMap;\n\
	#endif\n\
	#ifdef FS_FRESNELREFLECTION\n\
		uniform highp vec2 FresnelConstants; // x = R0 [0..1] and y = Power, always >0\n\
	#endif\n\
	#ifdef FS_2DREFLECTIONMAP\n\
		uniform lowp  sampler2D ReflectionMap;\n\
		uniform highp mat3      ViewSpaceToWorldSpace;		// View space to world space transform matrix\n\
	#elif defined(FS_CUBEREFLECTIONMAP)\n\
		uniform lowp  samplerCube ReflectionMap;\n\
		uniform highp mat3        ViewSpaceToWorldSpace;	// View space to world space transform matrix\n\
	#endif\n\
#endif\n\
#ifdef FS_NORMALMAP\n\
	uniform lowp sampler2D NormalMap;\n\
	uniform lowp float     NormalMapBumpiness;\n\
	#ifdef FS_DETAILNORMALMAP\n\
		uniform lowp sampler2D DetailNormalMap;\n\
		uniform lowp float     DetailNormalMapBumpiness;\n\
		uniform lowp vec2      DetailNormalMapUVScale;\n\
	#endif\n\
#endif\n\
#ifdef FS_PARALLAXMAPPING\n\
	uniform lowp    sampler2D HeightMap;\n\
	uniform mediump vec2      ParallaxScaleBias;\n\
#endif\n\
#ifdef FS_DIRECTIONAL\n\
	uniform vec3 LightDirection;								// View space normalized light direction\n\
#else\n\
	uniform vec3  LightPosition;								// View space light position\n\
	uniform float LightRadius;									// View space light radius\n\
	#ifdef FS_PROJECTIVE_POINT\n\
		uniform samplerCube ProjectivePointCubeMap;				// Cube map texture for projective point light\n\
		uniform mat3        ViewSpaceToCubeMapSpace;			// View space to cube map space transform matrix\n\
	#else\n\
		#ifdef FS_SPOT\n\
			uniform vec3	      LightDirection;				// View space normalized light direction\n\
			#ifdef FS_SPOT_PROJECTIVE\n\
				uniform sampler2D ProjectiveSpotMap;			// Texture for projective spot light\n\
				uniform mat4      ViewSpaceToSpotMapSpace;		// View space to spot map space transform matrix\n\
			#endif\n\
			#ifdef FS_SPOT_CONE\n\
				#ifdef FS_SPOT_SMOOTHCONE\n\
					uniform vec2  SpotConeCos;					// Cosinus of the outer and inner cone angle in view space\n\
				#else\n\
					uniform float SpotConeCos;					// Cosinus of the cone angle in view space\n\
				#endif\n\
			#endif\n\
		#endif\n\
	#endif\n\
	#ifdef FS_SHADOWMAPPING\n\
		#ifdef FS_SPOT\n\
			uniform sampler2DShadow ShadowMap;					// 2D shadow map - [TODO] This will not work with OpenGL ES 2.0 because there's no sampler2DShadow/shadow2DProj\n\
			uniform mat4			ViewSpaceToShadowMapSpace;	// View space to shadow map space transform matrix\n\
		#else\n\
			uniform samplerCube ShadowMap;						// Cube shadow map\n\
			uniform mat3        ViewSpaceToShadowCubeMapSpace;	// View space to shadow cube map space transform matrix\n\
			uniform float	    InvLightRadius;					// 1/LightRadius\n\
		#endif\n\
		#ifdef FS_SOFTSHADOWMAPPING\n\
			uniform float TexelSize;							// Shadow map texel size\n\
		#endif\n\
	#endif\n\
#endif\n\
uniform lowp vec3 LightColor;	// Light color\n\
#ifdef FS_SPECULAR\n\
	uniform lowp vec3  SpecularColor;\n\
	uniform lowp float SpecularExponent;\n\
	#ifdef FS_SPECULARMAP\n\
		uniform lowp sampler2D SpecularMap;\n\
	#endif\n\
	#ifdef FS_SPECULARRAMPMAP\n\
		uniform highp sampler1D SpecularRampMap;\n\
	#endif\n\
#endif\n\
#ifdef FS_EDGERAMPMAP\n\
	uniform highp sampler1D EdgeRampMap;\n\
#endif\n\
\n\
// Programs\n\
#ifdef FS_FRESNELREFLECTION\n\
	highp float fresnel(highp vec3 light, highp vec3 normal, highp vec2 constants)\n\
	{\n\
		// Light and normal are assumed to be normalized\n\
		// constants.x = R0 [0..1]\n\
		// constants.y = Power, always >0\n\
		highp float cosAngle = clamp(1.0f - dot(light, normal), 0.0f, 1.0f); // We REALLY need to clamp in here or pow may hurt us when using negative numbers!\n\
		return constants.x + (1 - constants.x) * pow(cosAngle, constants.y);\n\
	}\n\
#endif\n\
\n\
// Performs the Blinn-Phong lighting calculation\n\
lowp vec3 BlinnPhong(highp vec3 lightVector, lowp vec3 lightColor, highp vec3 viewVector, highp vec3 normalVector, lowp vec3 diffuseColor, lowp vec3 specularColor, lowp float specularExponent)\n\
{\n\
	// [TODO] There seem to be invalid normal vectors here (NAN)\n\
	if (isnan(normalVector.x) || isnan(normalVector.y) || isnan(normalVector.z))\n\
		normalVector = vec3(0, 0, 1);\n\
	if (isnan(lightVector.x) || isnan(lightVector.y) || isnan(lightVector.z))\n\
		lightVector = vec3(0, 0, 1);\n\
	if (isnan(viewVector.x) || isnan(viewVector.y) || isnan(viewVector.z))\n\
		viewVector = vec3(0, 0, 1);\n\
\n\
	// Diffuse term\n\
	highp float diffuse = clamp(dot(lightVector, normalVector), 0.0f, 1.0f);\n\
	#ifdef FS_DIFFUSERAMPMAP\n\
		diffuse *= texture1D(DiffuseRampMap, diffuse).x;\n\
	#endif\n\
	lowp vec3 diffuseLighting = diffuse*diffuseColor*lightColor;\n\
\n\
	// Specular term\n\
	#ifdef FS_SPECULAR\n\
		// Calculate the half vector between the light vector and the view vector. This is cheaper then calculating the actual reflective vector.\n\
		highp vec3 halfVector = normalize(lightVector + viewVector);\n\
\n\
		// Ensure that the specular exponent is never ever <=0, else NANs may be produced by pow!\n\
		#define FLT_MIN 1.175494351e-38F // Minimum positive value\n\
		if (specularExponent < FLT_MIN)\n\
			specularExponent = FLT_MIN;\n\
		#undef FLT_MIN\n\
\n\
		// Specular term\n\
		highp float specular = pow(clamp(dot(halfVector, normalVector), 0.0f, 1.0f), specularExponent);\n\
		lowp vec3 specularLighting = specular*specularColor*lightColor;\n\
		#ifdef FS_SPECULARRAMPMAP\n\
			specularLighting *= texture1D(SpecularRampMap, specular).x;\n\
		#endif\n\
	#else\n\
		#define specularLighting vec3(0, 0, 0)\n\
	#endif\n\
\n\
	// Edge detection\n\
	#ifdef FS_EDGERAMPMAP\n\
		lowp float edge = texture1D(EdgeRampMap, max(0, dot(viewVector, normalVector))).x;\n\
	#else\n\
		#define edge 1\n\
	#endif\n\
\n\
	// Final color\n\
	return (diffuseLighting + specularLighting)*edge;\n\
}\n\
\n\
#ifdef FS_SOFTSHADOWMAPPING\n\
	// Fake PCF (percentage-closer filtering)\n\
	highp vec4 texPCF(highp sampler2DShadow map, highp vec4 location, highp vec2 offset)\n\
	{\n\
		return shadow2DProj(map, vec4(location.xy + location.w*offset, location.z, location.w));\n\
	}\n\
\n\
	highp float texPCF(highp samplerCube map, highp vec3 location, highp vec3 offset)\n\
	{\n\
		// Get shadow map data\n\
		highp vec4 shadowMap = textureCube(map, location + offset);\n\
\n\
		// Unpack\n\
		return shadowMap.r/1 + shadowMap.g/256 + shadowMap.b/65536 + shadowMap.a/16777216;\n\
	}\n\
#endif\n\
\n\
#ifdef FS_SHADOWMAPPING\n\
	highp float texPCF(highp samplerCube map, highp vec3 location)\n\
	{\n\
		// Get shadow map data\n\
		highp vec4 shadowMap = textureCube(map, location);\n\
\n\
		// Unpack\n\
		return shadowMap.r/1 + shadowMap.g/256 + shadowMap.b/65536 + shadowMap.a/16777216;\n\
	}\n\
#endif";
static const PLGeneral::String sDiffuseOnly_GLSL_FS_Part2 = "\
\n\
void main()\n\
{\n\
	// Define were the texture coordinates come from\n\
	#ifdef FS_TEXCOORD0\n\
		highp vec2 TexCoord0 = VertexTexCoordVS;\n\
	#endif\n\
\n\
	#ifdef FS_PARALLAXMAPPING\n\
		// Plain parallax mapping works by offsetting the texture coordinate by approximating\n\
		// where the ray would hit the surface. The heightmap indicates how far to offset.\n\
		// The approximation assumes that all heights in the height-map is equal, which of\n\
		// course won't be the case, but if the bumpmap is fairly smooth it works well enough.\n\
		highp vec3  eyeVec = normalize(EyeVecVS);\n\
		lowp  float scale  = ParallaxScaleBias.x;\n\
		lowp  float bias   = ParallaxScaleBias.y;\n\
		lowp  float height = texture2D(HeightMap, TexCoord0).r;\n\
\n\
		// First offset pass with offset limiting (no division through eyeVec.z)\n\
		lowp float offset = height*scale + bias;\n\
		highp vec2 textureCoordinate = TexCoord0 + offset*eyeVec.xy;\n\
\n\
		// For better quality: Refine the parallax by making another lookup at where we ended\n\
		// up in the first parallax computation, then averaging the results.\n\
		lowp float height2 = (height + texture2D(HeightMap, textureCoordinate).r)*0.5f;\n\
		offset = height2*scale + bias;\n\
		TexCoord0 = TexCoord0 + offset*eyeVec.xy;\n\
	#endif\n\
\n\
	// Get the diffuse color\n\
	#ifdef FS_DIFFUSEMAP\n\
		lowp vec4 diffuseMapTexel = texture2D(DiffuseMap, TexCoord0);\n\
		#ifdef FS_ALPHATEST\n\
			// Perform an alpha test to discard fragments\n\
			if (diffuseMapTexel.a < AlphaReference)\n\
				discard; // Throw the fragment away and don't draw it!\n\
		#endif\n\
		#ifdef FS_GAMMACORRECTION\n\
			diffuseMapTexel.rgb = pow(diffuseMapTexel.rgb, vec3(2.2f, 2.2f, 2.2f));	// Perform sRGB to linear space conversion (gamma correction)\n\
		#endif\n\
		lowp vec3 diffuseColor = diffuseMapTexel.rgb*DiffuseColor;\n\
	#else\n\
		lowp vec3 diffuseColor = DiffuseColor;\n\
	#endif\n\
\n\
	// Get the view space normal vector\n\
	#ifdef FS_NORMAL\n\
		#ifdef FS_NORMALMAP\n\
			// Fetch normal texel data\n\
			#if defined(FS_NORMALMAP_DXT5_XGXR) || defined(FS_NORMALMAP_LATC2)\n\
				// Fetch the xy-components of the normal and reconstruct the z-component\n\
				lowp vec3 normal;\n\
				#ifdef FS_NORMALMAP_DXT5_XGXR\n\
					normal.xy = texture2D(NormalMap, TexCoord0).ag*2 - 1;\n\
				#else\n\
					normal.xy = texture2D(NormalMap, TexCoord0).ra*2 - 1;\n\
				#endif\n\
				normal.z  = sqrt(clamp(1 - normal.x*normal.x - normal.y*normal.y, 0.0f, 1.0f));\n\
			#else\n\
				lowp vec3 normal = texture2D(NormalMap, TexCoord0).xyz*2 - 1;\n\
			#endif\n\
			normal.xy *= NormalMapBumpiness;\n\
\n\
			// Fetch and apply detail normal texel data\n\
			#ifdef FS_DETAILNORMALMAP\n\
				#if defined(FS_DETAILNORMALMAP_DXT5_XGXR) || defined(FS_DETAILNORMALMAP_LATC2)\n\
					// Fetch the xy-components of the normal and reconstruct the z-component\n\
					lowp vec3 detailNormal;\n\
					#ifdef FS_DETAILNORMALMAP_DXT5_XGXR\n\
						detailNormal.xy = texture2D(DetailNormalMap, TexCoord0*DetailNormalMapUVScale).ag*2 - 1;\n\
					#else\n\
						detailNormal.xy = texture2D(DetailNormalMap, TexCoord0*DetailNormalMapUVScale).ra*2 - 1;\n\
					#endif\n\
					detailNormal.z  = sqrt(clamp(1 - detailNormal.x*detailNormal.x - detailNormal.y*detailNormal.y, 0.0f, 1.0f));\n\
				#else\n\
					lowp detailNormal = texture2D(DetailNormalMap, TexCoord0*DetailNormalMapUVScale).xyz*2 - 1;\n\
				#endif\n\
\n\
				// Just add the detail normal to the standard normal\n\
				normal = normal + detailNormal*DetailNormalMapBumpiness;\n\
			#endif\n\
\n\
			// Transform normal to view space\n\
			normal = normalize(normal.x*VertexTangentVS + normal.y*VertexBinormalVS + normal.z*VertexNormalVS);\n\
		#else\n\
			lowp vec3 normal = normalize(VertexNormalVS);\n\
		#endif\n\
		if (isnan(normal.x) || isnan(normal.y) || isnan(normal.z))\n\
			normal = vec3(0, 0, 1); // I had situations with invalid normal vectors...\n\
	#else\n\
		// Define a dummy normal so, when using reflections, we get at least some 'kind of reflection' effect\n\
		#define normal vec3(0, 0, 1)\n\
	#endif\n\
\n\
	// Apply reflection - modifies the diffuse color\n\
	#ifdef FS_REFLECTION\n\
		// Reflectivity = 0.0...1.0=no reflection...full reflection\n\
		lowp float reflectivity = Reflectivity;\n\
		// Fresnel reflection\n\
		#ifdef FS_FRESNELREFLECTION\n\
			reflectivity *= fresnel(normalize(-VertexPositionVS), normal, FresnelConstants);\n\
		#endif\n\
		// Reflectivity map\n\
		#ifdef FS_REFLECTIVITYMAP\n\
			reflectivity *= texture2D(ReflectivityMap, TexCoord0).r;\n\
		#endif\n\
\n\
		// Reflection color\n\
		lowp vec3 reflectionColor = vec3(1, 1, 1);\n\
		#ifdef FS_2DREFLECTIONMAP\n\
			// Spherical environment mapping\n\
			highp vec3  r = ViewSpaceToWorldSpace*normalize(reflect(VertexPositionVS, normal));\n\
			highp float m = 2*sqrt(r.x*r.x + r.y*r.y + (r.z + 1)*(r.z + 1));\n\
			#define FLT_MIN 1.175494351e-38F // Minimum positive value\n\
			if (m < FLT_MIN)\n\
				m = FLT_MIN;\n\
			#undef FLT_MIN\n\
			reflectionColor = texture2D(ReflectionMap, vec2(r.x/m + 0.5f, 1 - (r.y/m + 0.5f))).rgb;\n\
		#elif defined(FS_CUBEREFLECTIONMAP)\n\
			// Cubic environment mapping\n\
			// There's no need to normalize the reflection vector when using cube maps\n\
			reflectionColor = textureCube(ReflectionMap, ViewSpaceToWorldSpace*reflect(VertexPositionVS, normal)).rgb;\n\
		#endif\n\
		// Perform sRGB to linear space conversion (gamma correction)\n\
		#ifdef FS_GAMMACORRECTION\n\
			reflectionColor = pow(reflectionColor, vec3(2.2f, 2.2f, 2.2f));\n\
		#endif\n\
		// Apply reflection color\n\
		reflectionColor *= ReflectionColor;\n\
\n\
		// Calculate the final diffuse color after reflection was applied\n\
		diffuseColor = mix(diffuseColor, reflectionColor, reflectivity);\n\
	#endif\n\
\n\
	// Specular color and exponent\n\
	#ifdef FS_SPECULAR\n\
		#ifdef FS_SPECULARMAP\n\
			lowp vec4  specularMapTexel = texture2D(SpecularMap, TexCoord0);\n\
			lowp vec3  specularColor    = specularMapTexel.rgb*SpecularColor;\n\
			lowp float specularExponent = specularMapTexel.a*SpecularExponent;\n\
		#else\n\
			lowp vec3 specularColor = SpecularColor;\n\
			#define specularExponent SpecularExponent\n\
		#endif\n\
	#else\n\
		#define specularColor vec3(0, 0, 0)\n\
		#define specularExponent 0\n\
	#endif\n\
\n\
	// Perform the lighting calculation in view space\n\
	highp vec3 position = VertexPositionVS;\n\
	#ifdef FS_DIRECTIONAL\n\
		// Perform the Blinn-Phong lighting calculation\n\
		lowp vec3 lightingColor = BlinnPhong(LightDirection, LightColor, normalize(-position), normal, diffuseColor, specularColor, specularExponent);\n\
\n\
		// Not shadowed by default\n\
		#define shadow 1\n\
	#else\n\
		// Calculate the view space light vector pointing from the position to the light position\n\
		highp vec3 lightVector = LightPosition - position;\n\
\n\
		// Get the distance between the light and position\n\
		highp float distance = length(lightVector);\n\
\n\
		// If the position is outside of area of effect, discard position\n\
		if (distance > LightRadius) {\n\
			// Early escape: Not influcenced by the light\n\
			#ifdef FS_DISCARD\n\
				discard;\n\
			#else\n\
				gl_FragColor = vec4(0, 0, 0, 0);\n\
				return;\n\
			#endif\n\
		}\n\
\n\
		// Perform shadow mapping\n\
		#ifdef FS_SHADOWMAPPING\n\
			#ifdef FS_SPOT\n\
				// Calculate the shadow vector\n\
				highp vec4 shadowVector = ViewSpaceToShadowMapSpace*vec4(position, 1);\n\
\n\
				// Shadow mapping\n\
				#ifdef FS_SOFTSHADOWMAPPING\n\
					// Fake PCF (percentage-closer filtering)\n\
					highp float shadow = (texPCF(ShadowMap, shadowVector, vec2(-TexelSize,  TexelSize)).x +\n\
										  texPCF(ShadowMap, shadowVector, vec2( TexelSize,  TexelSize)).x +\n\
										  texPCF(ShadowMap, shadowVector, vec2(-TexelSize, -TexelSize)).x +\n\
										  texPCF(ShadowMap, shadowVector, vec2( TexelSize, -TexelSize)).x) * 0.25f;\n\
				#else\n\
					highp float shadow = shadow2DProj(ShadowMap, shadowVector).x;\n\
				#endif\n\
			#else\n\
				// Shadow mapping\n\
				highp vec3 shadowVector = ViewSpaceToShadowCubeMapSpace*(-lightVector*InvLightRadius);\n\
				highp float shadowVecLength = length(shadowVector);\n\
				#ifdef FS_SOFTSHADOWMAPPING\n\
					// Shadowed?\n\
					highp float shadow = (shadowVecLength < texPCF(ShadowMap, shadowVector, vec3(TexelSize, TexelSize, TexelSize))) ? 0.16666667f : 0.0f;\n\
					shadow += (shadowVecLength < texPCF(ShadowMap, shadowVector, vec3(-TexelSize, -TexelSize, -TexelSize))) ? 0.16666667f : 0.0f;\n\
					shadow += (shadowVecLength < texPCF(ShadowMap, shadowVector, vec3( TexelSize, -TexelSize, -TexelSize))) ? 0.16666667f : 0.0f;\n\
					shadow += (shadowVecLength < texPCF(ShadowMap, shadowVector, vec3(-TexelSize,  TexelSize, -TexelSize))) ? 0.16666667f : 0.0f;\n\
					shadow += (shadowVecLength < texPCF(ShadowMap, shadowVector, vec3( TexelSize, -TexelSize,  TexelSize))) ? 0.16666667f : 0.0f;\n\
					shadow += (shadowVecLength < texPCF(ShadowMap, shadowVector, vec3(-TexelSize,  TexelSize,  TexelSize))) ? 0.16666667f : 0.0f;\n\
					shadow = clamp(shadow, 0.0f, 1.0f);\n\
				#else\n\
					// Unpack\n\
					highp float depthValue = texPCF(ShadowMap, shadowVector);\n\
\n\
					// Shadowed?\n\
					highp float shadow = (shadowVecLength < depthValue) ? 1 : 0;\n\
				#endif\n\
			#endif\n\
\n\
			// Is the position completely shadowed?\n\
			if (shadow <= 0) {\n\
				// Early escape: Not influcenced by the light\n\
				#ifdef FS_DISCARD\n\
					discard;\n\
				#else\n\
					gl_FragColor = vec4(0, 0, 0, 0);\n\
					return;\n\
				#endif\n\
			}\n\
		#else\n\
			// Not shadowed by default\n\
			#define shadow 1\n\
		#endif\n\
\n\
		// Get the light color (lightColor)\n\
		#ifdef FS_PROJECTIVE_POINT\n\
			// Calculate the cube map space vector ('-' -> The light is the source of the ray, not the surface!)\n\
			highp vec3 cubeMapVector = ViewSpaceToCubeMapSpace*(-lightVector);\n\
\n\
			// Get cube map texture for projective point light\n\
			lowp vec3 lightColor = textureCube(ProjectivePointCubeMap, cubeMapVector).rgb;\n\
			// Perform sRGB to linear space conversion (gamma correction)\n\
			#ifdef FS_GAMMACORRECTION\n\
				lightColor = pow(lightColor, vec3(2.2f, 2.2f, 2.2f));\n\
			#endif\n\
			// Apply light color\n\
			lightColor *= LightColor;\n\
		#else\n\
			// Start with the original light color\n\
			lowp vec3 lightColor = LightColor;\n\
\n\
			// Add spot light\n\
			#ifdef FS_SPOT\n\
				// Projective spot map\n\
				#ifdef FS_SPOT_PROJECTIVE\n\
					// Calculate the projective spot map texture coordinate\n\
					highp vec4 projectiveSpotMapUV = ViewSpaceToSpotMapSpace*(-vec4(position, 1));\n\
\n\
					// No back projection, please!\n\
					if (projectiveSpotMapUV.z < 0) {\n\
						// Early escape: Not influcenced by the light\n\
						#ifdef FS_DISCARD\n\
							discard;\n\
						#else\n\
							gl_FragColor = vec4(0, 0, 0, 0);\n\
							return;\n\
						#endif\n\
					}\n\
\n\
					// Get the projective spot map texel data\n\
					lowp vec3 projectiveSpotMapTexel = texture2DProj(ProjectiveSpotMap, projectiveSpotMapUV).rgb;\n\
					// Perform sRGB to linear space conversion (gamma correction)\n\
					#ifdef FS_GAMMACORRECTION\n\
						projectiveSpotMapTexel = pow(projectiveSpotMapTexel, vec3(2.2f, 2.2f, 2.2f));\n\
					#endif\n\
					// Modulate the color of the light using the projective spot map texel data\n\
					lightColor *= projectiveSpotMapTexel;\n\
				#endif\n\
\n\
				// Spot light with cone\n\
				#ifdef FS_SPOT_CONE\n\
					// Calculate the angle between the current position and the spot light\n\
					highp float currentSpotConeCos = dot(normalize(position - LightPosition), LightDirection);\n\
\n\
					// Spot light with smooth cone\n\
					#ifdef FS_SPOT_SMOOTHCONE\n\
						// Get the current smooth spot cone attenuation\n\
						highp float currentSpotConeCosAttenuation = smoothstep(SpotConeCos.x, SpotConeCos.y, currentSpotConeCos);\n\
\n\
						// Is the position completly outside the spot cone?\n\
						if (currentSpotConeCosAttenuation <= 0) {\n\
							// Early escape: The position is outside the light cone and therefore not influcenced by the light\n\
							#ifdef FS_DISCARD\n\
								discard;\n\
							#else\n\
								gl_FragColor = vec4(0, 0, 0, 0);\n\
								return;\n\
							#endif\n\
						}\n\
\n\
						// Modulate the color of the light using the current smooth spot cone attenuation\n\
						lightColor *= currentSpotConeCosAttenuation;\n\
					#else\n\
						// A position is inside or outside the spot cone, there is no 'in between'\n\
						if (SpotConeCos > currentSpotConeCos) {\n\
							// Early escape: The position is outside the light cone and therefore not influcenced by the light\n\
							#ifdef FS_DISCARD\n\
								discard;\n\
							#else\n\
								gl_FragColor = vec4(0, 0, 0, 0);\n\
								return;\n\
							#endif\n\
						}\n\
					#endif\n\
				#endif\n\
			#endif\n\
		#endif\n\
\n\
		// Perform the lighting calculation in view space\n\
		lowp vec3 lightingColor = BlinnPhong(normalize(lightVector), lightColor, -normalize(position), normal, diffuseColor, specularColor, specularExponent);\n\
\n\
		// Apply attenuation\n\
		lightingColor *= clamp(1.0f - distance/LightRadius, 0.0f, 1.0f);\n\
	#endif\n\
\n\
	// Calculate the fragment color\n\
	gl_FragColor = vec4(lightingColor*shadow, 1.0f);\n\
\n\
}";
static const PLGeneral::String sDiffuseOnly_GLSL_FS = sDiffuseOnly_GLSL_FS_Part1 + sDiffuseOnly_GLSL_FS_Part2;
