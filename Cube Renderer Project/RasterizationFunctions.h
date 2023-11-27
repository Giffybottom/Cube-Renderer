#pragma once
#include "Shaders.h"

unsigned int Convert2Dto1DArray(unsigned int x, unsigned int y, unsigned int width)
{
	unsigned int converstionResult = 0;
	converstionResult = y * width + x;

	return converstionResult;
}

void DrawPixel(unsigned int x, unsigned int y, unsigned int BGRAtoRGBA)
{
	if (x < screen_width || y < screen_height)
	{
		unsigned int currPxlPos = Convert2Dto1DArray(x, y, screen_width);
		if (currPxlPos < screen_width * screen_height)
			screen_array[currPxlPos] = BGRAtoRGBA;
	}
}

void DrawVertex(VERTEX drawMe, unsigned int color)
{
	if (drawMe.xyzw[0] < screen_width || drawMe.xyzw[1] < screen_height)
	{
		unsigned int currPxlPos = Convert2Dto1DArray(drawMe.xyzw[0], drawMe.xyzw[1], screen_width);
		if (currPxlPos < screen_width * screen_height)
			screen_array[currPxlPos] = color;
	}
}

void ClearBuffer()
{
	unsigned int pxlColor = 0;

	for (unsigned int i = 0; i < screen_height; i++)
	{
		for (unsigned int j = 0; j < screen_width; j++)
		{
			pxlColor = 0xFF000000;
			DrawPixel(j, i, pxlColor);
		}
	}
}

unsigned int lerpPixels(unsigned int sourceColor1, unsigned int destinationColor2)
{
	//separate individual color channels for background pixel color
	unsigned int red1 = destinationColor2 & 0x00FF0000;
	unsigned int green1 = destinationColor2 & 0x0000FF00;
	unsigned int blue1 = destinationColor2 & 0x000000FF;
	unsigned int alpha1 = destinationColor2 & 0xFF000000;

	//separate individual color channels for sprite pixel color
	unsigned int red2 = sourceColor1 & 0x00FF0000;
	unsigned int green2 = sourceColor1 & 0x0000FF00;
	unsigned int blue2 = sourceColor1 & 0x000000FF;
	unsigned int alpha2 = sourceColor1 & 0xFF000000;

	//shift channel to least significant bit for sprite
	red1 = red1 >> 16;
	green1 = green1 >> 8;
	alpha1 = alpha1 >> 24;

	//shift channel to least significant bit for background
	red2 = red2 >> 16;
	green2 = green2 >> 8;
	alpha2 = alpha2 >> 24;

	//define ratio from alpha from sprite pixel color
	float ratio = (float)alpha2 / 255;

	//return (b - a) * ratio + a;
	red1 = lerp(red1, red2, ratio);
	green1 = lerp(green1, green2, ratio);
	blue1 = lerp(blue1, blue2, ratio);
	alpha1 = lerp(alpha1, alpha2, ratio);

	//shift bits back to original position
	alpha1 = alpha1 << 24;
	red1 = red1 << 16;
	green1 = green1 << 8;

	//regroup channels back together
	unsigned int result = red1 | green1 | blue1 | alpha1;

	return result;
}

unsigned int ConvertBGRAtoARGB(unsigned int BGRAvalue)
{
	//individual 8 bit colors
	unsigned int red = BGRAvalue & 0x0000FF00;
	unsigned int green = BGRAvalue & 0x00FF0000;
	unsigned int blue = BGRAvalue & 0xFF000000;
	unsigned int alpha = BGRAvalue & 0x000000FF;

	//shift each value to correct position
	red = red << 8;
	green = green >> 8;
	blue = blue >> 24;
	alpha = alpha << 24;

	//or them all back together
	unsigned int ARGBvalue = red | green | blue | alpha;

	return ARGBvalue;
}

