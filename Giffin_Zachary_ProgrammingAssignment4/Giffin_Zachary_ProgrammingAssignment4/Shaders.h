#pragma once
#include "Math.h"

// The active vertex shader. Modifies an incoming vertex. Pre-Rasterization. 
void (*VertexShader)(VERTEX&, MATRIX_4X4&) = 0;
// The active pixel shader. Modifies an outgoing pixel. Post-Rasterization.
void (*PixelShader)(VERTEX&) = 0;
//pixel shader for uvs
void (*PixelShaderUV)(VERTEX&, unsigned int&) = 0;

//VS_Shaders
void VS_WorldShader(VERTEX& vert, MATRIX_4X4& matrix)
{
    VERTEX storeUVs = vert;

    vert.color = DirectionalLight(vert);
    vert = VectorMultMatrix(vert, matrix);

    vert = VectorMultMatrix(vert, viewMatrix);
    vert = VectorMultMatrix(vert, ProjectionMatrix(90.0f, 0.1f, 10.0f));
    vert.xyzw[0] = vert.xyzw[0] / vert.xyzw[3];
    vert.xyzw[1] = vert.xyzw[1] / vert.xyzw[3];
    vert.xyzw[2] = vert.xyzw[2] / vert.xyzw[3];
    vert.uv[0] = storeUVs.uv[0];
    vert.uv[1] = storeUVs.uv[1];
}

//PS_Shaders
void PS_UV(VERTEX& changeColor, unsigned int& index)
{
    changeColor.color = ConvertBGRAtoARGB(StoneHenge_pixels[index]);
}
// Basic vertex shader returns the color red
void PS_White(VERTEX& makeWhite)
{
    makeWhite.color = 0xFFFFFFFF;
}
// Basic vertex shader returns the color red
void PS_Red(VERTEX& makeRed)
{
    makeRed.color = 0xFFFF0000;
}
// Basic vertex shader returns the color green
void PS_Green(VERTEX& makeGreen)
{
    makeGreen.color = 0xFF00FF00;
}
// Basic vertex shader returns the color blue
void PS_Blue(VERTEX& makeBlue)
{
    makeBlue.color = 0xFF0000FF;
}
// Basic vertex shader returns the color magenta
void PS_Magenta(VERTEX& makeMagenta)
{
    makeMagenta.color = 0xFFFF00FF;
}
// Basic vertex shader returns the color yellow
void PS_Yellow(VERTEX& makeYellow)
{
    makeYellow.color = 0xFFFFFF00;
}

void PS_Random(VERTEX& makeRandom)
{
    makeRandom.color = 0xFF02A6F2;
}