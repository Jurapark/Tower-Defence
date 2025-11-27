#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	InitializeTextures();
	GenerateGridPositions();
}

void Draw()
{
	ClearBackground();

	DrawGrid();
	DrawItems(g_Item1, g_Obama);
	SelectAndPlace(g_Item1);

}

void Update(float elapsedSec)
{
	// process input, do physics 

	// e.g. Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void End()
{
	DeleteTextures();
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	//switch (key)
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	g_MouseX = float(e.x);
	g_MouseY = float(e.y);
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	// SAMPLE CODE: print mouse position
	//const float mouseX{ float(e.x) };
	//const float mouseY{ float(e.y) };
	//std::cout << "  [" << mouseX << ", " << mouseY << "]\n";
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	// SAMPLE CODE: print mouse position
	//const float mouseX{ float(e.x) };
	//const float mouseY{ float(e.y) };
	//std::cout << "  [" << mouseX << ", " << mouseY << "]\n";
	
	// SAMPLE CODE: check which mouse button was pressed
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//	//std::cout << "Left mouse button released\n";
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here

void InitializeTextures() {
	if (!TextureFromFile("Resources/Obama.jpg", g_Obama)) {
		std::cout << "Obama didnt load '\n";
	}
}
void DeleteTextures() {
	DeleteTexture(g_Obama);
}

void GenerateGridPositions()
{
	for (int row{ 0 }; row < g_RowAmount; ++row)
	{
		for (int collumn{ 0 }; collumn < g_CollumnAmount; ++collumn)
		{
			g_Intersections[row * g_CollumnAmount + collumn].x = g_GridSize + g_GridSize * collumn;
			g_Intersections[row * g_CollumnAmount + collumn].y = 2 * g_GridSize + g_GridSize * row;
		}
	}
}

void DrawGrid()
{
	SetColor(g_White);
	for (int index{ 0 }; index <= g_RowAmount; ++index)
	{
		utils::DrawLine(Point2f{ 0.f , g_GridSize + g_GridSize * index }, Point2f{ g_GameWindowWidth , g_GridSize + g_GridSize * index });
	}

	for (int index{ 0 }; index < g_CollumnAmount; ++index)
	{
		utils::DrawLine(Point2f{ g_GridSize + g_GridSize * index , g_GridSize }, Point2f{ g_GridSize + g_GridSize * index , g_GridSize + g_GameWindowHeight });
	}
}

void CheckGridPositions()
{
	std::cout << "Grid positions\n";
	for (int index{ 0 }; index < g_GridAmount; ++index)
	{
		std::cout << "Square " << index << " position: {" << g_Intersections[index].x << ", " << g_Intersections[index].y << "}\n";
	}
}

void DrawItems(Rectf itemPos, Texture texture) {
	DrawTexture(texture, itemPos);
}
void SelectAndPlace(Rectf& itemPrm) {
	if (g_MouseX > itemPrm.left && g_MouseX < itemPrm.left + itemPrm.width && g_MouseY > itemPrm.top && g_MouseY < itemPrm.top + itemPrm.height) {
		float middleOfItemX{ itemPrm.left + (itemPrm.width / 2) };
		float middleOfItemY{ itemPrm.top + (itemPrm.height / 2) };
		SetColor(g_Green);
		DrawRect(itemPrm, 2.f);
	}
	std::cout << g_MouseX << ' ' << g_MouseY << '\n';
}
#pragma endregion ownDefinitions