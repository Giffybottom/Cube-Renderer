#pragma once
#include "Defines.h"

int lerp(int a, int b, float ratio)
{
	//a = background/original image
	//b = new image being overlayed onto background/original

	return (b - a) * ratio + a;
}

int SetGradientAmount(VERTEX P1, VERTEX P2)
{
	if (P1.xyzw[0] > P2.xyzw[0] || P1.xyzw[1] > P2.xyzw[1])
	{
		VERTEX temp = VERTEX();
		temp.xyzw[0] = P1.xyzw[0];
		temp.xyzw[0] = P1.xyzw[1];


		P1.xyzw[0] = P2.xyzw[0];
		P1.xyzw[1] = P2.xyzw[1];

		P2.xyzw[0] = temp.xyzw[0];
		P2.xyzw[1] = temp.xyzw[1];
	}

	return abs((std::sqrt(std::pow((int)(P2.xyzw[0] - P1.xyzw[0]), 2) + std::pow((int)(P2.xyzw[1] - P1.xyzw[1]), 2)))) / 4;
}

unsigned int lerpPixelsRatio(unsigned int color1, unsigned int color2, float ratio)
{
	//separate individual color channels for background pixel color
	unsigned int red1 = color1 & 0x00FF0000;
	unsigned int green1 = color1 & 0x0000FF00;
	unsigned int blue1 = color1 & 0x000000FF;

	//separate individual color channels for sprite pixel color
	unsigned int red2 = color2 & 0x00FF0000;
	unsigned int green2 = color2 & 0x0000FF00;
	unsigned int blue2 = color2 & 0x000000FF;

	//shift channel to least significant bit for sprite
	red1 = red1 >> 16;
	green1 = green1 >> 8;

	//shift channel to least significant bit for background
	red2 = red2 >> 16;
	green2 = green2 >> 8;

	//return (b - a) * ratio + a;
	red1 = lerp(red1, red2, ratio);
	green1 = lerp(green1, green2, ratio);
	blue1 = lerp(blue1, blue2, ratio);

	//shift bits back to original position
	red1 = red1 << 16;
	green1 = green1 << 8;

	unsigned int result = red1 | green1 | blue1;

	return result;
}

float DegreesToRadians(int degrees)
{
	float result = ((float)degrees * ((float)(atan(1) * 4) / 180.0f));

	return result;
}

VERTEX VectorMultMatrix(VERTEX v, MATRIX_4X4 m)
{
	VERTEX newVertex = v;

	//xyzw[0] = x value
	newVertex.xyzw[0] = ((m.arrays[0][0] * v.xyzw[0]) +
		(m.arrays[1][0] * v.xyzw[1]) +
		(m.arrays[2][0] * v.xyzw[2]) +
		(m.arrays[3][0] * v.xyzw[3]));
	//xyzw[1] = y value
	newVertex.xyzw[1] = ((m.arrays[0][1] * v.xyzw[0]) +
		(m.arrays[1][1] * v.xyzw[1]) +
		(m.arrays[2][1] * v.xyzw[2]) +
		(m.arrays[3][1] * v.xyzw[3]));
	//xyzw[2] = z value
	newVertex.xyzw[2] = ((m.arrays[0][2] * v.xyzw[0]) +
		(m.arrays[1][2] * v.xyzw[1]) +
		(m.arrays[2][2] * v.xyzw[2]) +
		(m.arrays[3][2] * v.xyzw[3]));
	//xyzw[3] = w value
	newVertex.xyzw[3] = ((m.arrays[0][3] * v.xyzw[0]) +
		(m.arrays[1][3] * v.xyzw[1]) +
		(m.arrays[2][3] * v.xyzw[2]) +
		(m.arrays[3][3] * v.xyzw[3]));
	return newVertex;
}

MATRIX_4X4 IdentityMatrix()
{
	MATRIX_4X4 identityMatrix = { {{1.0f,0.0f,0.0f,0.0f},
								   {0.0f,1.0f,0.0f,0.0f},
								   {0.0f,0.0f,1.0f,0.0f},
								   {0.0f,0.0f,0.0f,1.0f}}
	};

	return identityMatrix;
}

MATRIX_4X4 RotationX(float degrees)
{
	float radians = DegreesToRadians(degrees);

	//positive radians = Counter Clocwise Rotation
	MATRIX_4X4 rotationMatrixX = { {{1.0f,0.0f,0.0f,0.0f},
									{0.0f,cos(radians),-sin(radians),0.0f},
									{0.0f,sin(radians),cos(radians),0.0f},
									{0.0f,0.0f,0.0f,1.0f} }
	};

	return rotationMatrixX;
}

