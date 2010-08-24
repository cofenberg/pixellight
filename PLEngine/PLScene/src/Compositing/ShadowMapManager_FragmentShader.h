/*********************************************************\
 *  Definitions:
 *  - ALPHATEST: Use alpha test to discard fragments
\*********************************************************/

const static char *pszShadowMapManager_FragmentShader = "\n\
// vertex output\n\
struct VS_OUTPUT {\n\
  float4 position : POSITION;\n\
  float3 lightVec : TEXCOORD0;\n\
#ifdef ALPHATEST\n\
  float2 texCoord : TEXCOORD1;\n\
#endif\n\
};\n\
\n\
// fragment output\n\
struct FS_OUTPUT {\n\
  float4 color : COLOR;\n\
};\n\
\n\
\n\
// main function\n\
FS_OUTPUT main(VS_OUTPUT IN\n\
#ifdef ALPHATEST\n\
     , uniform sampler2D DiffuseMap\n\
	 , uniform float     AlphaReference\n\
#endif\n\
   )\n\
{\n\
  FS_OUTPUT OUT;\n\
\n\
  #ifdef ALPHATEST\n\
	// Fetch the required texel data\n\
	float4 sample = tex2D(DiffuseMap, IN.texCoord);\n\
\n\
	// Perform an alpha test to discard fragments\n\
	if (sample.a < AlphaReference)\n\
		discard; // Throw the fragment away and don't draw it!\n\
  #endif\n\
\n\
  // + '0.005' => Set polygon offset to avoid nasty shadow artefacts\n\
  float4 pack = {1.0f, 256.0f, 65536.0, 16777216.0f};\n\
  OUT.color = pack * (length(IN.lightVec) + 0.005f);\n\
\n\
  return OUT;\n\
}\0\
";
