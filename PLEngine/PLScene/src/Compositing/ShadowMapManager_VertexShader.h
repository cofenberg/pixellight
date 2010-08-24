/*********************************************************\
 *  Definitions:
 *  - USE_DIFFUSEMAP: Take diffuse map into account (if ambient color is black, we don't need it :)
\*********************************************************/

const static char *pszShadowMapManager_VertexShader = "\n\
// vertex input\n\
struct VS_INPUT {\n\
  float4 position : POSITION;\n\
#if defined(USE_DIFFUSEMAP)\n\
  float2 texCoord : TEXCOORD0;\n\
#endif\n\
};\n\
\n\
// vertex output\n\
struct VS_OUTPUT {\n\
  float4 position : POSITION;\n\
  float3 lightVec : TEXCOORD0;\n\
#if defined(USE_DIFFUSEMAP)\n\
  float2 texCoord : TEXCOORD1;\n\
#endif\n\
};\n\
\n\
\n\
// main function\n\
VS_OUTPUT main(VS_INPUT IN,\n\
       uniform float4x4 WorldVP,    // world view projection matrix\n\
       uniform float4x4 WorldV,     // world view matrix\n\
       uniform float    InvRadius)  // world space inverse light radius\n\
{\n\
  VS_OUTPUT OUT;\n\
\n\
  // transform vertex to clip space\n\
  OUT.position = mul(WorldVP, IN.position);\n\
\n\
  // calculate the world space light vector (the light position is the origin)\n\
  OUT.lightVec = -InvRadius*mul(WorldV, IN.position).xyz;\n\
\n\
#if defined(USE_DIFFUSEMAP)\n\
  // pass through the texture coordinate\n\
  OUT.texCoord = IN.texCoord;\n\
#endif\n\
\n\
  // done\n\
  return OUT;\n\
}\0\
";