MATRIX_4X4 RotationY(float degrees)
{
	float radians = DegreesToRadians(degrees);

	//positive radians = Counter Clocwise Rotation
	MATRIX_4X4 newMatrix = { {{cos(radians),0.0f,sin(radians),0.0f},
							  {0.0f,1.0f,0.0f,0.0f},
							  {-sin(radians),0.0f,cos(radians),0.0f},
							  {0.0f,0.0f,0.0f,1.0f} }
	};

	return newMatrix;
}

MATRIX_4X4 RotationZ(float degrees)
{
	float radians = DegreesToRadians(degrees);

	//positive radians = Counter Clocwise Rotation
	MATRIX_4X4 newMatrix = { {{cos(radians),sin(radians),0.0f,0.0f},
							  {-sin(radians),cos(radians),0.0f,0.0f},
							  {0.0f,0.0f,1.0f,0.0f},
							  {0.0f,0.0f,0.0f,1.0f} }
	};

	return newMatrix;
}

MATRIX_4X4 MatrixMultMatrix(MATRIX_4X4 a, MATRIX_4X4 b, int columnSize, int rowSize)
{
	MATRIX_4X4 newMatrix = MATRIX_4X4();

	int columns = columnSize;
	int rows = rowSize;

	//iterates to next column
	// i 
	/*{(0),1,2,3}
	  {(0),1,2,3}
	  {(0),1,2,3}
	  {(0),1,2,3}*/
	for (int i = 0; i < rows; i++)
	{
		//iterates to next column
		//      i   i+1 i+2 i+3
		/* j  {(0)} {1} {2} {3}
		  j+1  {0}  {1} {2} {3}
		  j+2  {0}  {1} {2} {3}
		  j+3  {0}  {1} {2} {3} */
		for (int j = 0; j < columns; j++)
		{
			//iterates to next column
			//      i  i+1 i+2 i+3      i  i+1 i+2 i+3           k    k+1   k+2   k+3 
			/*  j  {(0)} {1} {2} {3}   {(0)} {1} {2} {3}  k	   {(0)} {(1)} {(2)} {(3)}  j
			   j+1 {(0)} {1} {2} {3} = {(0)} {1} {2} {3} k+1 *  {0}   {1}   {2}   {3}  j+1
			   j+2 {(0)} {1} {2} {3}   {(0)} {1} {2} {3} k+2    {0}   {1}   {2}   {3}  j+2
			   j+3 {(0)} {1} {2} {3}   {(0)} {1} {2} {3} k+3    {0}   {1}   {2}   {3}  j+3*/
			newMatrix.arrays[i][j] = 0;
			for (int k = 0; k < columns; k++)
			{
				newMatrix.arrays[i][j] += b.arrays[i][k] * a.arrays[k][j];
			}
		}
	}

	return newMatrix;
}

MATRIX_4X4 Inverse(MATRIX_4X4 a)
{
	//set upper left 3x3 copied
	MATRIX_4X4 newMatrix = { {{a.arrays[0][0],a.arrays[1][0],a.arrays[2][0],0.0f},
							  {a.arrays[0][1],a.arrays[1][1],a.arrays[2][1],0.0f},
							  {a.arrays[0][2],a.arrays[1][2],a.arrays[2][2],0.0f},
							  {0.0f,0.0f,0.0f,1.0f} }
	};

	//source position copied
	VERTEX positionVector = { a.arrays[3][0], a.arrays[3][1], a.arrays[3][2], a.arrays[3][3], 0xFF000000 };

	//source position 3x3 multiplied by source position
	positionVector = VectorMultMatrix(positionVector, newMatrix);

	//result of last step negated
	for (int i = 0; i < 3; i++)
	{
		positionVector.xyzw[i] = positionVector.xyzw[i] * -1.0f;
	}

	newMatrix.arrays[3][0] = positionVector.xyzw[0];
	newMatrix.arrays[3][1] = positionVector.xyzw[1];
	newMatrix.arrays[3][2] = positionVector.xyzw[2];
	newMatrix.arrays[3][3] = positionVector.xyzw[3];

	return newMatrix;
}

MATRIX_4X4 Translation(float x, float y, float z)
{
	MATRIX_4X4 newMatrix = { {{1.0f,0.0f,0.0f,0.0f},
							  {0.0f,1.0f,0.0f,0.0f},
							  {0.0f,0.0f,1.0f,0.0f},
							  {x,y,z, 1.0f}}
	};

	return newMatrix;
}

