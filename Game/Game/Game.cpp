#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	InitializeTextures();
	InitializeGridPositions();
	InitializeConsumablePositions();
	//CheckGridPositions();
}

void Draw()
{
	ClearBackground();

	DrawGrid();
	DrawItems(g_arrConsumables[0], g_Obama);
}

void Update(float elapsedSec)
{
	if (g_MoveConsumable)
	{
		ConsumableInteraction(g_arrConsumables[0]);
	}
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
	g_MousePosition.x = static_cast<float>(e.x);
	g_MousePosition.y = static_cast<float>(e.y);
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	SelectAndMove(Point2f{ g_arrConsumables[0].left, g_arrConsumables[0].top }, g_X, g_Y);
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	PlaceConsumable(g_arrConsumables[0]);
	g_MoveConsumable = false;
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

void InitializeGridPositions()
{
	for (int row{ 0 }; row < g_RowAmount; ++row)
	{
		for (int collumn{ 0 }; collumn < g_CollumnAmount; ++collumn)
		{
			g_arrIntersections[row * g_CollumnAmount + collumn].x = g_GridSquareSize * collumn;
			g_arrIntersections[row * g_CollumnAmount + collumn].y = g_GridSquareSize + g_GridSquareSize * row;
		}
	}
}

void InitializeConsumablePositions()
{
	for (int index{ 0 }; index < g_ConsumableAmount; ++index)
	{
		g_arrConsumables[index].left = g_GridPosition.left + g_GridPosition.width + g_GridSquareSize;
		g_arrConsumables[index].top = g_GridSquareSize + g_GridSquareSize * index;
	}
}

void DrawGrid()
{
	SetColor(g_White);
	//for (int index{ 0 }; index <= g_RowAmount; ++index)
	//{
	//	utils::DrawLine(Point2f{ 0.f , g_GridSquareSize + g_GridSquareSize * index }, Point2f{ g_GameWindowWidth , g_GridSquareSize + g_GridSquareSize * index });
	//}

	//for (int index{ 0 }; index < g_CollumnAmount; ++index)
	//{
	//	utils::DrawLine(Point2f{ g_GridSquareSize + g_GridSquareSize * index , g_GridSquareSize }, Point2f{ g_GridSquareSize + g_GridSquareSize * index , g_GridSquareSize + g_GameWindowHeight });
	//}
	utils::DrawRect(g_GridPosition);
}

void CheckGridPositions()
{
	std::cout << "Grid positions\n";
	for (int index{ 0 }; index < g_GridAmount; ++index)
	{
		std::cout << "Square " << index << " position: {" << g_arrIntersections[index].x << ", " << g_arrIntersections[index].y << "}\n";
	}
}

void DrawItems(Rectf itemPos, Texture texture) {
	DrawTexture(texture, itemPos);
}

void ClickConsumableToGrid(Rectf& consumable)
{
	int positionToArrayConversion{ static_cast<int>((g_MousePosition.x - g_GridPosition.left) / g_GridSquareSize)
		+ static_cast<int>((g_MousePosition.y - g_GridPosition.top) / g_GridSquareSize) * g_CollumnAmount };

	consumable.left = g_arrIntersections[positionToArrayConversion].x;
	consumable.top = g_arrIntersections[positionToArrayConversion].y;
}

void SelectAndMove(const Point2f& consumableLocation, float& xCoordinateDifference, float& yCoordinateDifference)
{
	g_TemporaryConsumableLocation = consumableLocation;
	if (g_MousePosition.x >= consumableLocation.x && g_MousePosition.x <= consumableLocation.x + g_GridSquareSize &&
		g_MousePosition.y >= consumableLocation.y && g_MousePosition.y <= consumableLocation.y + g_GridSquareSize)
	{
		xCoordinateDifference = g_MousePosition.x - consumableLocation.x;
		yCoordinateDifference = g_MousePosition.y - consumableLocation.y;
		g_MoveConsumable = true;
	}
}

void ConsumableInteraction(Rectf& consumable)
{
	if(g_MousePosition.x > (g_GridPosition.left + g_GridPosition.width))
	{
		consumable.left = g_MousePosition.x - g_X;
		consumable.top = g_MousePosition.y - g_Y;
	}
	else if(g_MousePosition.x <= (g_GridPosition.left + g_GridPosition.width))
	{
		ClickConsumableToGrid(g_arrConsumables[0]);
	}
}

void PlaceConsumable(Rectf& consumable)
{
	if (g_MousePosition.x > (g_GridPosition.left + g_GridPosition.width) || g_MousePosition.y < g_GridPosition.top ||
		g_MousePosition.y > (g_GridPosition.top + g_GridPosition.height))
	{
		consumable.left = g_TemporaryConsumableLocation.x;
		consumable.top = g_TemporaryConsumableLocation.y;
	}
	else
		return;
}
#pragma endregion ownDefinitions