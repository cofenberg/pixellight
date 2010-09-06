/*********************************************************\
 *  File: SRPDeferredGBuffer_Cg.h                        *
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
 *
 *  Definitions:
 *  - USE_DIFFUSEMAP:                Take diffuse map into account
 *    - USE_ALPHATEST:               Use alpha test to discard fragments (USE_DIFFUSEMAP must be defined!)
 *  - USE_SPECULAR:                  Use specular
 *    - USE_SPECULARMAP:             Take specular map into account (USE_SPECULAR must be set, too)
 *  - USE_NORMALMAP:                 Take normal map into account
 *    - NORMALMAP_DXT5_XGXR:         DXT5 XGXR compressed normal map (USE_NORMALMAP must be defined and NORMALMAP_LATC2 not!)
 *    - NORMALMAP_LATC2:             LATC2 compressed normal map (USE_NORMALMAP must be defined and NORMALMAP_DXT5_XGXR not!)
 *    - USE_DETAILNORMALMAP:         Take detail normal map into account (USE_NORMALMAP must be defined!)
 *      - DETAILNORMALMAP_DXT5_XGXR: DXT5 XGXR compressed detail normal map (USE_NORMALMAP & USE_DETAILNORMALMAP must be defined and DETAILNORMALMAP_LATC2 not!)
 *      - DETAILNORMALMAP_LATC2:     LATC2 compressed detail normal map (USE_NORMALMAP & USE_DETAILNORMALMAP must be defined and DETAILNORMALMAP_DXT5_XGXR not!)
 *  - USE_PARALLAXMAPPING:           Perform parallax mapping
 *  - USE_AMBIENTOCCLUSIONMAP:       Use ambient occlusion map
 *  - USE_LIGHTMAP:                  Use light map
 *  - USE_EMISSIVEMAP:               Use emissive map
 *  - USE_GLOW:                      Use glow
 *    - USE_GLOWMAP:                 Use glow map (USE_GLOW must be defined!)
 *  - USE_REFLECTION:                Use reflection
 *    - USE_FRESNELREFLECTION:       Use fresnel reflection (USE_REFLECTION must be defined!)
 *    - USE_REFLECTIVITYMAP:         Use reflectivity map (USE_REFLECTION and USE_FRESNELREFLECTION or USE_2DREFLECTIONMAP or USE_CUBEREFLECTIONMAP must be defined!)
 *    - USE_2DREFLECTIONMAP:         Use 2D reflection mapping (USE_REFLECTION must be defined, can't be set together with USE_CUBEREFLECTIONMAP!)
 *    - USE_CUBEREFLECTIONMAP:       Use cube reflection mapping (USE_REFLECTION must be defined, can't be set together with USE_2DREFLECTIONMAP!)
 *  - USE_GAMMACORRECTION:           Use gamma correction (sRGB to linear space)
*********************************************************/


