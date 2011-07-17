/*********************************************************\
 *  File: PixelLight_SRShaderLighting.fx                 *
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


// this is used by 3ds Max to load the correct parser
string ParamID = "0x0"; // load default 3ds Max parser

string description = "PixelLight SRShaderLighting scene renderer shader";


/***********************************************/
/*************** tweakables ********************/
/***********************************************/
bool twoSided
<
  string UIName = "Two Sided";
> = false;

half opacity <
  string UIType = "FloatSpinner";
  string UIName = "Opacity";
  half UIMin = 0;
  half UIMax = 1;
  half UIStep = 0.05;
> = 1;

half3 diffuseColor
<
  string UIName = "Diffuse Color";
> = {1.0f, 1.0f, 1.0f};

bool useDiffuseMap
<
  string UIName = "Use Diffuse Map";
> = false;

bool useDiffuseMapAlpha
<
  string UIName = "Use Alpha Test (Diffuse Map Alpha = Opacity)";
> = false;

half alphaReference <
  string UIType = "FloatSpinner";
  string UIName = "Alpha Reference";
  half UIMin = 0;
  half UIMax = 255;
  half UIStep = 1.0;
> = 127;

// alpha channel = opacity
texture diffuseMap : DiffuseMap
<
  string UIName = "Diffuse Map";
  string TextureType = "2D";
  string name = "";
  // we only define this for the diffuse map, most of the other maps are using the same texture channel!
  int Texcoord = 0;
  int MapChannel = 1;
>;

bool useNormalMap
<
  string UIName = "Use Normal Map";
> = false;

bool compressedNormalMap
<
  string UIName = "Swizzled xGxR DXT5 Normal Map";
> = false;

texture normalMap : NormalMap
<
  string UIName = "Normal Map";
  string TextureType = "2D";
  string name = "";
>;

half specularExponent <
  string UIType = "FloatSpinner";
  string UIName = "Specular Exponent";
  half UIMin = 0;
  half UIMax = 128;
  half UIStep = 0.25;
> = 128;

half3 specularColor
<
  string UIName = "Specular Color";
> = {1.0f, 1.0f, 1.0f};

bool useSpecularMap
<
  string UIName = "Use Specular Map";
> = false;

bool useSpecularMapGloss
<
  string UIName = "Use Gloss Map (Specular Map Alpha = Gloss)";
> = false;

// alpha = gloss
texture specularMap : SpecularMap
<
  string UIName = "Specular Map";
  string TextureType = "2D";
  string name = "";
>;

bool useReflection2DMap
<
  string UIName = "Use Reflection 2D Map";
> = false;

texture reflection2DMap
<
  string UIName = "Reflection 2D Map";
  string TextureType = "2D";
  string name = "";
>;

bool useReflectionCubeMap
<
  string UIName = "Use Reflection Cube Map";
> = false;

texture reflectionCubeMap
<
  string UIName = "Reflection Cube Map";
  string TextureType = "CUBE";
  string name = "";
>;

half3 reflectionColor
<
  string UIName = "Reflection Color";
> = {1.0f, 1.0f, 1.0f};

bool useReflectivityMap
<
  string UIName = "Use Reflectivity Map";
> = false;

texture reflectivityMap : ReflectivityMap
<
  string UIName = "Reflectivity Map";
  string TextureType = "2D";
  string name = "";
>;

// currently 'index of refraction' is not supported by this fx-shader
half indexOfRefraction <
  string UIType = "FloatSpinner";
  string UIName = "Index of refraction (dummy)";
  half UIStep = 0.1;
> = 0.0;

bool useEmissiveMap
<
  string UIName = "Use Emissive Map";
> = false;

texture emissiveMap : EmissiveMap
<
  string UIName = "Emissive Map";
  string TextureType = "2D";
  string name = "";
>;

half3 emissiveMapColor
<
  string UIName = "Emissive Map Color";
> = {1.0f, 1.0f, 1.0f};

bool useLightMap
<
  string UIName = "Use Light Map";
> = false;

texture lightMap : LightMap
<
  string UIName = "Light Map";
  string TextureType = "2D";
  string name = "";
  // light maps normally have special texture coordinates
  int Texcoord = 1;
  int MapChannel = 2;
>;

half3 lightMapColor
<
  string UIName = "Light Map Color";
> = {1.0f, 1.0f, 1.0f};

