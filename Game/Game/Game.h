#pragma once
#include <utils.h>
using namespace utils;

#pragma region gameInformation
// TODO: Set your name and group in the title here
std::string g_WindowTitle{ "Game - Name, firstname - 1DAExx" };

// Change the window dimensions here
float g_WindowWidth{ 1280 };
float g_WindowHeight{ 720 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here

Color4f g_White{
	1.f,1.f,1.f,1.f
}, g_Green{
	0.f,1.f,0.f,1.f
};

float g_MouseX{};
float g_MouseY{};

Texture g_Obama;
const int g_CollumnAmount{13},
g_RowAmount{7},
g_GridAmount{ g_CollumnAmount * g_RowAmount };

const float g_GameWindowWidth{ g_WindowWidth / 16.f * 13.f },
g_GameWindowHeight{ g_WindowHeight / 9.f * 7.f };

float g_GridSize{ 80.f };

Point2f g_Intersections[g_GridAmount]{ Point2f{0.f, 0.f} };

Rectf g_Item1{
	g_GridSize * (g_CollumnAmount + 1),
	g_GridSize,
	g_GridSize,
	g_GridSize
};


// Declare your own functions here
void InitializeTextures();
void GenerateGridPositions();
void CheckGridPositions();
void DrawGrid();
void DrawItems(Rectf itemPos, Texture texture);
void DeleteTextures();
static void SelectAndPlace(Rectf& itemPrm);
void ShowClickedSquare(); // goes in draw

#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
