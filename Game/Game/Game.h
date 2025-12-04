#pragma once
#include <utils.h>
using namespace utils;

#pragma region gameInformation
// TODO: Set your name and group in the title here
std::string g_WindowTitle{ "Shitty Defence - Echoes of the Wind - 1DAE14-15" };

// Change the window dimensions here
float g_WindowWidth{ 1280 };
float g_WindowHeight{ 720 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here

Color4f 
g_White{
	1.f, 1.f, 1.f, 1.f
}, g_Green{
	0.f, 1.f, 0.f, 1.f
};

int 
g_SelectedConsumableIndex{ -1 };

float 
g_X{ 0.f },
g_Y{ 0.f };

Texture
g_Obama,
g_Castle,
g_Bomb,
g_Turret,
g_Tank,
g_Soldier;

const int 
g_CollumnAmount{13},
g_RowAmount{7},
g_ConsumableAmount{6},
g_GridAmount{ g_CollumnAmount * g_RowAmount };
Texture g_ConsumablesTextures[g_ConsumableAmount]{};

const float 
g_GameWindowWidth{ g_WindowWidth / 16.f * 13.f },
g_GameWindowHeight{ g_WindowHeight / 9.f * 7.f },
g_GridSquareSize{ 80.f };

Point2f
g_MousePosition{ 0.f, 0.f },
g_InitialConsumableLocation{ 0.f, 0.f },
g_arrIntersections[g_GridAmount]{ Point2f{0.f, 0.f} };

Rectf
g_arrConsumables[g_ConsumableAmount]{ 
	Rectf{
		0.f,
		0.f,
		0.f,
		0.f
	} 
},
g_GridPosition{
	0.f,
	g_GridSquareSize,
	g_GridSquareSize * g_CollumnAmount,
	g_GridSquareSize * g_RowAmount
};

bool
g_LeftClickToggled{ false };

// Declare your own functions here
void InitializeTextures();
void InitializeGridPositions();
void CheckGridPositions();
void DrawGrid();
void DrawItems(Rectf itemPos[], Texture texture[]);
void DeleteTextures();
void DragConsumable(Rectf& consumable);
void ClickConsumableToGrid(Rectf& consumable);
void InitializeConsumablePositions();
int GetGridIndexFromMousePosition();
void PutConsumableBack(Rectf& consumable);
void MouseInput();
bool IsMouseOutOfBounds();
bool IsMouseOutOfGrid();
bool IsConsumableInSlot();

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
