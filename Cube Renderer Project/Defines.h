#pragma once
#include <iostream>
//#include "math.h"
//#include "flower.h"
#include <vector>
#include "StoneHenge.h"
#include "StoneHenge_Texture.h"
	
struct VERTEX {

	//getters and setters are good for accessing fariables you want to change

	float xyzw[4];
	float uv[2];
	float normals[3];
	unsigned int color;

	//Default Constructor: sets to default values
	VERTEX()
	{
		xyzw[0] = 0.0f;
		xyzw[1] = 0.0f;
		xyzw[2] = 0.0f;
		xyzw[3] = 0.0f;

		uv[0] = 0.0f;
		uv[1] = 0.0f;

		normals[0] = 0.0f;
		normals[1] = 0.0f;
		normals[2] = 0.0f;

		color = 0xFFFFFFFF;
	}

	VERTEX(float x, float y, float z, unsigned int newColor)
	{
		xyzw[0] = x;
		xyzw[1] = y;
		xyzw[2] = z;
		xyzw[3] = 1.0f;

		uv[0] = 0.0f;
		uv[1] = 0.0f;

		normals[0] = 0.0f;
		normals[1] = 0.0f;
		normals[2] = 0.0f;

		color = newColor;
	}

	VERTEX(float x, float y, float z, float w, unsigned int newColor)
	{
		xyzw[0] = x;
		xyzw[1] = y;
		xyzw[2] = z;
		xyzw[3] = w;

		uv[0] = 0.0f;
		uv[1] = 0.0f;

		normals[0] = 0.0f;
		normals[1] = 0.0f;
		normals[2] = 0.0f;

		color = newColor;
	}
	//constructor to allow for uv mapping
	VERTEX(float x, float y, float z, float w, float uvX, float uvY, float norm1, float norm2, float norm3)
	{
		xyzw[0] = x;
		xyzw[1] = y;
		xyzw[2] = z;
		xyzw[3] = w;

		uv[0] = uvX;
		uv[1] = uvY;

		normals[0] = norm1;
		normals[1] = norm2;
		normals[2] = norm3;

		color = 0xFFFFFFFF;
	}

	VERTEX(float x, float y, float z, float w, float uvX, float uvY)
	{
		xyzw[0] = x;
		xyzw[1] = y;
		xyzw[2] = z;
		xyzw[3] = w;

		uv[0] = uvX;
		uv[1] = uvY;

		normals[0] = 0.0f;
		normals[1] = 0.0f;
		normals[2] = 0.0f;

		color = 0xFFFFFFFF;
	}

	VERTEX(float x, float y, float z, float w, float uvX, float uvY, unsigned int newColor)
	{
		xyzw[0] = x;
		xyzw[1] = y;
		xyzw[2] = z;
		xyzw[3] = w;

		uv[0] = uvX;
		uv[1] = uvY;

		normals[0] = 0.0f;
		normals[1] = 0.0f;
		normals[2] = 0.0f;

		color = newColor;
	}

	//overloaded assignment operator
	VERTEX& operator=(const VERTEX& copy) {

		for (int i = 0; i < 4; i++)
		{
			xyzw[i] = copy.xyzw[i];
		}

		color = copy.color;
		uv[0] = copy.uv[0];
		uv[1] = copy.uv[1];
		normals[0] = copy.normals[0];
		normals[1] = copy.normals[1];
		normals[2] = copy.normals[2];

		return *this;
	}
};

struct COORDINATE { float x, y; };

struct MATRIX_4X4 {

public: float arrays[4][4];

	  MATRIX_4X4& operator=(const MATRIX_4X4& copy) {

		  for (int i = 0; i < 4; i++)
		  {
			  for (int j = 0; j < 4; j++)
			  {
				  arrays[i][j] = copy.arrays[i][j];
			  }
		  }
		  return *this;
	  }
};

const unsigned int screen_width = 1000;
const unsigned int screen_height = 500;
unsigned int screen_array[screen_width * screen_height] = { 0, };
float z_buffer[screen_width * screen_height] = { FLT_MAX };

MATRIX_4X4 cubeWorldMatrix;
MATRIX_4X4 gridWorldMatrix;
MATRIX_4X4 cameraMatrix;
MATRIX_4X4 viewMatrix;
MATRIX_4X4 starFieldWorldMatrix;
MATRIX_4X4 stoneHengeWorldMatrix;

MATRIX_4X4 projectionMatrix;

void printMatrix(MATRIX_4X4 printMTX);

struct TRIANGLE {
	VERTEX abc[3];
};

struct TEXTURE { const unsigned int* ptr; const unsigned int width; const unsigned int height; };

unsigned int ConvertBGRAtoARGB(unsigned int BGRAvalue);


VERTEX starField[3000];
VERTEX stoneHenge[1457];
TRIANGLE stoneHengeTriangles[844];
VERTEX directionLight = { -0.577f, -0.577f,  0.577f, 1.0f, 0xFFC0C0F0 };
VERTEX pointLight = { -1.0f, 0.5f,  1.0f, 1.0f, 0xFFFFFF00 };
float pointLightRadi = 4.5f;
float ambientValue = 0.2f;