const static char *pszDeferredGBuffer_Cg_VS = "\n\
// Vertex input\n\
struct VS_INPUT {\n\
	float4 position : POSITION;		// Object space vertex position\n\
	float2 texUV	: TEXCOORD0;	// Vertex texture coordinate\n\
#if defined(USE_AMBIENTOCCLUSIONMAP) || defined(USE_LIGHTMAP)\n\
	float2 texAOUV	: TEXCOORD1;	// Vertex ambient occlusion map and/or light map texture coordinate\n\
#endif\n\
	float3 normal   : NORMAL;		// Object space vertex normal\n\
#ifdef TANGENT_BINORMAL\n\
	float3 tangent  : TANGENT;		// Object space vertex tangent\n\
	float3 binormal : BINORMAL;		// Object space vertex tangent\n\
#endif\n\
};\n\
\n\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 position    : POSITION;	// Clip space vertex position\n\
#if defined(USE_AMBIENTOCCLUSIONMAP) || defined(USE_LIGHTMAP)\n\
	float4 texUV	   : TEXCOORD0;	// Vertex texture coordinate, zw for ambient occlusion map and/or light map texture coordinate\n\
#else\n\
	float2 texUV	   : TEXCOORD0;	// Vertex texture coordinate\n\
#endif\n\
	float4 normalDepth : TEXCOORD1; // View space vertex normal and view space linear depth [0...far plane]\n\
	float3 tangent     : TEXCOORD2;	// View space vertex tangent\n\
	float3 binormal    : TEXCOORD3;	// View space vertex tangent\n\
	float3 eyeVec      : TEXCOORD4;	// Tangent space vector pointing from the pixel to the eye point\n\
#ifdef USE_REFLECTION\n\
	float3 positionVS  : TEXCOORD5;	// View space vertex position\n\
#endif\n\
};\n\
\n\
// Main function\n\
VS_OUTPUT main(VS_INPUT IN						// Vertex input\n\
#ifdef TWOSIDED\n\
	, uniform float     NormalScale				// Normal scale (negative to flip normals)\n\
#endif\n\
	, uniform float3    EyePos					// Object space eye position\n\
	, uniform float4x4  WorldVP					// World view projection matrix\n\
	, uniform float4x4  WorldV					// World view matrix\n\
#ifdef USE_DISPLACEMENTMAP\n\
	, uniform sampler2D DisplacementMap			// Displacement map\n\
	, uniform float2    DisplacementScaleBias	// Displacement scale and bias\n\
#endif\n\
	)\n\
{\n\
	VS_OUTPUT OUT;\n\
\n\
#ifdef USE_DISPLACEMENTMAP\n\
	// Sample displacement map\n\
	float displacement = tex2Dlod(DisplacementMap, float4(IN.texUV, 0, 0)).r;\n\
	displacement = (displacement*DisplacementScaleBias.x) + DisplacementScaleBias.y;\n\
	float4 vertexPosition = float4(IN.position.xyz + displacement*IN.normal, 1);\n\
#else\n\
	#define vertexPosition IN.position\n\
#endif\n\
\n\
	// Transform vertex position to clip space\n\
	OUT.position = mul(WorldVP, vertexPosition);\n\
\n\
	// Pass through the vertex texture coordinate\n\
	OUT.texUV.xy = IN.texUV;\n\
\n\
	// Pass through the vertex ambient occlusion texture map and/or light map coordinate\n\
#if defined(USE_AMBIENTOCCLUSIONMAP) || defined(USE_LIGHTMAP)\n\
	OUT.texUV.zw = IN.texAOUV;\n\
#endif\n\
\n\
	// Transform vertex normal to view space\n\
	OUT.normalDepth.xyz = mul((float3x3)WorldV, IN.normal);\n\
#ifdef TWOSIDED\n\
	// Allow vertex normal flip if required for proper two sided lighting\n\
	OUT.normalDepth.xyz = OUT.normalDepth.xyz*NormalScale;\n\
#endif\n\
\n\
	// Transform vertex tangent and binormal to view space\n\
#ifdef TANGENT_BINORMAL\n\
	OUT.tangent  = mul((float3x3)WorldV, IN.tangent);\n\
	OUT.binormal = mul((float3x3)WorldV, IN.binormal);\n\
\n\
	// Calculate the tangent space vector pointing from the pixel to the eye point for parallax mapping	\n\
	OUT.eyeVec = mul(float3x3(IN.tangent, IN.binormal, IN.normal), EyePos - IN.position.xyz);\n\
#endif\n\
\n\
	// Transform vertex position to view space\n\
	float4 viewSpacePosition = mul(WorldV, IN.position);\n\
#ifdef USE_REFLECTION\n\
	OUT.positionVS = viewSpacePosition.xyz;\n\
#endif\n\
\n\
	// Use the z coordinate of the view space vertex position as linear depth\n\
	// Because we're using a right-handed coordinate system, we need to negate the depth!\n\
	OUT.normalDepth.w = -viewSpacePosition.z;\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";