void LineDrawFunction(VERTEX start, VERTEX end, unsigned int color1, unsigned int color2)
{
	int CurrX = start.xyzw[0];
	int CurrY = start.xyzw[1];

	int changeX = end.xyzw[0] - start.xyzw[0];
	int changeY = end.xyzw[1] - start.xyzw[1];

	//change when ready to lerp colors
	unsigned int newColor = color1;
	unsigned int copyColor2 = color2;

	//gradient amount to divide by
	int gradient = SetGradientAmount(start, end);

	//is the change in x greater or equal to the change in y
	//determines loop to enter
	if (abs(changeX) >= abs(changeY))
	{
		//x is greater or equal to
		//loop through all x values

		if (start.xyzw[0] > end.xyzw[0])
		{
			VERTEX temp = VERTEX();
			temp.xyzw[0] = start.xyzw[0];
			temp.xyzw[1] = start.xyzw[1];


			start.xyzw[0] = end.xyzw[0];
			start.xyzw[1] = end.xyzw[1];

			end.xyzw[0] = temp.xyzw[0];
			end.xyzw[1] = temp.xyzw[1];
		}
		for (unsigned int CurrX = start.xyzw[0]; CurrX <= end.xyzw[0]; CurrX++)
		{
			//
			float ratio = ((float)(CurrX - start.xyzw[0]) / (float)(abs(changeX)));
			//gradient color
			//a = background/original image
			//b = new image being overlayed onto background/original
			//return (b - a) * ratio + a;
			//                a       b     ratio
			newColor = lerpPixelsRatio(newColor, copyColor2, ratio);

			CurrY = lerp(start.xyzw[1], end.xyzw[1], ratio);
			DrawPixel(CurrX, floor(CurrY + 0.5), newColor);
		}
	}
	else
	{
		if (start.xyzw[1] > end.xyzw[1])
		{
			VERTEX temp2 = VERTEX();
			temp2.xyzw[0] = start.xyzw[0];
			temp2.xyzw[1] = start.xyzw[1];


			start.xyzw[0] = end.xyzw[0];
			start.xyzw[1] = end.xyzw[1];

			end.xyzw[0] = temp2.xyzw[0];
			end.xyzw[1] = temp2.xyzw[1];
		}
		for (unsigned int CurrY = start.xyzw[1]; CurrY < end.xyzw[1]; CurrY++)
		{
			float ratio = ((float)(CurrY - start.xyzw[1]) / (float)(abs(changeY)));
			//gradient color
			//a = background/original image
			//b = new image being overlayed onto background/original
			//return (b - a) * ratio + a;
			//                a       b     ratio

			newColor = lerpPixelsRatio(newColor, color2, ratio);
			CurrX = lerp(start.xyzw[0], end.xyzw[0], ratio);
			DrawPixel(floor(CurrX + 0.5), CurrY, newColor);
		}
	}
}

	VERTEX CartesianToScreen(VERTEX point)
{
	VERTEX XandY;

	XandY.xyzw[0] = (1 + point.xyzw[0]) * (screen_width * 0.5f);
	XandY.xyzw[1] = (1 - point.xyzw[1]) * (screen_height * 0.5f);
	XandY.xyzw[2] = point.xyzw[2];
	XandY.xyzw[3] = point.xyzw[3];

	XandY.uv[0] = point.uv[0];
	XandY.uv[1] = point.uv[1];

	return XandY;
}

	void newDrawPixel(const VERTEX& V1, const MATRIX_4X4& matrx)
	{
		VERTEX copy_V1 = V1;
		MATRIX_4X4 copy_matrix = matrx;

		//words
		if (VertexShader)
		{
			VertexShader(copy_V1, copy_matrix);
		}

		//for pixel shader
		if (PixelShader)
		{
			PixelShader(copy_V1);
		}

		VERTEX screen_XY = CartesianToScreen(copy_V1);

		DrawVertex(screen_XY, copy_V1.color);

	}

void newDrawLine(const VERTEX& start, const VERTEX& end, const MATRIX_4X4& matrx)
{
	VERTEX copy_start = start;
	VERTEX copy_end = end;
	MATRIX_4X4 copy_matrix = matrx;

	//words
	if (VertexShader)
	{
		VertexShader(copy_start, copy_matrix);
		VertexShader(copy_end, copy_matrix);
	}

	//for pixel shader
	if (PixelShader)
	{
		PixelShader(copy_start);
		PixelShader(copy_end);
	}

	VERTEX screen_start = CartesianToScreen(copy_start);
	VERTEX screen_end = CartesianToScreen(copy_end);

	LineDrawFunction(screen_start, screen_end, copy_start.color, copy_end.color);

}

