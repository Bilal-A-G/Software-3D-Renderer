#include <array>
#include "NextAPI/app.h"
#include "Math.h"
#include "Mesh.h"

TESLA::Mesh* cube;
constexpr float cubeSize = 2;

constexpr float nearPlane = 0.1f;
constexpr float farPlane = 1000.0f;
constexpr float fov = 90.0f;
constexpr float aspectRatio = GLUT_SCREEN_HEIGHT/GLUT_SCREEN_WIDTH;
const float fovRad = 1.0f / tan(fov/2 / PI * 180);

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	TESLA::Vector bottomLeft = TESLA::Vector(-1, -1, -1);
	TESLA::Vector bottomRight = TESLA::Vector(1, -1, -1);

	TESLA::Vector topLeft = TESLA::Vector(-1, 1, -1);
	TESLA::Vector topRight = TESLA::Vector(1, 1, -1);

	TESLA::Vector bottomLeftBack = TESLA::Vector(-1, -1, 1);
	TESLA::Vector bottomRightBack = TESLA::Vector(1, -1, 1);

	TESLA::Vector topLeftBack = TESLA::Vector(-1, 1, 1);
	TESLA::Vector topRightBack = TESLA::Vector(1, 1, 1);
	
	std::vector<TESLA::Triangle> triangles
	{
		//Front
		{bottomLeft, topLeft, topRight},
		{topRight, bottomRight, bottomLeft},

		//Back
		{ bottomLeftBack, topLeftBack, topRightBack},
		{topRightBack, bottomRightBack, bottomLeftBack},

		//Left
		{topLeftBack, topLeft, bottomLeft},
		{bottomLeft, bottomLeftBack, topLeftBack},

		//Right
		{topRight, topRightBack, bottomRightBack},
		{bottomRightBack, bottomRight, topRight},

		//Up
		{topLeftBack, topRightBack, topRight},
		{topRight, topLeft, topLeftBack},

		//Down
		{bottomRightBack, bottomLeftBack, bottomLeft},
		{bottomLeft, bottomRight, bottomRightBack},
	};

	TESLA::Matrix4x4 projection = TESLA::Matrix4x4{
		{aspectRatio * fovRad, 0.0f, 0.f, 0.0f},
		{0.0f, fovRad, 0.0f, 0.0f},
		{0.0f, 0.0f, farPlane/(farPlane - nearPlane), 1.0f},
		{0.0f, 0.0f, -farPlane * nearPlane/(farPlane - nearPlane), 0.0f}
	};

	cube = new TESLA::Mesh(triangles, TESLA::Matrix4x4::Identity(), projection);
	cube->Scale(cubeSize * 100, TESLA::Vector(1,1,1));
	cube->Translate(TESLA::Vector{-650, -420, 0});
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	cube->Rotate(0.05, TESLA::Vector(0, 1, 1));
	
	for (TESLA::Triangle triangle : cube->GetProjectedTriangles())
	{
		App::DrawLine(triangle.vertices[0].x, triangle.vertices[0].y,
			triangle.vertices[1].x, triangle.vertices[1].y);
	
		App::DrawLine(triangle.vertices[1].x, triangle.vertices[1].y,
			triangle.vertices[2].x, triangle.vertices[2].y);
	}
	
	App::Print(100, 100, "Amogus");
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	delete(cube);
}
