// Giffin_Zachary_ProgrammingAssignment4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RasterSurface.h"
#include "RasterizationFunctions.h"
#include "XTime.h"


int main()
{
	//spawn window
	RS_Initialize("Zachary Giffin: Assignment 4", screen_width, screen_height);

#if 1
#pragma region Grid Vertices
	//Grid Vertecies
	VERTEX gridbackLeft;
	VERTEX gridbackRight;
	VERTEX gridfrontLeft;
	VERTEX gridfrontRight;

	//Columns
	VERTEX column1Back;
	VERTEX column2Back;
	VERTEX column3Back;
	VERTEX column4Back;
	VERTEX column5Back;
	VERTEX column6Back;
	VERTEX column7Back;
	VERTEX column8Back;
	VERTEX column9Back;
	VERTEX column1Front;
	VERTEX column2Front;
	VERTEX column3Front;
	VERTEX column4Front;
	VERTEX column5Front;
	VERTEX column6Front;
	VERTEX column7Front;
	VERTEX column8Front;
	VERTEX column9Front;

	//Rows
	VERTEX Row1Left;
	VERTEX Row2Left;
	VERTEX Row3Left;
	VERTEX Row4Left;
	VERTEX Row5Left;
	VERTEX Row6Left;
	VERTEX Row7Left;
	VERTEX Row8Left;
	VERTEX Row9Left;

	VERTEX Row1Right;
	VERTEX Row2Right;
	VERTEX Row3Right;
	VERTEX Row4Right;
	VERTEX Row5Right;
	VERTEX Row6Right;
	VERTEX Row7Right;
	VERTEX Row8Right;
	VERTEX Row9Right;
#pragma endregion    
#endif // 1

	//Test for grid
#if 0
#pragma region Grid Test with Y and Z swapped
	//Grid Information
	backLeft = { -0.5f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	backRight = { 0.5f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	frontLeft = { -0.5f,-0.5f, 0.0f, 1, 0xFFFFFFFF };
	frontRight = { 0.5f,-0.5f, 0.0f, 1, 0xFFFFFFFF };

	//Columns
	column1Back = { -0.4f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	column2Back = { -0.3f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	column3Back = { -0.2f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	column4Back = { -0.1f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	column5Back = { 0.0f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	column6Back = { 0.1f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	column7Back = { 0.2f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	column8Back = { 0.3f, 0.5f, 0.0f, 1, 0xFFFFFFFF };
	column9Back = { 0.4f, 0.5f, 0.0f, 1, 0xFFFFFFFF };

	column1Front = { -0.4f, -0.5f, 0.0f, 1, 0xFFFFFFFF };
	column2Front = { -0.3f, -0.5f, 0.0f, 1, 0xFFFFFFFF };
	column3Front = { -0.2f, -0.5f, 0.0f, 1, 0xFFFFFFFF };
	column4Front = { -0.1f, -0.5f, 0.0f, 1, 0xFFFFFFFF };
	column5Front = { 0.0f, -0.5f, 0.0f, 1, 0xFFFFFFFF };
	column6Front = { 0.1f, -0.5f, 0.0f, 1, 0xFFFFFFFF };
	column7Front = { 0.2f, -0.5f, 0.0f, 1, 0xFFFFFFFF };
	column8Front = { 0.3f, -0.5f, 0.0f, 1, 0xFFFFFFFF };
	column9Front = { 0.4f, -0.5f, 0.0f, 1, 0xFFFFFFFF };

	//Rows
	Row1Left = { -0.5f, -0.4f, 0.0f, 1, 0xFFFFFFFF };
	Row2Left = { -0.5f, -0.3f, 0.0f, 1, 0xFFFFFFFF };
	Row3Left = { -0.5f, -0.2f, 0.0f, 1, 0xFFFFFFFF };
	Row4Left = { -0.5f, -0.1f, 0.0f, 1, 0xFFFFFFFF };
	Row5Left = { -0.5f,  0.0f, 0.0f, 1, 0xFFFFFFFF };
	Row6Left = { -0.5f,  0.1f, 0.0f, 1, 0xFFFFFFFF };
	Row7Left = { -0.5f,  0.2f, 0.0f, 1, 0xFFFFFFFF };
	Row8Left = { -0.5f,  0.3f, 0.0f, 1, 0xFFFFFFFF };
	Row9Left = { -0.5f,  0.4f, 0.0f, 1, 0xFFFFFFFF };

	Row1Right = { 0.5f, -0.4f, 0.0f, 1, 0xFFFFFFFF };
	Row2Right = { 0.5f, -0.3f, 0.0f, 1, 0xFFFFFFFF };
	Row3Right = { 0.5f, -0.2f, 0.0f, 1, 0xFFFFFFFF };
	Row4Right = { 0.5f, -0.1f, 0.0f, 1, 0xFFFFFFFF };
	Row5Right = { 0.5f,  0.0f, 0.0f, 1, 0xFFFFFFFF };
	Row6Right = { 0.5f,  0.1f, 0.0f, 1, 0xFFFFFFFF };
	Row7Right = { 0.5f,  0.2f, 0.0f, 1, 0xFFFFFFFF };
	Row8Right = { 0.5f,  0.3f, 0.0f, 1, 0xFFFFFFFF };
	Row9Right = { 0.5f,  0.4f, 0.0f, 1, 0xFFFFFFFF };
#pragma endregion
#endif // 0


#if 1
#pragma region Grid Variable Assignemnt
	//Grid Information
	gridbackLeft = { -0.5f, 0.0f,  0.5f, 1, 0xFFFFFFFF };
	gridbackRight = { 0.5f, 0.0f,  0.5f, 1, 0xFFFFFFFF };
	gridfrontLeft = { -0.5f, 0.0f, -0.5f, 1, 0xFFFFFFFF };
	gridfrontRight = { 0.5f, 0.0f, -0.5f, 1, 0xFFFFFFFF };

	//Columns
	column1Back = { -0.4f, 0.0f, 0.5f, 1, 0xFFFFFFFF };
	column2Back = { -0.3f, 0.0f, 0.5f, 1, 0xFFFFFFFF };
	column3Back = { -0.2f, 0.0f, 0.5f, 1, 0xFFFFFFFF };
	column4Back = { -0.1f, 0.0f, 0.5f, 1, 0xFFFFFFFF };
	column5Back = { 0.0f, 0.0f, 0.5f, 1, 0xFFFFFFFF };
	column6Back = { 0.1f, 0.0f, 0.5f, 1, 0xFFFFFFFF };
	column7Back = { 0.2f, 0.0f, 0.5f, 1, 0xFFFFFFFF };
	column8Back = { 0.3f, 0.0f, 0.5f, 1, 0xFFFFFFFF };
	column9Back = { 0.4f, 0.0f, 0.5f, 1, 0xFFFFFFFF };

	column1Front = { -0.4f, 0.0f, -0.5f, 1, 0xFFFFFFFF };
	column2Front = { -0.3f, 0.0f, -0.5f, 1, 0xFFFFFFFF };
	column3Front = { -0.2f, 0.0f, -0.5f, 1, 0xFFFFFFFF };
	column4Front = { -0.1f, 0.0f, -0.5f, 1, 0xFFFFFFFF };
	column5Front = { 0.0f, 0.0f,  -0.5f, 1, 0xFFFFFFFF };
	column6Front = { 0.1f, 0.0f,  -0.5f, 1, 0xFFFFFFFF };
	column7Front = { 0.2f, 0.0f,  -0.5f, 1, 0xFFFFFFFF };
	column8Front = { 0.3f, 0.0f,  -0.5f, 1, 0xFFFFFFFF };
	column9Front = { 0.4f, 0.0f,  -0.5f, 1, 0xFFFFFFFF };

	//Rows
	Row1Left = { -0.5f, 0.0f, -0.4f, 1, 0xFFFFFFFF };
	Row2Left = { -0.5f, 0.0f, -0.3f, 1, 0xFFFFFFFF };
	Row3Left = { -0.5f, 0.0f, -0.2f, 1, 0xFFFFFFFF };
	Row4Left = { -0.5f, 0.0f, -0.1f, 1, 0xFFFFFFFF };
	Row5Left = { -0.5f, 0.0f,  0.0f, 1, 0xFFFFFFFF };
	Row6Left = { -0.5f, 0.0f,  0.1f, 1, 0xFFFFFFFF };
	Row7Left = { -0.5f, 0.0f,  0.2f, 1, 0xFFFFFFFF };
	Row8Left = { -0.5f, 0.0f,  0.3f, 1, 0xFFFFFFFF };
	Row9Left = { -0.5f, 0.0f,  0.4f, 1, 0xFFFFFFFF };

	Row1Right = { 0.5f, 0.0f, -0.4f, 1, 0xFFFFFFFF };
	Row2Right = { 0.5f, 0.0f, -0.3f, 1, 0xFFFFFFFF };
	Row3Right = { 0.5f, 0.0f, -0.2f, 1, 0xFFFFFFFF };
	Row4Right = { 0.5f, 0.0f, -0.1f, 1, 0xFFFFFFFF };
	Row5Right = { 0.5f, 0.0f,  0.0f, 1, 0xFFFFFFFF };
	Row6Right = { 0.5f, 0.0f,  0.1f, 1, 0xFFFFFFFF };
	Row7Right = { 0.5f, 0.0f,  0.2f, 1, 0xFFFFFFFF };
	Row8Right = { 0.5f, 0.0f,  0.3f, 1, 0xFFFFFFFF };
	Row9Right = { 0.5f, 0.0f,  0.4f, 1, 0xFFFFFFFF };

	gridWorldMatrix = IdentityMatrix();

#pragma endregion
#endif // 0

#if 1
#pragma region Box Vertices
	//Box Vertices Bottom
	VERTEX backLeftBottom;
	VERTEX backRightBottom;
	VERTEX frontRightBottom;
	VERTEX frontLeftBottom;

	VERTEX frontLeftTop;
	VERTEX backLeftTop;
	VERTEX backRightTop;
	VERTEX frontRightTop;
#pragma endregion
#endif // 0

#if 1
#pragma region Box Variable Assignment

	//stores vertecies(float,float,float,float,unsigned int)
	VERTEX cube[8] = {};

	//storing Vertecies in an array    
	backLeftBottom = { -0.25f, -0.25f, 0.25, 1, 0xFFFFFFFF };
	backRightBottom = { 0.25, -0.25, 0.25, 1, 0xFFFFFFFF };
	frontRightBottom = { 0.25, -0.25, -0.25, 1, 0xFFFFFFFF };
	frontLeftBottom = { -0.25, -0.25, -0.25, 1, 0xFFFFFFFF };

	backLeftTop = { -0.25f, 0.25f, 0.25, 1, 0xFFFFFFFF };
	backRightTop = { 0.25f, 0.25f, 0.25, 1, 0xFFFFFFFF };
	frontRightTop = { 0.25f, 0.25f, -0.25, 1, 0xFFFFFFFF };
	frontLeftTop = { -0.25f, 0.25f, -0.25, 1, 0xFFFFFFFF };

	//cube here now
	cubeWorldMatrix = IdentityMatrix();
	//cube go up
	cubeWorldMatrix = MatrixMultMatrix(cubeWorldMatrix, Translation(0.0, 0.25, 0.0), 4, 4);

#pragma endregion

#endif // 1

#if 1
#pragma region Box with Triangles Vertecies

	TRIANGLE FrontFaceBottom;
	TRIANGLE FrontFaceTop;

	TRIANGLE RightFaceBottom;
	TRIANGLE RightFaceTop;

	TRIANGLE BackFaceBottom;
	TRIANGLE BackFaceTop;

	TRIANGLE LeftFaceBottom;
	TRIANGLE LeftFaceTop;

	TRIANGLE TopFaceBottom;
	TRIANGLE TopFaceTop;

	TRIANGLE BottomFaceBottom;
	TRIANGLE BottomFaceTop;

#pragma endregion
#endif // 1

#if 1
#pragma region Triangles Vertecies Assignment

	//A,B,C
	FrontFaceBottom = { { {-0.25, -0.25, -0.25, 1, 0,1},
					  { -0.25f, 0.25f, -0.25, 1, 0,0 },
					  {0.25f, -0.25f, -0.25, 1, 1,1} } };
	FrontFaceTop = { { {0.25f, 0.25f, -0.25, 1, 1,0},
					  { -0.25f, 0.25f, -0.25, 1, 0,0 },
					  {0.25f, -0.25f, -0.25, 1, 1,1} } };

	RightFaceBottom = { { {0.25f, -0.25f, -0.25, 1, 0,1},
					  { 0.25f, -0.25f, 0.25, 1, 1,1 },
					  {0.25f, 0.25f, -0.25, 1, 0,0} } };
	RightFaceTop = { { {0.25f, 0.25f, 0.25, 1, 1,0},
					  { 0.25f, 0.25f, -0.25, 1, 0,0 },
					  {0.25, -0.25, 0.25, 1, 1,1} } };

	BackFaceBottom = { { {0.25f,-0.25f,0.25f,1.0f,0,1},
					  { -0.25f,-0.25f,0.25f,1.0f,1,1 },
					  {0.25f,0.25f,0.25f,1.0f,0,0} } };
	BackFaceTop = { { {0.25f,0.25f,0.25f,1.0f,0,0},
					  { -0.25f,0.25f,0.25f,1.0f,1,0 },
					  {-0.25f,-0.25f,0.25f,1.0f,1,1} } };

	LeftFaceBottom = { { {-0.25f,-0.25f,0.25f,1.0f,0,1},
						 {-0.25f,0.25f,0.25f,1.0f,0,0 },
						 { -0.25f,-0.25f,-0.25f,1.0f,1,1} } };
	LeftFaceTop = { { {-0.25f,0.25f,-0.25f,1.0f,1,0},
					  {-0.25f,-0.25f,-0.25f,1.0f,1,1 },
					  {-0.25f,0.25f,0.25f,1.0f,0,0} } };

	TopFaceBottom = { { {-0.25f,0.25f,-0.25f,1.0f,0,1},
					  {-0.25f,0.25f,0.25f,1.0f,0,0 },
					  {0.25f,0.25f,-0.25f,1.0f,1,1} } };
	TopFaceTop = { { {-0.25f,0.25f,0.25f,1.0f,0,0},
					  {0.25f,0.25f,-0.25f,1.0f,1,1 },
					  {0.25f,0.25f,0.25f,1.0f,1,0} } };

	BottomFaceBottom = { { {-0.25f,-0.25f,-0.25f,1.0f,0,0},
					  { 0.25f,-0.25f,-0.25f,1.0f,1,0 },
					  {-0.25f,-0.25f,0.25f,1.0f,0,1} } };
	BottomFaceTop = { { {-0.25f,-0.25f,0.25f,1.0f,0,1},
					  { 0.25f,-0.25f,0.25f,1.0f,1,1 },
					  {0.25f,-0.25f,-0.25f,1.0f,1,0} } };

#pragma endregion
#endif // 1

	srand(time(0));		

	for (int i = 0; i < 3000; i++)
	{
		float random = randomFloat(-1, 1);

		starField[i].xyzw[0] = random * 50.0f;

		random = randomFloat(-1, 1);

		starField[i].xyzw[1] = random * 50.0f;

		random = randomFloat(-1, 1);

		starField[i].xyzw[2] = random * 50.0f;

		starField[i].xyzw[3] = 1.0f;
	}

	starFieldWorldMatrix = IdentityMatrix();

	//convert StoneHenge.h info to Type VERTEX
	for (int i = 0; i < 1457; i++)
	{
		stoneHenge[i].xyzw[0] = StoneHenge_data[i].pos[0] * 0.15f; 
		stoneHenge[i].xyzw[1] = StoneHenge_data[i].pos[1] * 0.15f;
		stoneHenge[i].xyzw[2] = StoneHenge_data[i].pos[2] * 0.15f;
		stoneHenge[i].xyzw[3] = 1.0f;

		stoneHenge[i].uv[0] = StoneHenge_data[i].uvw[0];
		stoneHenge[i].uv[1] = StoneHenge_data[i].uvw[1];

		stoneHenge[i].normals[0] = StoneHenge_data[i].nrm[0];
		stoneHenge[i].normals[1] = StoneHenge_data[i].nrm[1];
		stoneHenge[i].normals[2] = StoneHenge_data[i].nrm[2];
	}

	//Create Triangles from information above
	//Every 3 vertecies is a triangle
	int j = 0;
	for (int i = 0; i < 844; i++)
	{
		stoneHengeTriangles[i].abc[0] = stoneHenge[StoneHenge_indicies[j]];
		j += 1;
		stoneHengeTriangles[i].abc[1] = stoneHenge[StoneHenge_indicies[j]];
		j += 1;
		stoneHengeTriangles[i].abc[2] = stoneHenge[StoneHenge_indicies[j]];
		j += 1;
	}

	//set to identity matrix
	cameraMatrix = IdentityMatrix();
	//rotate on x axis
	cameraMatrix = MatrixMultMatrix(cameraMatrix, RotationX(-18.0f), 4, 4);
	//translate back and up
	cameraMatrix = MatrixMultMatrix(cameraMatrix, Translation(0.0f, 0.0f, -4.5f), 4, 4);
	printMatrix(cameraMatrix);
	viewMatrix = Inverse(cameraMatrix);
	printMatrix(viewMatrix);

	//color change
	XTime timer = XTime();
	timer.Restart();
	float elapsed = 0;
	//used for changing color of box
	int colorNumber = 0;

	//cube spin
	XTime rotationTimer = XTime();
	rotationTimer.Restart();
	float elapsedRotation = 0;

	//camera spin
	XTime cameraSpinTimer = XTime();
	cameraSpinTimer.Restart();
	float cameraSpinElapsed = 0;

	//loop till window is closed
	do
	{
		//color timer
		timer.Signal();
		//time before frrames
		float delta = timer.Delta();
		////running total time
		//float total = timer.TotalTime();
		//timer elapsed since last signal
		elapsed += delta;


		//cube spin
		rotationTimer.Signal();
		//time before frrames
		float rotationDelta = rotationTimer.Delta();
		//timer elapsed since last signal
		elapsedRotation += rotationDelta;

		//camera spin
		cameraSpinTimer.Signal();
		float cameraSpinDelta = cameraSpinTimer.Delta();
		cameraSpinElapsed += cameraSpinDelta;

		if (elapsedRotation > (1.0f / 12.0f))
		{
			//Rotation Code
			cubeWorldMatrix = MatrixMultMatrix(cubeWorldMatrix, RotationY(7.0f), 4, 4);

			elapsedRotation = 0;
		}

		if (cameraSpinElapsed > (1.0f / 12.0f))
		{
			if (GetKeyState('D') < 0)
			{
				cameraMatrix = MatrixMultMatrix(RotationY(5.0f), cameraMatrix, 4, 4);
				printMatrix(cameraMatrix);
				viewMatrix = Inverse(cameraMatrix);
				printMatrix(viewMatrix);
			}

			if (GetKeyState('A') < 0)
			{
				cameraMatrix = MatrixMultMatrix(RotationY(-5.0f), cameraMatrix, 4, 4);
				printMatrix(cameraMatrix);
				viewMatrix = Inverse(cameraMatrix);
				printMatrix(viewMatrix);
			}

			if (GetKeyState('W') < 0)
			{
				pointLightRadi = pointLightRadi + 0.5f;
				std::cout << pointLightRadi << std::endl;
			}

			if (GetKeyState('S') < 0)
			{
				pointLightRadi = pointLightRadi - 0.5f;
				std::cout << pointLightRadi << std::endl;
			}
			cameraSpinElapsed = 0;
		}

		ClearBuffer();
		for (unsigned int i = 0; i < screen_width * screen_height; i++)
		{
			z_buffer[i] = FLT_MAX;
		}
		VertexShader = VS_WorldShader;
		PixelShader = PS_Red;
#if 0

#pragma region Grid Draw
		//Grid Draw
		//Outside Edge
		newDrawLine(gridbackLeft, gridbackRight, gridWorldMatrix);
		newDrawLine(gridbackRight, gridfrontRight, gridWorldMatrix);
		newDrawLine(gridfrontRight, gridfrontLeft, gridWorldMatrix);
		newDrawLine(gridfrontLeft, gridbackLeft, gridWorldMatrix);

		//Columns
		newDrawLine(column1Back, column1Front, gridWorldMatrix);
		newDrawLine(column2Back, column2Front, gridWorldMatrix);
		newDrawLine(column3Back, column3Front, gridWorldMatrix);
		newDrawLine(column4Back, column4Front, gridWorldMatrix);
		newDrawLine(column5Back, column5Front, gridWorldMatrix);
		newDrawLine(column6Back, column6Front, gridWorldMatrix);
		newDrawLine(column7Back, column7Front, gridWorldMatrix);
		newDrawLine(column8Back, column8Front, gridWorldMatrix);
		newDrawLine(column9Back, column9Front, gridWorldMatrix);

		//Rows
		newDrawLine(Row1Left, Row1Right, gridWorldMatrix);
		newDrawLine(Row2Left, Row2Right, gridWorldMatrix);
		newDrawLine(Row3Left, Row3Right, gridWorldMatrix);
		newDrawLine(Row4Left, Row4Right, gridWorldMatrix);
		newDrawLine(Row5Left, Row5Right, gridWorldMatrix);
		newDrawLine(Row6Left, Row6Right, gridWorldMatrix);
		newDrawLine(Row7Left, Row7Right, gridWorldMatrix);
		newDrawLine(Row8Left, Row8Right, gridWorldMatrix);
		newDrawLine(Row9Left, Row9Right, gridWorldMatrix);
#pragma endregion

#endif // 0

#if 1

#pragma region Star Draw
		//Stars

		for (int i = 0; i < 3000; i++)
		{
			newDrawPixel(starField[i], starFieldWorldMatrix);
		}
		
#pragma endregion

#endif // 0

#if 1

#pragma region DrawStoneHengeWithTriangles

		PixelShaderUV = PS_UV;
		for (int i = 0; i < 844; i++)
		{		
			drawTriangle(stoneHengeTriangles[i], stoneHengeWorldMatrix);
		}

#pragma endregion 

#endif // 0

#if 0
		if (elapsed > (1.0f / 1.0f))
		{
			if (colorNumber == 6)
			{
				colorNumber = 0;
			}
			else
			{
				colorNumber++;
			}

			//reset delta for next frame
			elapsed = 0;
		}

		switch (colorNumber) {
		case 0:
			PixelShader = PS_Random;
			break;
		case 1:
			PixelShader = PS_White;
			break;
		case 2:
			PixelShader = PS_Green;
			break;
		case 3:
			PixelShader = PS_Blue;
			break;
		case 4:
			PixelShader = PS_Yellow;
			break;
		case 5:
			PixelShader = PS_Magenta;

			break;
		}



#pragma region BoxDraw
		newDrawLine(backLeftBottom, backRightBottom, cubeWorldMatrix);
		newDrawLine(backRightBottom, frontRightBottom, cubeWorldMatrix);
		newDrawLine(frontRightBottom, frontLeftBottom, cubeWorldMatrix);
		newDrawLine(frontLeftBottom, backLeftBottom, cubeWorldMatrix);
		newDrawLine(backLeftBottom, backLeftTop, cubeWorldMatrix);
		newDrawLine(backLeftTop, backRightTop, cubeWorldMatrix);
		newDrawLine(backRightTop, frontRightTop, cubeWorldMatrix);
		newDrawLine(frontRightTop, frontLeftTop, cubeWorldMatrix);
		newDrawLine(frontLeftTop, backLeftTop, cubeWorldMatrix);
		newDrawLine(frontLeftTop, frontLeftBottom, cubeWorldMatrix);
		newDrawLine(backRightTop, backRightBottom, cubeWorldMatrix);
		newDrawLine(frontRightTop, frontRightBottom, cubeWorldMatrix);
#pragma endregion

#endif // 0

#if 0

#pragma region DrawBoxWithTriangles

		PixelShader = PS_Random;
		PixelShaderUV = PS_UV;
		drawTriangle(FrontFaceBottom, cubeWorldMatrix);
		drawTriangle(FrontFaceTop, cubeWorldMatrix);

		PixelShader = PS_White;
		drawTriangle(RightFaceBottom, cubeWorldMatrix);
		drawTriangle(RightFaceTop, cubeWorldMatrix);

		PixelShader = PS_Green;
		drawTriangle(BackFaceBottom, cubeWorldMatrix);
		drawTriangle(BackFaceTop, cubeWorldMatrix);

		PixelShader = PS_Blue;
		drawTriangle(LeftFaceBottom, cubeWorldMatrix);
		drawTriangle(LeftFaceTop, cubeWorldMatrix);

		PixelShader = PS_Yellow;
		drawTriangle(TopFaceBottom, cubeWorldMatrix);
		drawTriangle(TopFaceTop, cubeWorldMatrix);

		PixelShader = PS_Magenta;
		drawTriangle(BottomFaceBottom, cubeWorldMatrix);
		drawTriangle(BottomFaceTop, cubeWorldMatrix);


#pragma endregion 

#endif // 0

	} while (RS_Update(screen_array, sizeof(screen_array) >> 2));

	RS_Shutdown();
}

