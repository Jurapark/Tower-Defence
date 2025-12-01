#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	InitializeTextures();
<<<<<<< Updated upstream
	GenerateGridPositions();
	//add comment
	for (int index{ 0 }; index < g_GridAmount; ++index)
	{
		std::cout << "Coordinates at : {" << g_Intersections[index].x << ", " << g_Intersections[index].y << "}\n";
	}
=======
	InitializeGridPositions();
	InitializeConsumablePositions();
	//CheckGridPositions();
	
>>>>>>> Stashed changes
}

void Draw()
{
	ClearBackground();
	
	DrawGrid();
<<<<<<< Updated upstream
	DrawItems(g_Item1, g_Obama);
	SelectAndPlace(g_Item1);
	ShowClickedSquare();
=======
	DrawItems(g_arrConsumables, g_ArrConsumableTextures);
>>>>>>> Stashed changes
}

void Update(float elapsedSec)
{
<<<<<<< Updated upstream
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
=======
	if (g_MoveConsumable)
	{
		ConsumableInteraction(g_arrConsumables[FindConsumable()]);
	}
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	if (e.button == SDL_BUTTON_LEFT && g_MouseOnItem==true) {
		g_LeftClickToggled = !g_LeftClickToggled;
	}
=======
	SelectAndMove(Point2f{ g_arrConsumables[FindConsumable()].left, g_arrConsumables[FindConsumable()].top}, g_X, g_Y);
>>>>>>> Stashed changes
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
	if (!TextureFromFile("Resources/Crown.png", g_Castle)) {
		std::cout << "Castle didnt load '\n";
	}
	if (!TextureFromFile("Resources/Soldier.png", g_Soldier)) {
		std::cout << "Castle didnt load '\n";
	}
	if (!TextureFromFile("Resources/Bombaclat.png", g_Bomb)) {
		std::cout << "Castle didnt load '\n";
	}
	if (!TextureFromFile("Resources/Turret.png", g_Turret)) {
		std::cout << "Castle didnt load '\n";
	}
	if (!TextureFromFile("Resources/Tank.png", g_Tank)) {
		std::cout << "Castle didnt load '\n";
	}
	Texture tempArr[g_ConsumableAmount]{ g_Obama , g_Castle, g_Soldier, g_Bomb, g_Turret, g_Tank };
	for (int i{ 0 }; i < g_ConsumableAmount; i++) {
		g_ArrConsumableTextures[i] = tempArr[i];
	}
}

void DeleteTextures() {
	DeleteTexture(g_Obama);
	DeleteTexture(g_Castle);
	DeleteTexture(g_Soldier);
	DeleteTexture(g_Bomb);
	DeleteTexture(g_Turret);
	DeleteTexture(g_Tank);
}

int FindConsumable()
{
	return static_cast<int>(g_MousePosition.y - g_arrConsumables[0].top) / static_cast<int>(g_GridSquareSize);
}

void GenerateGridPositions()
{
	for (int row{ 0 }; row < g_RowAmount; ++row)
	{
		for (int collumn{ 0 }; collumn < g_CollumnAmount; ++collumn)
		{
			g_Intersections[row * g_CollumnAmount + collumn].x = g_GridSize * collumn;
			g_Intersections[row * g_CollumnAmount + collumn].y = g_GridSize + g_GridSize * row;
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

void DrawItems(Rectf itemPos[], Texture texture[]) {
	

	for (int i{ 0 }; i < g_ConsumableAmount; i++) {
		DrawTexture(texture[i], itemPos[i]);
	}
}

void SelectAndPlace(Rectf& itemPrm) {
	if (g_MouseX > itemPrm.left && g_MouseX < itemPrm.left + itemPrm.width && g_MouseY > itemPrm.top && g_MouseY < itemPrm.top + itemPrm.height) {
		float middleOfItemX{ itemPrm.left + (itemPrm.width / 2) };
		float middleOfItemY{ itemPrm.top + (itemPrm.height / 2) };
		SetColor(g_Green);
		DrawRect(itemPrm, 2.f);
		g_MouseOnItem = true;
	}
	else if (g_LeftClickToggled == false) {
		g_MouseOnItem = false;
	}
	if (g_MouseX > g_CollumnAmount * g_GridSize) {
		g_MouseInGrid = true;
	}

	std::cout << g_MouseX << ' ' << g_MouseY << '\n';
	if (g_MouseOnItem == true && g_LeftClickToggled == true && g_MouseInGrid == true) {
		itemPrm.left = g_MouseX - (itemPrm.width / 2);
		itemPrm.top = g_MouseY - (itemPrm.height / 2);
	}
}

void ShowClickedSquare() // make it to a changeable variable
{
	Rectf clickedSquare
	{
<<<<<<< Updated upstream
		0.f, 0.f, g_GridSize, g_GridSize
	};
=======
		consumable.left = g_MousePosition.x - g_X;
		consumable.top = g_MousePosition.y - g_Y;
	}
	else if(g_MousePosition.x <= (g_GridPosition.left + g_GridPosition.width))
	{
		ClickConsumableToGrid(g_arrConsumables[FindConsumable()]);
	}
}
>>>>>>> Stashed changes

	for (int index{ 0 }; index < g_CollumnAmount; ++index)
	{
		if (g_Intersections[index].x <= g_MouseX && (g_Intersections[index].x + g_GridSize) >= g_MouseX)
		{
			g_Item1.left = g_Intersections[index].x;
		}
	}

	for (int index{ 0 }; index < g_RowAmount; ++index)
	{
		if ((g_Intersections[index * g_CollumnAmount].y) <= g_MouseY && (g_Intersections[index * g_CollumnAmount].y + g_GridSize) >= g_MouseY)
		{
			g_Item1.top = g_Intersections[index * g_CollumnAmount].y;
		}
	}

	//utils::FillRect(clickedSquare);
}
#pragma endregion ownDefinitions