const static char *pszDeferredGBuffer_Cg_FS = "\n\
// Vertex output\n\
struct VS_OUTPUT {\n\
	float4 position    : POSITION;	// Clip space vertex position\n\
#if defined(USE_AMBIENTOCCLUSIONMAP) || defined(USE_LIGHTMAP)\n\
	float4 texUV	   : TEXCOORD0;	// Vertex texture coordinate, zw for ambient occlusion map and/or light map texture coordinate\n\
#else\n\
	float2 texUV	   : TEXCOORD0;	// Vertex texture coordinate\n\
#endif\n\
	float4 normalDepth : TEXCOORD1; // View space vertex normal (normalize it to avoid interpolation artefacts!) and view space linear depth [0...far plane]\n\
#ifdef USE_NORMALMAP\n\
	float3 tangent     : TEXCOORD2;	// View space vertex tangent (normalize it to avoid interpolation artefacts!)\n\
	float3 binormal    : TEXCOORD3;	// View space vertex tangent (normalize it to avoid interpolation artefacts!)\n\
#endif\n\
	float3 eyeVec      : TEXCOORD4;	// Tangent space vector pointing from the pixel to the eye point\n\
#ifdef USE_REFLECTION\n\
	float3 positionVS  : TEXCOORD5;	// View space vertex position\n\
#endif\n\
};\n\
\n\
// Fragment output\n\
struct FS_OUTPUT {\n\
	float4 color0 : COLOR0;\n\
	float4 color1 : COLOR1;\n\
	float4 color2 : COLOR2;\n\
	float4 color3 : COLOR3;\n\
};\n\
\n\
// Encodes a 3 component normal vector to a 2 component normal vector\n\
float2 encodeNormalVector(float3 normal)\n\
{\n\
	float p = sqrt(normal.z*8 + 8);\n\
	return float2(normal.xy/p + 0.5f);\n\
}\n\
\n\
float fresnel(float3 light, float3 normal, float2 constants)\n\
{\n\
	// Light and normal are assumed to be normalized\n\
	// constants.x = R0 [0..1]\n\
	// constants.y = Power, always >0\n\
	float cosAngle = saturate(1 - dot(light, normal)); // We REALLY need to saturate in here or pow may hurt us when using negative numbers!\n\
	return constants.x + (1 - constants.x) * pow(cosAngle, constants.y);\n\
}\n\
\n\
// Main function\n\
FS_OUTPUT main(VS_OUTPUT IN				// Interpolated output from the vertex stage\n\
	 , uniform float3    DiffuseColor\n\
#ifdef USE_DIFFUSEMAP\n\
	 , uniform sampler2D DiffuseMap\n\
	  #ifdef USE_ALPHATEST\n\
		 , uniform float AlphaReference\n\
	  #endif\n\
#endif\n\
#ifdef USE_SPECULAR\n\
	 , uniform float3    SpecularColor\n\
	 , uniform float     SpecularExponent\n\
	#ifdef USE_SPECULARMAP\n\
	 , uniform sampler2D SpecularMap\n\
	#endif\n\
#endif\n\
#ifdef USE_NORMALMAP\n\
	 , uniform sampler2D NormalMap\n\
	 , uniform float     NormalMapBumpiness\n\
	#ifdef USE_DETAILNORMALMAP\n\
	 , uniform sampler2D DetailNormalMap\n\
	 , uniform float     DetailNormalMapBumpiness\n\
	 , uniform float2    DetailNormalMapUVScale\n\
	#endif\n\
#endif\n\
#ifdef USE_PARALLAXMAPPING\n\
	 , uniform sampler2D HeightMap\n\
	 , uniform float2    ParallaxScaleBias\n\
#endif\n\
#ifdef USE_AMBIENTOCCLUSIONMAP\n\
	 , uniform sampler2D AmbientOcclusionMap\n\
	 , uniform float     AmbientOcclusionFactor\n\
#endif\n\
#ifdef USE_LIGHTMAP\n\
	 , uniform sampler2D LightMap\n\
	 , uniform float3    LightMapColor\n\
#endif\n\
#ifdef USE_EMISSIVEMAP\n\
	 , uniform sampler2D EmissiveMap\n\
	 , uniform float3    EmissiveMapColor\n\
#endif\n\
#ifdef USE_GLOW\n\
	 , uniform float GlowFactor\n\
	#ifdef USE_GLOWMAP\n\
		, uniform sampler2D GlowMap\n\
	#endif\n\
#endif\n\
#ifdef USE_REFLECTION\n\
	 , uniform float3 ReflectionColor\n\
	 , uniform float  Reflectivity\n\
	#ifdef USE_REFLECTIVITYMAP\n\
		, uniform sampler2D ReflectivityMap\n\
	#endif\n\
	#ifdef USE_FRESNELREFLECTION\n\
		, uniform float2 FresnelConstants // x = R0 [0..1] and y = Power, always >0\n\
	#endif\n\
	#ifdef USE_2DREFLECTIONMAP\n\
		, uniform sampler2D ReflectionMap\n\
		, uniform float3x3  ViewSpaceToWorldSpace	// View space to world space transform matrix\n\
	#elif defined(USE_CUBEREFLECTIONMAP)\n\
		, uniform samplerCUBE ReflectionMap\n\
		, uniform float3x3    ViewSpaceToWorldSpace	// View space to world space transform matrix\n\
	#endif\n\
#endif\n\
	 )\n\
{\n\
	FS_OUTPUT OUT;\n\
\n\
	// Get the texel coordinate (textureCoordinate) to use\n\
#ifdef USE_PARALLAXMAPPING\n\
	// Plain parallax mapping works by offsetting the texture coordinate by approximating\n\
	// where the ray would hit the surface. The heightmap indicates how far to offset.\n\
	// The approximation assumes that all heights in the height-map is equal, which of\n\
	// course won't be the case, but if the bumpmap is fairly smooth it works well enough.\n\
	float3 eyeVec = normalize(IN.eyeVec);\n\
	float  scale  = ParallaxScaleBias.x;\n\
	float  bias   = ParallaxScaleBias.y;\n\
	float  height = tex2D(HeightMap, IN.texUV.xy).r;\n\
\n\
	// First offset pass with offset limiting (no division through eyeVec.z)\n\
	float offset = height*scale + bias;\n\
	float2 textureCoordinate = IN.texUV.xy + offset*eyeVec.xy;\n\
\n\
	// For better quality: Refine the parallax by making another lookup at where we ended\n\
	// up in the first parallax computation, then averaging the results.\n\
	float height2 = (height + tex2D(HeightMap, textureCoordinate))*0.5f;\n\
	offset = height2*scale + bias;\n\
	textureCoordinate = IN.texUV.xy + offset*eyeVec.xy;\n\
#else\n\
	#define textureCoordinate IN.texUV.xy\n\
#endif\n\
\n\
	// RT0: Albedo RGB + alpha test value and/or ambient occlusion\n\
#ifdef USE_DIFFUSEMAP\n\
	OUT.color0 = tex2D(DiffuseMap, textureCoordinate);\n\
	#ifdef USE_ALPHATEST\n\
		// Perform an alpha test to discard fragments\n\
		if (OUT.color0.a < AlphaReference)\n\
			discard; // Throw the fragment away and don't draw it!\n\
	#endif\n\
	// Perform sRGB to linear space conversion (gamma correction)\n\
	#ifdef USE_GAMMACORRECTION\n\
		OUT.color0.rgb = pow(OUT.color0.rgb, 2.2f);\n\
	#endif\n\
	// Apply diffuse color\n\
	OUT.color0.rgb *= DiffuseColor;\n\
\n\
	// Use ambient occlusion map\n\
	#ifdef USE_AMBIENTOCCLUSIONMAP\n\
		OUT.color0.a = tex2D(AmbientOcclusionMap, IN.texUV.zw).r*AmbientOcclusionFactor;\n\
	#endif\n\
#else\n\
	OUT.color0.rgb = DiffuseColor;\n\
\n\
	// Use ambient occlusion map\n\
	#ifdef USE_AMBIENTOCCLUSIONMAP\n\
		OUT.color0.a = tex2D(AmbientOcclusionMap, IN.texUV.zw).r*AmbientOcclusionFactor;\n\
	#else\n\
		OUT.color0.a = 1;\n\
	#endif\n\
#endif\n\
\n\
	// RT1: RG encoded normal vector\n\
#ifdef USE_NORMALMAP\n\
	// Fetch normal texel data\n\
	#if defined(NORMALMAP_DXT5_XGXR) || defined(NORMALMAP_LATC2)\n\
		// Fetch the xy-components of the normal and reconstruct the z-component\n\
		float3 normal;\n\
		#ifdef NORMALMAP_DXT5_XGXR\n\
			normal.xy = tex2D(NormalMap, textureCoordinate).ag*2 - 1;\n\
		#else\n\
			normal.xy = tex2D(NormalMap, textureCoordinate).ra*2 - 1;\n\
		#endif\n\
		normal.z  = sqrt(clamp(1 - normal.x*normal.x - normal.y*normal.y, 0.0f, 1.0f));\n\
	#else\n\
		float3 normal = tex2D(NormalMap, textureCoordinate).xyz*2 - 1;\n\
	#endif\n\
	normal.xy *= NormalMapBumpiness;\n\
\n\
	// Fetch and apply detail normal texel data\n\
	#ifdef USE_DETAILNORMALMAP\n\
		#if defined(DETAILNORMALMAP_DXT5_XGXR) || defined(DETAILNORMALMAP_LATC2)\n\
			// Fetch the xy-components of the normal and reconstruct the z-component\n\
			float3 detailNormal;\n\
			#ifdef DETAILNORMALMAP_DXT5_XGXR\n\
				detailNormal.xy = tex2D(DetailNormalMap, textureCoordinate*DetailNormalMapUVScale).ag*2 - 1;\n\
			#else\n\
				detailNormal.xy = tex2D(DetailNormalMap, textureCoordinate*DetailNormalMapUVScale).ra*2 - 1;\n\
			#endif\n\
			detailNormal.z  = sqrt(clamp(1 - detailNormal.x*detailNormal.x - detailNormal.y*detailNormal.y, 0.0f, 1.0f));\n\
		#else\n\
			float3 detailNormal = tex2D(DetailNormalMap, textureCoordinate*DetailNormalMapUVScale).xyz*2 - 1;\n\
		#endif\n\
\n\
		// Just add the detail normal to the standard normal\n\
		normal = normal + detailNormal*DetailNormalMapBumpiness;\n\
	#endif\n\
\n\
	// Transform normal to view space\n\
	normal = normalize(normal.x*IN.tangent + normal.y*IN.binormal + normal.z*IN.normalDepth.rgb);\n\
#else\n\
	float3 normal = normalize(IN.normalDepth.rgb);\n\
#endif\n\
	if (isnan(normal.x) || isnan(normal.y) || isnan(normal.z))\n\
		normal = float3(0, 0, 1); // I had situations with invalid normal vectors...\n\
	// RG encoded normal vector\n\
	OUT.color1.rg = encodeNormalVector(normal);\n\
\n\
	// RT1: Write the linear view space depth into the blue channel of RT1\n\
	OUT.color1.b = IN.normalDepth.w;\n\
#ifdef USE_PARALLAXMAPPING\n\
	// Manipulate the depth of the 'Virtual Position' so shadow mapping and projected textures are influenced by parallax mapping as well\n\
	// [TODO] This already looks quite nice for projected textures, but currently doesn't work correctly with shadow mapping because during\n\
	// the creation of the shadow map, this 'Virtual Position' must be taken into account, too. Check it later again when refactoring the shadow\n\
	// mapping system!\n\
//	OUT.color1.b -= normal.z*(height*ParallaxScaleBias.x + ParallaxScaleBias.y);\n\
#endif\n\
	OUT.color1.a = 1; // Currently unused\n\
\n\
	// RT2: Specular color RGB + specular exponent\n\
#ifdef USE_SPECULAR\n\
	#ifdef USE_SPECULARMAP\n\
		OUT.color2      = tex2D(SpecularMap, textureCoordinate);\n\
		OUT.color2.rgb *= SpecularColor;\n\
		OUT.color2.a   *= SpecularExponent;\n\
	#else\n\
		OUT.color2.rgb = SpecularColor;\n\
		OUT.color2.a   = SpecularExponent;\n\
	#endif\n\
#else\n\
	OUT.color2 = 0;\n\
#endif\n\
\n\
	// RT3: Light accumulation RGB\n\
	OUT.color3 = 0;\n\
	// Light map color RGB\n\
	#ifdef USE_LIGHTMAP\n\
		// Get light map texel data\n\
		float3 lightMapTexel = tex2D(LightMap, IN.texUV.zw).rgb;\n\
		// Perform sRGB to linear space conversion (gamma correction)\n\
		#ifdef USE_GAMMACORRECTION\n\
			lightMapTexel = pow(lightMapTexel, 2.2f);\n\
		#endif\n\
		// Add color\n\
		OUT.color3.rgb += lightMapTexel*LightMapColor;\n\
	#endif\n\
	// Emissive map color RGB\n\
	#ifdef USE_EMISSIVEMAP\n\
		// Get emissive map texel data\n\
		float3 emissiveMapTexel = tex2D(EmissiveMap, textureCoordinate).rgb;\n\
		// Perform sRGB to linear space conversion (gamma correction)\n\
		#ifdef USE_GAMMACORRECTION\n\
			emissiveMapTexel = pow(emissiveMapTexel, 2.2f);\n\
		#endif\n\
		// Add color\n\
		OUT.color3.rgb += emissiveMapTexel*EmissiveMapColor;\n\
	#endif\n\
	// Glow map color a\n\
	#ifdef USE_GLOW\n\
		#ifdef USE_GLOWMAP\n\
			OUT.color3.a = tex2D(GlowMap, textureCoordinate).r*GlowFactor;\n\
		#else\n\
			OUT.color3.a = GlowFactor;\n\
		#endif\n\
	#endif\n\
\n\
	// Reflection\n\
	#ifdef USE_REFLECTION\n\
		// Reflectivity = 0.0...1.0=no reflection...full reflection\n\
		float reflectivity = Reflectivity;\n\
		// Fresnel reflection\n\
		#ifdef USE_FRESNELREFLECTION\n\
			reflectivity *= fresnel(normalize(-IN.positionVS), normal, FresnelConstants);\n\
		#endif\n\
		// Reflectivity map\n\
		#ifdef USE_REFLECTIVITYMAP\n\
			reflectivity *= tex2D(ReflectivityMap, textureCoordinate).r;\n\
		#endif\n\
\n\
		// Reflection color\n\
		float3 reflectionColor = 1;\n\
		#ifdef USE_2DREFLECTIONMAP\n\
			// Spherical environment mapping\n\
			float3 r = mul(ViewSpaceToWorldSpace, normalize(reflect(IN.positionVS, normal)));\n\
			float  m = 2*sqrt(r.x*r.x + r.y*r.y + (r.z + 1)*(r.z + 1));\n\
			#define FLT_MIN 1.175494351e-38F // Minimum positive value\n\
			if (m < FLT_MIN)\n\
				m = FLT_MIN;\n\
			#undef FLT_MIN\n\
			reflectionColor = tex2D(ReflectionMap, float2(r.x/m + 0.5f, 1 - (r.y/m + 0.5f))).rgb;\n\
		#elif defined(USE_CUBEREFLECTIONMAP)\n\
			// Cubic environment mapping\n\
			// There's no need to normalize the reflection vector when using cube maps\n\
			reflectionColor = texCUBE(ReflectionMap, mul(ViewSpaceToWorldSpace, reflect(IN.positionVS, normal))).rgb;\n\
		#endif\n\
		// Perform sRGB to linear space conversion (gamma correction)\n\
		#ifdef USE_GAMMACORRECTION\n\
			reflectionColor = pow(reflectionColor, 2.2f);\n\
		#endif\n\
		// Apply reflection color\n\
		reflectionColor *= ReflectionColor;\n\
\n\
		// Calculate the final albedo color after reflection was applied\n\
		OUT.color0.rgb = lerp(OUT.color0.rgb, reflectionColor, reflectivity);\n\
	#endif\n\
\n\
	// Done\n\
	return OUT;\n\
}\0";
