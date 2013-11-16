cbuffer cbChangesEveryFrame : register( b0 ){matrix worldMatrix;};
cbuffer cbNeverChanges : register( b1 ){matrix viewMatrix;};
cbuffer cbChangeOnResize : register( b2 ){matrix projMatrix;};

Texture2D colorMap_ : register( t0 );
SamplerState colorSampler_ : register( s0 );


struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
	float2 tex0 : TEXCOORD0;
};


struct VS_Input
{
    float4 pos  : POSITION;
    float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
    float2 tex0 : TEXCOORD0;
};

PS_Input VShader( VS_Input vertex )
{
    PS_Input vsOut = (PS_Input) 0;
	
	vsOut.pos = mul( vertex.pos, worldMatrix );
	vsOut.pos = mul( vsOut.pos, viewMatrix );
	vsOut.pos = mul( vsOut.pos, projMatrix );
	vsOut.tex0 = vertex.tex0;

    return vsOut;
}


VOut VShaderOld(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = position;
    output.color = color;

    return output;
}

float4 PShader( PS_Input frag ) : SV_TARGET
{
    return colorMap_.Sample( colorSampler_, frag.tex0 );
}

float4 PShaderOld(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}