void drawTriangle(const TRIANGLE& T1, const MATRIX_4X4& matrx)
{
	//copy triangle vertecies
	VERTEX copy_VA = T1.abc[0];
	VERTEX copy_VB = T1.abc[1];
	VERTEX copy_VC = T1.abc[2];

	VERTEX screen_start = VERTEX();
	VERTEX screen_end = VERTEX();

	MATRIX_4X4 copy_matrix = matrx;

	float beta = 0.0f;
	float gamma = 0.0f;
	float alpha = 0.0f;

	//use this to check currX and currY for better brute
	VERTEX tempCheckPoint = { 0.0f, 0.0f, 0.0f, 0.0f, 0x0};	
	float tempBeta = 0.0f;
	float tempGamma = 0.0f;
	float tempAlpha = 0.0f;
	float zBufferCheck = 0.0f;
	unsigned int zBufferIndex = 0;
	float U = 0;
	float V = 0;
	unsigned int UVarrayIndex = 0;

	//words
	if (VertexShader)
	{
		VertexShader(copy_VA, copy_matrix);
		VertexShader(copy_VB, copy_matrix);
		VertexShader(copy_VC, copy_matrix);
	}

	tempCheckPoint.color = copy_VA.color;

	VERTEX screen_CA = CartesianToScreen(copy_VA);
	VERTEX screen_CB = CartesianToScreen(copy_VB);
	VERTEX screen_CC = CartesianToScreen(copy_VC);

	//implicit line equations for alpha, beta, and gamma.
	beta = implicitLineEquation(screen_CA, screen_CC, screen_CB);
	gamma = implicitLineEquation(screen_CB, screen_CA, screen_CC);
	alpha = implicitLineEquation(screen_CC, screen_CB, screen_CA);

	//find min x and min y
	screen_start.xyzw[0] = (screen_CA.xyzw[0] < screen_CB.xyzw[0]) ? screen_CA.xyzw[0] : screen_CB.xyzw[0];
	screen_start.xyzw[0] = (screen_start.xyzw[0] < screen_CC.xyzw[0]) ? screen_start.xyzw[0] : screen_CC.xyzw[0];

	screen_start.xyzw[1] = (screen_CA.xyzw[1] < screen_CB.xyzw[1]) ? screen_CA.xyzw[1] : screen_CB.xyzw[1];
	screen_start.xyzw[1] = (screen_start.xyzw[1] < screen_CC.xyzw[1]) ? screen_start.xyzw[1] : screen_CC.xyzw[1];

	//find max x and y
	screen_end.xyzw[0] = (screen_CA.xyzw[0] > screen_CB.xyzw[0]) ? screen_CA.xyzw[0] : screen_CB.xyzw[0];
	screen_end.xyzw[0] = (screen_end.xyzw[0] > screen_CC.xyzw[0]) ? screen_end.xyzw[0] : screen_CC.xyzw[0];

	screen_end.xyzw[1] = (screen_CA.xyzw[1] > screen_CB.xyzw[1]) ? screen_CA.xyzw[1] : screen_CB.xyzw[1];
	screen_end.xyzw[1] = (screen_end.xyzw[1] > screen_CC.xyzw[1]) ? screen_end.xyzw[1] : screen_CC.xyzw[1];

	//iterate through all Y values from least to greatest
	for (float CurrY = screen_start.xyzw[1]; CurrY <= screen_end.xyzw[1]; CurrY++)
	{

		tempCheckPoint.xyzw[1] = CurrY;

		//iterate through all Y values from least to greatest
		for (float CurrX = screen_start.xyzw[0]; CurrX <= screen_end.xyzw[0]; CurrX++)
		{
			tempCheckPoint.xyzw[0] = CurrX;

			//get barycentric coordinates
			tempBeta = implicitLineEquation(screen_CA, screen_CC, tempCheckPoint);
			tempGamma = implicitLineEquation(screen_CB, screen_CA, tempCheckPoint);
			tempAlpha = implicitLineEquation(screen_CC, screen_CB, tempCheckPoint);

			//bya
			tempBeta = tempBeta / beta;
			tempGamma = tempGamma / gamma;
			tempAlpha = tempAlpha / alpha;

			//are the point's beta, gamma, and alpha within the maximums of the triangle
			if (tempBeta >= 0 && tempBeta <= 1 &&
				tempGamma >= 0 && tempGamma <= 1 &&
				tempAlpha >= 0 && tempAlpha <= 1)
			{
				zBufferCheck = (screen_CA.xyzw[2] * tempAlpha) +
					(screen_CB.xyzw[2] * tempBeta) +
					(screen_CC.xyzw[2] * tempGamma);

				//value to check if it is infront of current value
				zBufferIndex = Convert2Dto1DArray(tempCheckPoint.xyzw[0], tempCheckPoint.xyzw[1], screen_width);

				U = screen_CA.uv[0] * tempAlpha + screen_CB.uv[0] * tempBeta + screen_CC.uv[0] * tempGamma;
				V = screen_CA.uv[1] * tempAlpha + screen_CB.uv[1] * tempBeta + screen_CC.uv[1] * tempGamma;

				U = U * StoneHenge_width;
				V = V * StoneHenge_height;

				UVarrayIndex = Convert2Dto1DArray(U, V, StoneHenge_width);

				if (zBufferIndex < screen_width * screen_height)
				{
					if (zBufferCheck < z_buffer[zBufferIndex])
					{
						if (PixelShaderUV)
						{
							PixelShaderUV(tempCheckPoint, UVarrayIndex);							
						}

						z_buffer[zBufferIndex] = zBufferCheck;

						DrawVertex(tempCheckPoint, ModulateColors(copy_VA.color, tempCheckPoint.color));
					}
				}
			}
		}	
	}
}

void printMatrix(MATRIX_4X4 printMTX)
{
	float printMe = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printMe = printMTX.arrays[i][j];
			std::cout << printMe << ", ";
		}
		std::cout << std::endl;
	}
}