MATRIX_4X4 ProjectionMatrix(float FOV, float nearPlane, float farPlane)
{
	float Y_Scale = cos(DegreesToRadians(FOV / 2)) / sin(DegreesToRadians(FOV / 2));

	float aspectRatio = screen_width / screen_height;
	if (screen_height > screen_width)
	{
		aspectRatio = (float)screen_width / (float)screen_height;
	}
	else
	{
		aspectRatio = (float)screen_height / (float)screen_width;
		
	}

	float X_Scale = Y_Scale * aspectRatio;

	float zNear = nearPlane;
	float zFar = farPlane;

	MATRIX_4X4 newMatrix = { {{X_Scale,0.0f,0.0f,0.0f},
							  {0.0f,Y_Scale,0.0f,0.0f},
							  {0.0f,0.0f,zFar / (zFar - zNear),1.0f},
							  {0.0f,0.0f,-(zFar * zNear) / (zFar - zNear), 0.0f}}
	};

	return newMatrix;
}

//V1 and V2 are the points vertecies of the line.
//V3 is the point to be testing
float implicitLineEquation(VERTEX V1, VERTEX V2, VERTEX V3)
{
	float result = 0;

	//(Y1 – Y2)x + (X2 – X1)y + X1Y2 – Y1X2 = 0
	result = (V1.xyzw[1] - V2.xyzw[1]) * V3.xyzw[0] +
		     (V2.xyzw[0] - V1.xyzw[0]) * V3.xyzw[1] +
		      V1.xyzw[0] * V2.xyzw[1] - 
		      V1.xyzw[1] * V2.xyzw[0];

	return result;
}

float DOT(VERTEX V1, VERTEX V2)
{
	//Can be used to determine the relationship between two vectors of equal length. 
	//A result of 1 or -1 indicates the two vectors are PARALLEL to each other.
	//A result of ZERO indicates the two vectors are perpendicular to one another.

	float product = 0;

	return product = V1.xyzw[0] * V2.xyzw[0] + V1.xyzw[1] * V2.xyzw[1] + V1.xyzw[2] * V2.xyzw[2];

}

VERTEX CROSS(VERTEX V1, VERTEX V2)
{
	//Given two 3D vectors of any length, the cross product can be used to solve a third vector 
	//that will be PERPENDICULAR to both.
	//

	VERTEX product = VERTEX();

	//assign x, y, z values after calculation
	product.xyzw[0] = V1.xyzw[1] * V2.xyzw[2] - V1.xyzw[2] * V2.xyzw[1];
	product.xyzw[1] = V1.xyzw[2] * V2.xyzw[0] - V1.xyzw[0] * V2.xyzw[2];
	product.xyzw[2] = V1.xyzw[0] * V2.xyzw[1] - V1.xyzw[1] * V2.xyzw[0];


	return product;
}

float VectorLength(VERTEX V1)
{
	float result = 0;

	return result = sqrt(std::pow(V1.xyzw[0], 2) + std::pow(V1.xyzw[1], 2) + std::pow(V1.xyzw[2], 2));
}

VERTEX NORMALIZE(VERTEX V1)
{
	VERTEX product = V1;

	product.xyzw[0] = product.xyzw[0] / VectorLength(V1);
	product.xyzw[1] = product.xyzw[1] / VectorLength(V1);
	product.xyzw[2] = product.xyzw[2] / VectorLength(V1);

	return product;
}

VERTEX SubstractVec3(VERTEX V1, VERTEX V2)
{
	VERTEX result = VERTEX();
	result.xyzw[0] = V1.xyzw[0] - V2.xyzw[0];
	result.xyzw[1] = V1.xyzw[1] - V2.xyzw[1];
	result.xyzw[2] = V1.xyzw[2] - V2.xyzw[2];

	return result;
}

unsigned int CombineColors(unsigned int C1, unsigned int C2)
{
	unsigned int newRed;
	unsigned int newGreen;
	unsigned int newBlue;
	//separate individual color channels for background pixel color
	unsigned int red1 = C1 & 0x00FF0000;
	unsigned int green1 = C1 & 0x0000FF00;
	unsigned int blue1 = C1 & 0x000000FF;

	//separate individual color channels for sprite pixel color
	unsigned int red2 = C2 & 0x00FF0000;
	unsigned int green2 = C2 & 0x0000FF00;
	unsigned int blue2 = C2 & 0x000000FF;

	//shift channel to least significant bit for ratio multiplication
	red1 = red1 >> 16;
	green1 = green1 >> 8;

	//shift channel to least significant bit for background
	red2 = red2 >> 16;
	green2 = green2 >> 8;

	if (red1 + red2 <= 255)
	{
		red1 = red1 + red2;
	}
	else
		red1 = 255;

	if (green1 + green2 <= 255)
	{
		green1 = green1 + green2;
	}
	else
		green1 = 255;

	if (blue1 + blue2 <= 255)
	{
		blue1 = blue1 + blue2;
	}
	else
		blue1 = 255;

	newRed = red1 << 16;
	newGreen = green1 << 8;
	newBlue = blue1;

	unsigned int newColor = newRed | newGreen | newBlue;

	return newColor;
}

