/*********************************************************\
 *  File: SRPDeferredSSAO_Cg.h                           *
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


// Cg vertex shader source code
static const PLCore::String sDeferredSSAO_Cg_VS = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float4 TexCoord	: TEXCOORD0;	// xy = Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)
									// zw = Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)
};

// Main function
VS_OUTPUT main(float4 VertexPosition : POSITION,	// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
													// zw = Vertex texture coordinate, lower/left is (0,0) and upper/right is (1,1)
	   uniform int2	  TextureSize,					// xy = Texture size
	   uniform int2	  InputTextureSize)				// Input texture size
{
	VS_OUTPUT OUT;

	// Pass through the vertex position
	OUT.Position = float4(VertexPosition.xy, 0, 1);

	// Pass through the scaled vertex texture coordinate
	OUT.TexCoord.xy = VertexPosition.zw*TextureSize;
	OUT.TexCoord.zw = VertexPosition.zw*InputTextureSize;

	// Done
	return OUT;
}
);	// STRINGIFY


// Cg vertex shader source code
static const PLCore::String sDeferredSSAO_Cg_FS = STRINGIFY(
// Vertex output
struct VS_OUTPUT {
	float4 Position : POSITION;		// Clip space vertex position, lower/left is (-1,-1) and upper/right is (1,1)
	float4 TexCoord	: TEXCOORD0;	// xy = Vertex texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)
									// zw = Vertex input texture coordinate, lower/left is (0,0) and upper/right is (<TextureWidth>,<TextureHeight>)
};

// Fragment output
struct FS_OUTPUT {
	float4 Color0 : COLOR;
};

float FetchEyeZ(samplerRECT normalDepthTexture, float2 uv)
{
	return texRECT(normalDepthTexture, uv).b;
}

float BlurFunction(samplerRECT inputTexture, samplerRECT normalDepthTexture, float blurFalloff, float sharpness, float2 uv, float2 uvInput, float r, float center_c, float center_d, inout float w_total)
{
	float c = texRECT(inputTexture, uvInput).r;
	float d = FetchEyeZ(normalDepthTexture, uv);

	float ddiff = d - center_d;
	float w = exp(-r*r*blurFalloff - ddiff*ddiff*sharpness);
	w_total += w;

	return w*c;
}

// Main function
FS_OUTPUT main(VS_OUTPUT   IN					// Interpolated output from the vertex stage
	 , uniform float	   BlurRadius			// Blur radius
	 , uniform float	   BlurFalloff			// Blur falloff
	 , uniform float	   Sharpness			// Sharpness
	 , uniform float2	   UVScale				// UV scale
	 , uniform samplerRECT InputTexture			// Input texture
	 , uniform samplerRECT NormalDepthTexture)	// RG=normal vector, B=linear view space length
{
	FS_OUTPUT OUT;

	float b = 0;
	float w_total = 0;
	float center_c = texRECT(InputTexture, IN.TexCoord.zw).r;
	float center_d = FetchEyeZ(NormalDepthTexture, IN.TexCoord.xy);
	for (float r=-BlurRadius; r<=BlurRadius; r++)
		b += BlurFunction(InputTexture, NormalDepthTexture, BlurFalloff, Sharpness, IN.TexCoord.xy + r*UVScale, IN.TexCoord.zw + r*UVScale, r, center_c, center_d, w_total);
	OUT.Color0 = b/w_total;

	// Done
	return OUT;
}
);	// STRINGIFY


//[-------------------------------------------------------]
//[ Undefine helper macro                                 ]
//[-------------------------------------------------------]
#undef STRINGIFY