bool useParallaxMapping
<
  string UIName = "Use Parallax Mapping";
> = false;

half parallax <
  string UIType = "FloatSpinner";
  string UIName = "Parallax";
  half UIMin = -1;
  half UIMax = 1;
  half UIStep = 0.001;
> = 0.03;

texture heightMap : HeightMap
<
  string UIName = "Height Map";
  string TextureType = "2D";
  string name = "";
>;

bool useDiffuseRampMap
<
  string UIName = "Use Diffuse Ramp Map";
> = false;

texture diffuseRampMap
<
  string UIName = "Diffuse Ramp Map";
  string TextureType = "1D";
  string name = "";
>;

bool useSpecularRampMap
<
  string UIName = "Use Specular Ramp Map";
> = false;

texture specularRampMap
<
  string UIName = "Specular Ramp Map";
  string TextureType = "1D";
  string name = "";
>;

bool useEdgeRampMap
<
  string UIName = "Use Edge Ramp Map";
> = false;

texture edgeRampMap
<
  string UIName = "Edge Ramp Map";
  string TextureType = "1D";
  string name = "";
>;


/***********************************************/
/*************** light info ********************/
/***********************************************/
half3 ambient : Ambient
<
  string UIName = "Ambient Color";
> = {0.2f, 0.2f, 0.2f};

half4 light1Pos : POSITION
<
  string UIName = "Light 1 Position";
  string Object = "PointLight";
  int RefID = 0;
> = {100.0f, 100.0f, 100.0f, 0.0f};

half light1Range <
  string UIType = "FloatSpinner";
  string UIName = "Light 1 Range";
  half UIMin = 0.0001;
  half UIMax = 10000;
> = 1;

half4 light1Color : LIGHTCOLOR
<
  int LightRef = 0;
> = half4(1.0f, 1.0f, 1.0f, 1.0f);

half4 light2Pos : POSITION
<
  string UIName = "Light 2 Position";
  string Object = "PointLight";
  int RefID = 1;
> = {100.0f, 100.0f, 100.0f, 0.0f};

half light2Range <
  string UIType = "FloatSpinner";
  string UIName = "Light 2 Range";
  half UIMin = 0.0001;
  half UIMax = 10000;
> = 1;

half4 light2Color : LIGHTCOLOR
<
  int LightRef = 1;
> = half4(1.0f, 1.0f, 1.0f, 1.0f);

half4 light3Pos : POSITION
<
  string UIName = "Light 3 Position";
  string Object = "PointLight";
  int RefID = 2;
> = {100.0f, 100.0f, 100.0f, 0.0f};

half light3Range <
  string UIType = "FloatSpinner";
  string UIName = "Light 3 Range";
  half UIMin = 0.0001;
  half UIMax = 10000;
> = 1;

half4 light3Color : LIGHTCOLOR
<
  int LightRef = 2;
> = half4(1.0f, 1.0f, 1.0f, 1.0f);


/****************************************************/
/********** samplers ********************************/
/****************************************************/
sampler2D diffuseMapSampler = sampler_state
{
  Texture = <diffuseMap>;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Anisotropic;
};

sampler2D normalMapSampler = sampler_state
{
  Texture = <normalMap>;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Anisotropic;
};

sampler2D specularMapSampler = sampler_state
{
  Texture = <specularMap>;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Anisotropic;
};

sampler2D reflection2DMapSampler = sampler_state
{
  Texture = <reflection2DMap>;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Anisotropic;
};

samplerCUBE reflectionCubeMapSampler = sampler_state
{
  Texture = <reflectionCubeMap>;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Anisotropic;
};

sampler2D reflectivityMapSampler = sampler_state
{
  Texture = <reflectivityMap>;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Anisotropic;
};

sampler2D emissiveMapSampler = sampler_state
{
  Texture = <emissiveMap>;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Anisotropic;
};

sampler2D lightMapSampler = sampler_state
{
  Texture = <lightMap>;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Anisotropic;
};

sampler2D heightMapSampler = sampler_state
{
  Texture = <heightMap>;
  MinFilter = Linear;
  MagFilter = Linear;
  MipFilter = Anisotropic;
};

sampler1D diffuseRampMapSampler = sampler_state
{
  Texture = <diffuseRampMap>;
  MinFilter = None;
  MagFilter = None;
  MipFilter = Anisotropic;
};