unsigned int ModulateColors(unsigned int C1, unsigned int C2)
{
	unsigned int newRed;
	unsigned int newGreen;
	unsigned int newBlue;
	//separate individual color channels for background pixel color
	unsigned int red1 = C1 & 0x00FF0000;
	unsigned int green1 = C1 & 0x0000FF00;
	unsigned int blue1 = C1 & 0x000000FF;

	//separate individual color channels for sprite pixel color
	unsigned int red2 = C2 & 0x00FF0000;
	unsigned int green2 = C2 & 0x0000FF00;
	unsigned int blue2 = C2 & 0x000000FF;

	//shift channel to least significant bit for ratio multiplication
	red1 = red1 >> 16;
	green1 = green1 >> 8;

	//shift channel to least significant bit for background
	red2 = red2 >> 16;
	green2 = green2 >> 8;

	float redRatio1 = (float)red1 / 0x000000FF;
	float greenRatio1 = (float)green1 / 0x000000FF;
	float blueRatio1 = (float)blue1 / 0x000000FF;

	float redRatio2 = (float)red2 / 0x000000FF;
	float greenRatio2 = (float)green2 / 0x000000FF;
	float blueRatio2 = (float)blue2 / 0x000000FF;

	float modulatedRed = redRatio1 * redRatio2;
	float modulatedGreen = greenRatio1 * greenRatio2;
	float modulatedBlue = blueRatio1 * blueRatio2;

	newRed = modulatedRed * 255;
	newGreen = modulatedGreen * 255;
	newBlue = modulatedBlue * 255;

	newRed = newRed << 16;
	newGreen = newGreen << 8;

	unsigned int newColor = newRed | newGreen | newBlue;

	return newColor;
}

float Clamp(float decimal)
{

	float result = decimal;
	if (result > 1)
	{
		result = 1.0f;
	}
	else if (result < 0)
	{
		result = 0;
	}
	return result;
}

unsigned int DirectionalLight(VERTEX V1)
{
	float dotProductRatio = 0;
	VERTEX normals = VERTEX();
	VERTEX negDirectionLight = directionLight;
	VERTEX copyVert = V1;

	stoneHengeWorldMatrix = IdentityMatrix();

	for (int i = 0; i < 3; i++)
	{
		normals.xyzw[i] = copyVert.normals[i];
	}

	//store normals from surface
	normals = VectorMultMatrix(normals, IdentityMatrix());

	/*set direction x,y,z to negative*/
	for (int i = 0; i < 3; i++)
	{
		negDirectionLight.xyzw[i] = negDirectionLight.xyzw[i] * -1;
	}

	dotProductRatio = Clamp(DOT(negDirectionLight, normals));

	unsigned int dirLightColor = lerpPixelsRatio(0x00000000, directionLight.color, Clamp(dotProductRatio + ambientValue));

	VERTEX lightDir = NORMALIZE(SubstractVec3(pointLight, copyVert));

	dotProductRatio = Clamp(DOT(lightDir, normals));

	float attenuation = 1.0f - Clamp(VectorLength(SubstractVec3(pointLight, copyVert)) / pointLightRadi);

	unsigned int spotLightColor = lerpPixelsRatio(0x00000000, pointLight.color, dotProductRatio * attenuation);

	unsigned int newColor = CombineColors(dirLightColor, spotLightColor);

	return newColor;
}

unsigned int PointLight(VERTEX V1)
{
	VERTEX copyV1 = V1;
	VERTEX normals = VERTEX();
	float dotProductResult = 0;
	float lerpResult = 0;
	unsigned int newColor = 0;

	VERTEX lightDir = NORMALIZE(SubstractVec3(pointLight, copyV1));

	for (int i = 0; i < 3; i++)
	{
		normals.xyzw[i] = V1.normals[i];
	}

	dotProductResult = DOT(lightDir, normals);

	dotProductResult = dotProductResult + ambientValue;

	if (dotProductResult > 1)
	{
		dotProductResult = 1.0f;
	}
	else if (dotProductResult < 0)
	{
		dotProductResult = 0;
	}

	newColor = dotProductResult * pointLight.color;

	return newColor;
}

float randomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

int randomInt(int a, int b)
{
	if (a > b)
		return randomInt(b, a);
	if (a == b)
		return a;
	return a + (rand() % (b - a));
}

float randomFloat(int a, int b)
{
	if (a > b)
		return randomFloat(b, a);
	if (a == b)
		return a;

	return (float)randomInt(a, b) + randomFloat();
}