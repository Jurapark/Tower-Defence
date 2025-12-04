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
	CheckGridPositions();
}

void Draw()
{
	ClearBackground();

	DrawGrid();
	DrawItems(g_arrConsumables, g_ConsumablesTextures);
}

void Update(float elapsedSec)
{
	if (g_SelectedConsumableIndex != -1 && IsMouseOutOfBounds() == false)
	{
		std::cout << g_SelectedConsumableIndex << "\n";
		DragConsumable(g_arrConsumables[g_SelectedConsumableIndex]);
		ClickConsumableToGrid(g_arrConsumables[g_SelectedConsumableIndex]);
	}
	else if (g_SelectedConsumableIndex >= 0)
	{
		PutConsumableBack(g_arrConsumables[g_SelectedConsumableIndex]);
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
	MouseInput();
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	PlaceConsumable(g_arrConsumables[g_SelectedConsumableIndex]);
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here

void InitializeTextures() {
	if (!TextureFromFile("Resources/Obama.jpg", g_Obama)) {
		std::cout << "Obama didnt load '\n";
	}
	if (!TextureFromFile("Resources/Crown.png", g_Castle)) {
		std::cout << "g_Castle didnt load '\n";
	}
	if (!TextureFromFile("Resources/Bombaclat.png", g_Bomb)) {
		std::cout << "g_Bomb didnt load '\n";
	}
	if (!TextureFromFile("Resources/Turret.png", g_Turret)) {
		std::cout << "g_Turret didnt load '\n";
	}
	if (!TextureFromFile("Resources/Soldier.png", g_Soldier)) {
		std::cout << "g_Soldier didnt load '\n";
	}
	if (!TextureFromFile("Resources/Tank.png", g_Tank)) {
		std::cout << "g_Tank didnt load '\n";
	}
	Texture tempTxtArr[g_ConsumableAmount]{ g_Obama , g_Castle , g_Bomb , g_Turret , g_Soldier , g_Tank };
	for (int index{ 0 }; index < g_ConsumableAmount; index++) {
		g_ConsumablesTextures[index] = tempTxtArr[index];
		g_arrConsumables[index].width = g_GridSquareSize;
		g_arrConsumables[index].height = g_GridSquareSize;
	}
}

void DeleteTextures() {
	DeleteTexture(g_Obama);
	DeleteTexture(g_Castle);
	DeleteTexture(g_Bomb);
	DeleteTexture(g_Turret);
	DeleteTexture(g_Soldier);
	DeleteTexture(g_Tank);
}

void InitializeGridPositions()
{
	for (int row{ 0 }; row < g_RowAmount; ++row)
	{
		for (int collumn{ 0 }; collumn < g_CollumnAmount; ++collumn)
		{
			g_arrIntersections[row * g_CollumnAmount + collumn].originLocation.x = g_GridSquareSize * collumn;
			g_arrIntersections[row * g_CollumnAmount + collumn].originLocation.y = g_GridSquareSize + g_GridSquareSize * row;
			g_arrIntersections[row * g_CollumnAmount + collumn].consumableIndex = -1;
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
		std::cout << "Square " << index << " index: " << g_arrIntersections[index].consumableIndex << "\n";
	}
}

void DrawItems(Rectf itemPos[], Texture texture[]) {
	for (int i{ 0 }; i < g_ConsumableAmount; i++) {
		DrawTexture(texture[i], itemPos[i]);
	}
}

void MouseInput()
{

	if (IsMouseOutOfBounds() || FindConsumable() == -1)
	{
		return;
	}
	int gridIndex{ GetGridIndex() };
	if (gridIndex != -1 && g_arrIntersections[gridIndex].consumableIndex > 0)
	{
		g_SelectedConsumableIndex = g_arrIntersections[gridIndex].consumableIndex;
		return;
	}

	g_SelectedConsumableIndex = FindConsumable();
	g_InitialConsumableLocation = Point2f{ g_GridPosition.left + g_GridPosition.width + g_GridSquareSize,
		g_GridSquareSize + g_GridSquareSize * g_SelectedConsumableIndex };

}

void ClickConsumableToGrid(Rectf& consumable)
{
	if (g_MousePosition.x < (g_GridPosition.left + g_GridPosition.width))
	{
		int positionToArrayConversion{ static_cast<int>((g_MousePosition.x - g_GridPosition.left) / g_GridSquareSize)
			+ static_cast<int>((g_MousePosition.y - g_GridPosition.top) / g_GridSquareSize) * g_CollumnAmount };

		consumable.left = g_arrIntersections[positionToArrayConversion].originLocation.x;
		consumable.top = g_arrIntersections[positionToArrayConversion].originLocation.y;
	}
}

void DragConsumable(Rectf& consumable)
{
	std::cout << consumable.left << " " << consumable.top;
	consumable.left = g_MousePosition.x - consumable.width * 0.5f;
	consumable.top = g_MousePosition.y - consumable.height * 0.5f;
}

void PutConsumableBack(Rectf& consumable) // problem here
{
	if (IsMouseOutOfGrid() == true && g_SelectedConsumableIndex != -1)
	{
		g_arrConsumables[g_SelectedConsumableIndex].left = g_InitialConsumableLocation.x;
		g_arrConsumables[g_SelectedConsumableIndex].top = g_InitialConsumableLocation.y;
		g_SelectedConsumableIndex = -1;
	}
}

bool IsMouseOutOfBounds()
{
	return
		g_MousePosition.y <= g_GridPosition.top ||
		g_MousePosition.y >= (g_GridPosition.top + g_GridPosition.height);
}

bool IsMouseOutOfGrid()
{
	return g_MousePosition.x > (g_GridPosition.left + g_GridPosition.width);
}

bool IsConsumableInSlot()
{
	return false;
}

int FindConsumable()
{
	if (g_MousePosition.x < (g_GridPosition.left + g_GridSquareSize * 14) || g_MousePosition.x >(g_GridPosition.left + g_GridSquareSize * 15))
	{
		return -1;
	}
	return static_cast<int>(g_MousePosition.y - g_GridSquareSize) / static_cast<int>(g_GridSquareSize);
}

int GetGridIndex()
{
	if (IsMouseOutOfGrid() == true)
	{
		return -1;
	}
	int collumn{ static_cast<int>(g_MousePosition.y) / static_cast<int>(g_GridSquareSize) };
	int row{ static_cast<int>(g_MousePosition.x) / static_cast<int>(g_GridSquareSize) };

	return collumn + row * g_RowAmount;
}

void PlaceConsumable(Rectf& consumable)
{
	int gridIndex = GetGridIndex();
	if (g_arrIntersections[gridIndex].consumableIndex == -1 || gridIndex == -1)
	{
		PutConsumableBack(g_arrConsumables[g_SelectedConsumableIndex]);
		g_SelectedConsumableIndex = -1;
		return;
	}
	g_arrConsumables[g_SelectedConsumableIndex].left = g_arrIntersections[gridIndex].originLocation.x;
	g_arrConsumables[g_SelectedConsumableIndex].top = g_arrIntersections[gridIndex].originLocation.y;
	g_arrIntersections[gridIndex].consumableIndex = g_SelectedConsumableIndex;
}

#pragma endregion ownDefinitions