sampler1D specularRampMapSampler = sampler_state
{
  Texture = <specularRampMap>;
  MinFilter = None;
  MagFilter = None;
  MipFilter = Anisotropic;
};

sampler1D edgeRampMapSampler = sampler_state
{
  Texture = <edgeRampMap>;
  MinFilter = None;
  MagFilter = None;
  MipFilter = Anisotropic;
};


/***********************************************/
/*** automatically-tracked "tweakables" ********/
/***********************************************/
half4x4 worldVP   : WorldViewProjection < string UIWidget = "None"; >;
half4x4 world     : World < string UIWidget = "None"; >;
half4x4 worldI    : WorldInverse < string UIWidget = "None"; >;
half4x4 worldIT   : WorldInverseTranspose < string UIWidget = "None"; >;
half3   cameraPos : WorldCameraPosition;


/****************************************************/
/*************** structures *************************/
/****************************************************/
// vertex input
struct VS_INPUT_AMBIENT {
  half4 position  : POSITION;
  half2 texCoord0 : TEXCOORD0;
  half2 texCoord1 : TEXCOORD1;
  half3 normal    : NORMAL;
  half3 tangent   : TANGENT;
  half3 binormal  : BINORMAL;
};

struct VS_INPUT_REFLECTION {
  half4 position  : POSITION;
  half2 texCoord0 : TEXCOORD0;
  half3 normal    : NORMAL;
  half3 tangent   : TANGENT;
  half3 binormal  : BINORMAL;
};

struct VS_INPUT_LIGHTING {
  half4 position  : POSITION;
  half2 texCoord0 : TEXCOORD0;
  half3 normal    : NORMAL;
  half3 tangent   : TANGENT;
  half3 binormal  : BINORMAL;
};

// vertex output
struct VS_OUTPUT_AMBIENT {
  half4 position : POSITION;
  half4 texCoord : TEXCOORD0; // xy = diffuse, zw = light map
  half3 viewVec  : TEXCOORD1;
};

struct VS_OUTPUT_REFLECTION {
  half4 position      : POSITION;
  half2 texCoord      : TEXCOORD0;
  half3 worldPosition : TEXCOORD1;
  half3 worldNormal   : TEXCOORD2;
  half3 worldTangent  : TEXCOORD3;
  half3 worldBinormal : TEXCOORD4;
  half3 viewVec       : TEXCOORD5;
  half3 viewVecWorld  : TEXCOORD6;
};

struct VS_OUTPUT_LIGHTING {
  half4 position : POSITION;
  half2 texCoord : TEXCOORD0;
  half3 lightVec : TEXCOORD1;
  half3 viewVec  : TEXCOORD2;
};


/**************************************/
/***** vertex program *****************/
/**************************************/
VS_OUTPUT_AMBIENT VertexAmbient(VS_INPUT_AMBIENT IN,
                        uniform half4x4          WorldVP,    // object to clip space
                        uniform half4x4          WorldI,     // world to object space
                        uniform half3            CameraPos,  // world space camera position
                        uniform bool             TwoSided)   // two sided?
{
  VS_OUTPUT_AMBIENT OUT;

  // transform vertex to clip space
  OUT.position = mul(IN.position, WorldVP);

  // pass through the texture coordinates
  OUT.texCoord.xy = IN.texCoord0.xy;
  OUT.texCoord.zw = IN.texCoord1.xy;

  // compute the view vector in world space and put it in object space
  half4 objSpaceViewPos = mul(CameraPos, WorldI);
  half3 objViewVec      = objSpaceViewPos.xyz - IN.position.xyz;

  // compute the 3x3 tranform from tangent space to object space
  half3x3 objTangentXf;
  objTangentXf[0] =  IN.binormal;
  objTangentXf[1] = -IN.tangent;
  objTangentXf[2] =  (TwoSided && dot(IN.normal, objViewVec) < 0.0) ? -IN.normal : IN.normal; // flip the normal if required

  // xform view vector from obj space to tangent space
  OUT.viewVec = mul(objTangentXf, objViewVec);

  // done
  return OUT;
}

VS_OUTPUT_REFLECTION VertexReflection(VS_INPUT_REFLECTION IN,
                              uniform half4x4             WorldVP,    // object to clip space
                              uniform half4x4             World,      // object space to world
                              uniform half4x4             WorldI,     // world to object space
                              uniform half3               CameraPos,  // world space camera position
                              uniform bool                TwoSided)   // two sided?
{
  VS_OUTPUT_REFLECTION OUT;

  // transform vertex to clip space
  OUT.position = mul(IN.position, WorldVP);

  // pass through the texture coordinate
  OUT.texCoord = IN.texCoord0;

  // for reflection
  OUT.worldPosition = mul(IN.position, World).xyz;   // compute world space position
  OUT.worldNormal   = mul(IN.normal,   worldIT).xyz; // compute world space normal
  OUT.worldTangent  = mul(IN.tangent,  worldIT).xyz; // compute world space tangent
  OUT.worldBinormal = mul(IN.binormal, worldIT).xyz; // compute world space binormal

  // compute the view vector in world space and put it in object space
  half4 objSpaceViewPos = mul(CameraPos, WorldI);
  half3 objViewVec      = objSpaceViewPos.xyz - IN.position.xyz;

  // compute the 3x3 tranform from tangent space to object space
  half3x3 objTangentXf;
  objTangentXf[0] =  IN.binormal;
  objTangentXf[1] = -IN.tangent;
  objTangentXf[2] =  (TwoSided && dot(IN.normal, objViewVec) < 0.0) ? -IN.normal : IN.normal; // flip the normal if required

  // xform view vector from obj space to tangent space
  OUT.viewVec      = mul(objTangentXf, objViewVec);
  OUT.viewVecWorld = -(CameraPos - OUT.worldPosition);

  // done
  return OUT;
}

VS_OUTPUT_LIGHTING VertexLighting(VS_INPUT_LIGHTING IN,
                          uniform half4             LightPos,   // world space light position
                          uniform half4             LightRange, // world space light range
                          uniform half4x4           WorldVP,    // object to clip space
                          uniform half4x4           WorldI,     // world to object space
                          uniform half3             CameraPos,  // world space camera position
                          uniform bool              TwoSided)   // two sided?
{
  VS_OUTPUT_LIGHTING OUT;

  // transform vertex to clip space
  OUT.position = mul(IN.position, WorldVP);

  // pass through the texture coordinate
  OUT.texCoord = IN.texCoord0;

  // compute the view vector in world space and put it in object space
  half4 objSpaceViewPos = mul(CameraPos, WorldI);
  half3 objViewVec      = objSpaceViewPos.xyz - IN.position.xyz;

  // compute the 3x3 tranform from tangent space to object space
  half3x3 objTangentXf;
  objTangentXf[0] =  IN.binormal;
  objTangentXf[1] = -IN.tangent;
  objTangentXf[2] =  (TwoSided && dot(IN.normal, objViewVec) < 0.0) ? -IN.normal : IN.normal; // flip the normal if required

  // put the world space light position in object space
  half4 objSpaceLightPos = mul(LightPos, WorldI);
  half3 objLightVec      = normalize(objSpaceLightPos.xyz - IN.position.xyz)*(1.0/LightRange);

  // xform light vector from obj space to tangent space
  OUT.lightVec = mul(objTangentXf, objLightVec).xyz;

  // xform view vector from obj space to tangent space
  OUT.viewVec = mul(objTangentXf, objViewVec);

  // done
  return OUT;
}


/**************************************/
/***** fragment program ***************/
/**************************************/
half2 PerformParallaxMapping(half2     TexCoord,
                             half3     ViewVec,
                             bool      UseParallaxMapping,
                             half      Parallax,
                             sampler2D HeightMap)
{
  // I have to do this take make it look right - don't know why
  half2 newV = ViewVec.xy;
  newV.y = -newV.y;

  // parallax mapping
  half height = tex2D(HeightMap, TexCoord).r;
  half offset = Parallax*(2.0*height - 1.0);
  half2 newTexCoord = TexCoord + offset*newV*UseParallaxMapping;

  // refine the parallax
  height += tex2D(HeightMap, newTexCoord).r;
  offset = Parallax*(height - 1.0);
  return TexCoord + offset*newV*UseParallaxMapping;
}

half4 FragmentAmbient(VS_OUTPUT_AMBIENT IN,
              uniform half3             DiffuseColor,
              uniform bool              UseDiffuseMap,
              uniform bool              UseDiffuseMapAlpha,
              uniform sampler2D         DiffuseMap,
              uniform bool              UseEmissiveMap,
              uniform sampler2D         EmissiveMap,
              uniform half3             EmissiveMapColor,
              uniform bool              UseLightMap,
              uniform sampler2D         LightMap,
              uniform half3             LightMapColor,
              uniform bool              UseParallaxMapping,
              uniform half              Parallax,
              uniform sampler2D         HeightMap,
              uniform half3             Ambient,
              uniform half              Opacity) : COLOR
{
  // perform parallax mapping
  half2 newTexCoord = PerformParallaxMapping(IN.texCoord, normalize(IN.viewVec), UseParallaxMapping, Parallax, HeightMap);

  // get diffuse map color
  half4 base = UseDiffuseMap ? tex2D(DiffuseMap, newTexCoord) : half4(1.0, 1.0, 1.0, tex2D(DiffuseMap, newTexCoord).a);
  base.rgb *= DiffuseColor.rgb;
  base.a    = UseDiffuseMapAlpha ? base.a : 1.0;

  // set resulting color
  half4 color;
  color.rgb = (UseEmissiveMap ? tex2D(EmissiveMap, newTexCoord).rgb : 0.0)*EmissiveMapColor + Ambient*base.rgb*(UseLightMap ? tex2D(LightMap, IN.texCoord.zw).rgb : 1.0)*(UseLightMap ? LightMapColor : 1.0);
  color.a   = base.a*opacity;

  // return the final color
  return color;
}

half4 FragmentReflection(VS_OUTPUT_REFLECTION IN,
                 uniform bool                 UseDiffuseMap,
                 uniform bool                 UseDiffuseMapAlpha,
                 uniform sampler2D            DiffuseMap,
                 uniform bool                 UseNormalMap,
                 uniform bool                 CompressedNormalMap,
                 uniform sampler2D            NormalMap,
                 uniform bool                 UseReflection2DMap,
                 uniform sampler2D            Reflection2DMap,
                 uniform bool                 UseReflectionCubeMap,
                 uniform samplerCUBE          ReflectionCubeMap,
                 uniform half3                ReflectionColor,
                 uniform bool                 UseReflectivityMap,
                 uniform sampler2D            ReflectivityMap,
                 uniform bool                 UseParallaxMapping,
                 uniform half                 Parallax,
                 uniform sampler2D            HeightMap,
                 uniform half3                CameraPos) : COLOR
{
  // perform parallax mapping
  half2 newTexCoord = PerformParallaxMapping(IN.texCoord.xy, normalize(IN.viewVec), UseParallaxMapping, Parallax, HeightMap);

  // get diffuse map color
  half4 base = UseDiffuseMap ? tex2D(DiffuseMap, newTexCoord) : half4(1.0, 1.0, 1.0, tex2D(DiffuseMap, newTexCoord).a);
  base.a = UseDiffuseMapAlpha ? base.a : 1.0;

  // set resulting color
  half4 color;
  color.rgb = half3(0.0, 0.0, 0.0);
  color.a   = base.a;

// get normalized normal
  // get color value from normal map
  half3 normal = CompressedNormalMap ? tex2D(NormalMap, newTexCoord).agr : tex2D(NormalMap, newTexCoord).rgb;
  // unpack into -1...1 range
  normal.xy = normal.xy*2.0 - 1.0;
  // calculate the z-component (for none compressed normal maps a simple 'normalize'-call would also do the job)
  normal.z = sqrt(1.0 - dot(normal.xy, normal.xy));
  // reject the per fragment normal map? (we can't use dynamic branching in ps 2.0!)
  normal = UseNormalMap ? normal : half3(0.0, 0.0, 1.0);

  // perform the tangent to world space transformation (no pre-normalization of the normals to safe instructions)
  normal = half3((IN.worldNormal*normal.z) + (normal.x*IN.worldTangent + normal.y*-IN.worldBinormal)); // create a per-pixel normal for Y up
//  normal = normalize(normal); // normalized the normal vector... to many instructions for PS 2.0...

// add cube reflection...
  half3 reflection = normalize(reflect(IN.viewVecWorld, normal));
  // fetch the reflected environment color/lighting and add it to the final color
  half3 reflectionColor = UseReflectionCubeMap ? texCUBE(ReflectionCubeMap, reflection).rgb : 0.0;

// add 2D reflection...
  // compute altitude and azimuth angles
  half2 index;
  half3 Xunitvec = half3(1.0, 0.0, 0.0);
  half3 Yunitvec = half3(0.0, 1.0, 0.0);
  index.y = dot(normalize(reflection), Yunitvec);
  reflection.y = 0.0;
  index.x = dot(normalize(reflection), Xunitvec)*0.5;

  // translate index values into proper range
  if (reflection.z >= 0.0)
    index = (index + 1.0)*0.5;
  else {
    index.y = (index.y + 1.0)*0.5;
    index.x = index.x*0.5 + 1.0;
  }

  // if reflection.z >= 0.0, x will go from 0.25 to 0.75
  // if reflection.z <  0.0, x will go from 0.75 to 1.25, and
  // that's OK, because we've set the texture to wrap.

  // fetch the reflected environment color/lighting and add it to the final color
  reflectionColor += UseReflection2DMap ? tex2D(Reflection2DMap, half2(index.x, 1.0-index.y)).rgb : 0.0;

  // get final color
  color.rgb += reflectionColor*ReflectionColor*(UseReflectivityMap ? tex2D(ReflectivityMap, newTexCoord) : 1.0);

  // return the final color
  return color;
}

half4 FragmentLighting(VS_OUTPUT_LIGHTING IN,
               uniform half4              LightColor,
               uniform half3              DiffuseColor,
               uniform bool               UseDiffuseMap,
               uniform bool               UseDiffuseMapAlpha,
               uniform sampler2D          DiffuseMap,
               uniform bool               UseNormalMap,
               uniform bool               CompressedNormalMap,
               uniform sampler2D          NormalMap,
               uniform half               SpecularExponent,
               uniform half3              SpecularColor,
               uniform bool               UseSpecularMap,
               uniform bool               UseSpecularMapGloss,
               uniform sampler2D          SpecularMap,
               uniform bool               UseParallaxMapping,
               uniform half               Parallax,
               uniform sampler2D          HeightMap,
               uniform bool               UseDiffuseRampMap,
               uniform sampler1D          DiffuseRampMap,
               uniform bool               UseSpecularRampMap,
               uniform sampler1D          SpecularRampMap,
               uniform bool               UseEdgeRampMap,
               uniform sampler1D          EdgeRampMap) : COLOR
{
  // get normalized view vector
  half3 viewVec = normalize(IN.viewVec);

  // perform parallax mapping
  half2 newTexCoord = PerformParallaxMapping(IN.texCoord, viewVec, UseParallaxMapping, Parallax, HeightMap);

// get normalized normal
  // get color value from normal map
  half3 normal = CompressedNormalMap ? tex2D(NormalMap, newTexCoord).agr : tex2D(NormalMap, newTexCoord).rgb;
  // unpack into -1...1 range
  normal.xy = normal.xy*2.0 - 1.0;
  // calculate the z-component (for none compressed normal maps a simple 'normalize'-call would also do the job)
  normal.z = sqrt(1.0 - dot(normal.xy, normal.xy));
  // reject the per fragment normal map? (we can't use dynamic branching in ps 2.0!)
  normal = UseNormalMap ? normal : half3(0.0, 0.0, 1.0);

// perform lighting
  // get diffuse map color
  half4 base = UseDiffuseMap ? tex2D(DiffuseMap, newTexCoord) : half4(1.0, 1.0, 1.0, tex2D(DiffuseMap, newTexCoord).a);
  base.rgb *= DiffuseColor.rgb;
  base.a    = UseDiffuseMapAlpha ? base.a : 1.0;

  // get light vector
  half3 lightVec = normalize(IN.lightVec);

  // get diffuse lighting
  half diffuse = saturate(dot(lightVec, normal));

  // use a diffuse ramp map for the diffuse if requested
  diffuse = UseDiffuseRampMap ? tex1D(DiffuseRampMap, diffuse).r : diffuse;

  // get basic lighting term
  half3 lighting = base.rgb*diffuse;

  // get specular color
  half4 specularColor = UseSpecularMap ? tex2D(SpecularMap, newTexCoord) : half4(1.0, 1.0, 1.0, tex2D(SpecularMap, newTexCoord).a);

  // standard Phong lighting - add specular highlight
  half specular = pow(saturate(dot(reflect(-viewVec, normal), lightVec)), SpecularExponent*(UseSpecularMapGloss ? specularColor.a : 1.0));

  // use a specular ramp map for the diffuse if requested
  specular = UseSpecularRampMap ? tex1D(SpecularRampMap, specular).r : specular;

  // update lighting term
  lighting += specular*diffuse*specularColor.rgb*SpecularColor;

  // get attenuation
  half atten = saturate(1.0 - dot(IN.lightVec, IN.lightVec));

  // use a edge ramp map for the diffuse if requested
  float edge = tex1D(EdgeRampMap, max(0, dot(viewVec, normal))).r;
  edge = UseEdgeRampMap ? edge : 1.0;

  // set resulting color
  half4 color;
  color.rgb = LightColor.rgb*lighting*atten*edge;
  color.a   = base.a;

  // return the final color
  return color;
}


/****************************************************/
/********** techniques ******************************/
/****************************************************/
// CullMode: 0=None, 2=CW (we can't use this names directly in here)
technique OneLight
{
  pass AmbientPass
  {
    ZEnable          = true;
    ZWriteEnable     = (opacity == 1);
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = (opacity < 1);
    SrcBlend         = SrcAlpha;
    DestBlend        = InvSrcAlpha;
    VertexShader     = compile vs_1_1 VertexAmbient(worldVP, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentAmbient(diffuseColor, useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useEmissiveMap, emissiveMapSampler, emissiveMapColor, useLightMap, lightMapSampler, lightMapColor, useParallaxMapping, parallax, heightMapSampler, ambient, opacity);
  }
  pass ReflectionPass
  {
    ZEnable          = true;
    ZWriteEnable     = false;
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = true;
    SrcBlend         = One;
    DestBlend        = One;
    VertexShader     = compile vs_1_1 VertexReflection(worldVP, world, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentReflection(useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useNormalMap, compressedNormalMap, normalMapSampler, useReflection2DMap, reflection2DMapSampler, useReflectionCubeMap, reflectionCubeMapSampler, reflectionColor, useReflectivityMap, reflectivityMapSampler, useParallaxMapping, parallax, heightMapSampler, cameraPos);
  }
  pass LightingPass
  {
    ZEnable          = true;
    ZWriteEnable     = false;
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = true;
    SrcBlend         = One;
    DestBlend        = One;
    VertexShader     = compile vs_1_1 VertexLighting(light1Pos, light1Range, worldVP, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentLighting(light1Color, diffuseColor, useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useNormalMap, compressedNormalMap, normalMapSampler, specularExponent, specularColor, useSpecularMap, useSpecularMapGloss, specularMapSampler, useParallaxMapping, parallax, heightMapSampler, useDiffuseRampMap, diffuseRampMapSampler, useSpecularRampMap, specularRampMapSampler, useEdgeRampMap, edgeRampMapSampler);
  }
}

technique TwoLights
{
  pass AmbientPass
  {
    ZEnable          = true;
    ZWriteEnable     = (opacity == 1);
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = (opacity < 1);
    SrcBlend         = SrcAlpha;
    DestBlend        = InvSrcAlpha;
    VertexShader     = compile vs_1_1 VertexAmbient(worldVP, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentAmbient(diffuseColor, useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useEmissiveMap, emissiveMapSampler, emissiveMapColor, useLightMap, lightMapSampler, lightMapColor, useParallaxMapping, parallax, heightMapSampler, ambient, opacity);
  }
  pass ReflectionPass
  {
    ZEnable          = true;
    ZWriteEnable     = false;
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = true;
    SrcBlend         = One;
    DestBlend        = One;
    VertexShader     = compile vs_1_1 VertexReflection(worldVP, world, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentReflection(useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useNormalMap, compressedNormalMap, normalMapSampler, useReflection2DMap, reflection2DMapSampler, useReflectionCubeMap, reflectionCubeMapSampler, reflectionColor, useReflectivityMap, reflectivityMapSampler, useParallaxMapping, parallax, heightMapSampler, cameraPos);
  }
  pass LightingPass
  {
    ZEnable          = true;
    ZWriteEnable     = false;
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = true;
    SrcBlend         = One;
    DestBlend        = One;
    VertexShader     = compile vs_1_1 VertexLighting(light1Pos, light1Range, worldVP, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentLighting(light1Color, diffuseColor, useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useNormalMap, compressedNormalMap, normalMapSampler, specularExponent, specularColor, useSpecularMap, useSpecularMapGloss, specularMapSampler, useParallaxMapping, parallax, heightMapSampler, useDiffuseRampMap, diffuseRampMapSampler, useSpecularRampMap, specularRampMapSampler, useEdgeRampMap, edgeRampMapSampler);
  }
  pass LightingPass
  {
    ZEnable          = true;
    ZWriteEnable     = false;
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = true;
    SrcBlend         = One;
    DestBlend        = One;
    VertexShader     = compile vs_1_1 VertexLighting(light2Pos, light2Range, worldVP, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentLighting(light2Color, diffuseColor, useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useNormalMap, compressedNormalMap, normalMapSampler, specularExponent, specularColor, useSpecularMap, useSpecularMapGloss, specularMapSampler, useParallaxMapping, parallax, heightMapSampler, useDiffuseRampMap, diffuseRampMapSampler, useSpecularRampMap, specularRampMapSampler, useEdgeRampMap, edgeRampMapSampler);
  }
}

technique ThreeLights
{
  pass AmbientPass
  {
    ZEnable          = true;
    ZWriteEnable     = (opacity == 1);
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = (opacity < 1);
    SrcBlend         = SrcAlpha;
    DestBlend        = InvSrcAlpha;
    VertexShader     = compile vs_1_1 VertexAmbient(worldVP, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentAmbient(diffuseColor, useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useEmissiveMap, emissiveMapSampler, emissiveMapColor, useLightMap, lightMapSampler, lightMapColor, useParallaxMapping, parallax, heightMapSampler, ambient, opacity);
  }
  pass ReflectionPass
  {
    ZEnable          = true;
    ZWriteEnable     = false;
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = true;
    SrcBlend         = One;
    DestBlend        = One;
    VertexShader     = compile vs_1_1 VertexReflection(worldVP, world, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentReflection(useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useNormalMap, compressedNormalMap, normalMapSampler, useReflection2DMap, reflection2DMapSampler, useReflectionCubeMap, reflectionCubeMapSampler, reflectionColor, useReflectivityMap, reflectivityMapSampler, useParallaxMapping, parallax, heightMapSampler, cameraPos);
  }
  pass LightingPass
  {
    ZEnable          = true;
    ZWriteEnable     = false;
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = true;
    SrcBlend         = One;
    DestBlend        = One;
    VertexShader     = compile vs_1_1 VertexLighting(light1Pos, light1Range, worldVP, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentLighting(light1Color, diffuseColor, useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useNormalMap, compressedNormalMap, normalMapSampler, specularExponent, specularColor, useSpecularMap, useSpecularMapGloss, specularMapSampler, useParallaxMapping, parallax, heightMapSampler, useDiffuseRampMap, diffuseRampMapSampler, useSpecularRampMap, specularRampMapSampler, useEdgeRampMap, edgeRampMapSampler);
  }
  pass LightingPass
  {
    ZEnable          = true;
    ZWriteEnable     = false;
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = true;
    SrcBlend         = One;
    DestBlend        = One;
    VertexShader     = compile vs_1_1 VertexLighting(light2Pos, light2Range, worldVP, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentLighting(light2Color, diffuseColor, useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useNormalMap, compressedNormalMap, normalMapSampler, specularExponent, specularColor, useSpecularMap, useSpecularMapGloss, specularMapSampler, useParallaxMapping, parallax, heightMapSampler, useDiffuseRampMap, diffuseRampMapSampler, useSpecularRampMap, specularRampMapSampler, useEdgeRampMap, edgeRampMapSampler);
  }
  pass LightingPass
  {
    ZEnable          = true;
    ZWriteEnable     = false;
    ZFunc            = LessEqual;
    CullMode         = (twoSided ? 0 : 2);
    AlphaTestEnable  = (useDiffuseMapAlpha);
    AlphaRef         = (alphaReference);
    AlphaBlendEnable = true;
    SrcBlend         = One;
    DestBlend        = One;
    VertexShader     = compile vs_1_1 VertexLighting(light3Pos, light3Range, worldVP, worldI, cameraPos, twoSided);
    PixelShader      = compile ps_2_0 FragmentLighting(light3Color, diffuseColor, useDiffuseMap, useDiffuseMapAlpha, diffuseMapSampler, useNormalMap, compressedNormalMap, normalMapSampler, specularExponent, specularColor, useSpecularMap, useSpecularMapGloss, specularMapSampler, useParallaxMapping, parallax, heightMapSampler, useDiffuseRampMap, diffuseRampMapSampler, useSpecularRampMap, specularRampMapSampler, useEdgeRampMap, edgeRampMapSampler);
  }
}
