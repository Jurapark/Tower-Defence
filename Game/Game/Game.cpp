#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	g_EnemiesCount = 1;
	g_Enemies = new EnemyInfo[g_EnemiesCount]{};

	InitializeTextures();
	InitializeGridPositions();
	g_SpirPathCapacity = 11;
	g_SpirPath = new Point2f[g_SpirPathCapacity]{};
	CreateSpiralPath(g_GridPosition);
	InitializeConsumablePositions();
	AddPathTilesToIntersections(g_SpirPath, g_SpirPathSize);
	CheckGridPositions();
	AddConsumableParameters(g_arrConsumables);
}

void Draw()
{
	ClearBackground();

	DrawRoadAndGrass(g_GridPosition);
	DrawItems(g_arrConsumables, g_ConsumablesTextures);
	DrawEnemies();
	DrawGrid();
	DrawHealthBar(g_HealthAmount, g_MaxHealthAmount);
}

void Update(float elapsedSec)
{
	g_EnemySpawnTime += 1 * elapsedSec;
	g_TimeFlow += 1 * elapsedSec;
	g_Tst += 1 * elapsedSec;
	if (g_EnemySpawnTime >= 2.f) {
		SpawnEnemy();
		g_EnemySpawnTime = 0;
	}
	if (g_SelectedConsumableIndex != -1 && IsMouseOutOfBounds() == false)
	{
		MoveConsumable(g_arrConsumables[g_SelectedConsumableIndex].position);
		ClickConsumableToGrid(g_arrConsumables[g_SelectedConsumableIndex].position);
	}
	else if (g_SelectedConsumableIndex >= 0)
	{
		PutConsumableBack(g_SelectedConsumableIndex);
	}

	EnemyMovement(elapsedSec);

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
	if (IsMouseOutOfBounds() == true)
	{
		return;
	}
	else if (IsMouseOutOfGrid() == true)
	{
		SelectConsumable();
	}
	else if (IsMouseOutOfGrid() == false)
	{
		std::cout << g_arrIntersections[GetGridIndex(g_MousePosition)].isTaken << "\n";
	}
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (g_SelectedConsumableIndex != -1)
	{
		int gridIndex{ GetGridIndex(g_MousePosition) };
		if (IsMouseOutOfBounds() == true || IsMouseOutOfGrid() == true || g_arrIntersections[gridIndex].isTaken)
		{
			PutConsumableBack(g_SelectedConsumableIndex);
		}
		else
		{
			PlaceConsumableOnGrid(g_arrConsumables[g_SelectedConsumableIndex].position, g_arrIntersections[gridIndex]);
		}

		g_SelectedConsumableIndex = -1;
	}
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
	if (!TextureFromFile("Resources/Grass.png", g_Grass)) {
		std::cout << "g_Tank didnt load '\n";
	}
	if (!TextureFromFile("Resources/Road.png", g_Road)) {
		std::cout << "g_Tank didnt load '\n";
	}
	if (!TextureFromFile("Resources/Enemy.png", g_Enemy)) {
		std::cout << "g_Tank didnt load '\n";
	}
	Texture tempTxtArr[g_ConsumableAmount]{ g_Obama , g_Bomb , g_Turret , g_Soldier , g_Tank };
	for (int index{ 0 }; index < g_ConsumableAmount; index++) {
		g_ConsumablesTextures[index] = tempTxtArr[index];
		g_arrConsumables[index].position.width = g_GridSquareSize;
		g_arrConsumables[index].position.height = g_GridSquareSize;
	}
}

void DeleteTextures() {
	DeleteTexture(g_Obama);
	DeleteTexture(g_Castle);
	DeleteTexture(g_Bomb);
	DeleteTexture(g_Turret);
	DeleteTexture(g_Soldier);
	DeleteTexture(g_Tank);
	DeleteTexture(g_Grass);
	DeleteTexture(g_Road);
	DeleteTexture(g_Enemy);
}

void InitializeGridPositions()
{
	for (int row{ 0 }; row < g_RowAmount; ++row)
	{
		for (int collumn{ 0 }; collumn < g_CollumnAmount; ++collumn)
		{
			g_arrIntersections[row * g_CollumnAmount + collumn].originLocation.x = g_GridSquareSize * collumn;
			g_arrIntersections[row * g_CollumnAmount + collumn].originLocation.y = g_GridSquareSize + g_GridSquareSize * row;
			g_arrIntersections[row * g_CollumnAmount + collumn].isTaken = false;
		}
	}
}

void InitializeConsumablePositions()
{
	for (int index{ 0 }; index < g_ConsumableAmount; ++index)
	{
		g_arrConsumables[index].position.left = g_GridPosition.left + g_GridPosition.width + g_GridSquareSize;
		g_arrConsumables[index].position.top = g_GridSquareSize + g_GridSquareSize * index;
	}
}

void DrawGrid()
{
	SetColor(g_White);
	for (int index{ 0 }; index <= g_RowAmount; ++index)
	{
		utils::DrawLine(Point2f{ 0.f , g_GridSquareSize + g_GridSquareSize * index }, Point2f{ g_GameWindowWidth , g_GridSquareSize + g_GridSquareSize * index });
	}

	for (int index{ 0 }; index < g_CollumnAmount; ++index)
	{
		utils::DrawLine(Point2f{ g_GridSquareSize + g_GridSquareSize * index , g_GridSquareSize }, Point2f{ g_GridSquareSize + g_GridSquareSize * index , g_GridSquareSize + g_GameWindowHeight });
	}
	utils::DrawRect(g_GridPosition);
}

void CheckGridPositions()
{
	std::cout << "Grid positions\n";
	for (int index{ 0 }; index < g_GridAmount; ++index)
	{
		std::cout << "Square " << index << " index: " << g_arrIntersections[index].isTaken << "\n";
	}
}

void DrawItems(ConsumableInfo itemPos[], Texture texture[]) {
	for (int i{ 0 }; i < g_ConsumableAmount; i++) {
		DrawTexture(texture[i], itemPos[i].position);
	}
	DrawTexture(g_Castle, g_arrIntersections[48].originLocation);
}

void ClickConsumableToGrid(Rectf& consumable)
{
	if (g_MousePosition.x < (g_GridPosition.left + g_GridPosition.width))
	{
		int gridIndex{ GetGridIndex(g_MousePosition) };

		consumable.left = g_arrIntersections[gridIndex].originLocation.x;
		consumable.top = g_arrIntersections[gridIndex].originLocation.y;
	}
}

void MoveConsumable(Rectf& consumable)
{
	consumable.left = g_MousePosition.x - consumable.width * 0.5f;
	consumable.top = g_MousePosition.y - consumable.height * 0.5f;
}

void PutConsumableBack(const int index)
{
	g_arrConsumables[index].position.left = g_InitialConsumableLocation.x;
	g_arrConsumables[index].position.top = g_InitialConsumableLocation.y;
}

bool IsMouseOutOfBounds()
{
	if (g_MousePosition.y <= g_GridPosition.top ||
		g_MousePosition.y >= (g_GridPosition.top + g_GridPosition.height))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsMouseOutOfGrid()
{
	if (g_MousePosition.x > (g_GridPosition.left + g_GridPosition.width))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int FindConsumable()
{
	if (g_MousePosition.y < (g_GridSquareSize + g_ConsumableAmount * g_GridSquareSize))
	{
		return static_cast<int>(g_MousePosition.y - g_GridSquareSize) / static_cast<int>(g_GridSquareSize);
	}
	else
	{
		return -1;
	}
}

int GetGridIndex(const Point2f& location)
{
	if (IsMouseOutOfGrid() == true)
	{
		return -1;
	}
	int collumn{ static_cast<int>(location.x) / static_cast<int>(g_GridSquareSize) };
	int row{ static_cast<int>(location.y - g_GridSquareSize) / static_cast<int>(g_GridSquareSize) };

	return collumn + row * g_CollumnAmount;
}

int GetGridIndex(const float left, const float top)
{
	if (IsMouseOutOfGrid() == true)
	{
		return -1;
	}
	int collumn{ static_cast<int>(left) / static_cast<int>(g_GridSquareSize) };
	int row{ static_cast<int>(top - g_GridSquareSize) / static_cast<int>(g_GridSquareSize) };

	return collumn + row * g_CollumnAmount;
}

void PlaceConsumableOnGrid(Rectf& consumable, Grid& intersection)
{
	consumable.left = intersection.originLocation.x;
	consumable.top = intersection.originLocation.y;
	intersection.isTaken = true;
}

void SelectConsumable()
{
	g_SelectedConsumableIndex = FindConsumable();
	g_InitialConsumableLocation = Point2f{
		g_arrConsumables[g_SelectedConsumableIndex].position.left,
		g_arrConsumables[g_SelectedConsumableIndex].position.top };
}

void DrawRoadAndGrass(Rectf coord) {
	Rectf curCord{ coord.left, coord.top, g_GridBlockSize.width, g_GridBlockSize.height };
	Rectf curCord2{ coord.left, coord.top + g_GridSquareSize, g_GridBlockSize.width, g_GridBlockSize.height };
	float originalWidth{ coord.width };
	float originalHeight{ coord.height };
	float originalLeft{ coord.left };
	float originalTop{ coord.top };

	int loops{ 0 };
	int loopAmm{ 7 };
	int loopAmm2{ 5 };
	bool
		goRight{ true },
		goDown{ false },
		goLeft{ false },
		goUp{ false };
	for (int i{ 0 }; i < g_GridAmount; i++) {
		if (loops < loopAmm) {
			DrawTexture(g_Grass, curCord);
		}
		if (goDown == true) {
			curCord.top += g_GridSquareSize;
		}
		else if (goRight == true) {
			curCord.left += g_GridSquareSize;
		}
		else if (goUp == true) {
			curCord.top -= g_GridSquareSize;
		}
		else if (goLeft == true) {
			curCord.left -= g_GridSquareSize;
		}

		if (curCord.left == coord.width - g_GridSquareSize && goRight == true) {
			goRight = !goRight;
			goDown = !goDown;
			coord.width -= 2 * g_GridSquareSize;
			loops++;
		}
		else if (curCord.top == coord.height && goDown == true) {
			goLeft = !goLeft;
			goDown = !goDown;
			coord.height -= 2 * g_GridSquareSize;
			loops++;
		}
		else if (curCord.left == coord.left && goLeft == true) {
			goLeft = !goLeft;
			goUp = !goUp;
			coord.left += 2 * g_GridSquareSize;
			loops++;
			if (loops == loopAmm) {
				DrawTexture(g_Grass, curCord);
			}
		}
		else if (curCord.top == coord.top + 2 * g_GridSquareSize && goUp == true) {
			goRight = !goRight;
			goUp = !goUp;
			coord.top += 2 * g_GridSquareSize;
			loops++;
		}
	}
	loops = 0;
	goDown = false;
	goLeft = false;
	goUp = false;
	goRight = true;
	coord.width = originalWidth - g_GridSquareSize;
	coord.height = originalHeight - g_GridSquareSize;
	coord.left = originalLeft + g_GridSquareSize;
	coord.top = originalTop + g_GridSquareSize;
	for (int i{ 0 }; i < g_GridAmount; i++) {
		if (loops < loopAmm2) {
			DrawTexture(g_Road, curCord2);
			g_arrIntersections[GetGridIndex(curCord2.left, curCord2.top)].isTaken = true;
		}
		if (goDown == true) {
			curCord2.top += g_GridSquareSize;
		}
		else if (goRight == true) {
			curCord2.left += g_GridSquareSize;
		}
		else if (goUp == true) {
			curCord2.top -= g_GridSquareSize;
		}
		else if (goLeft == true) {
			curCord2.left -= g_GridSquareSize;
		}

		if (curCord2.left == coord.width - g_GridSquareSize && goRight == true) {
			goRight = !goRight;
			goDown = !goDown;
			coord.width -= 2 * g_GridSquareSize;
			loops++;
			if (loops == loopAmm2) {
				DrawTexture(g_Road, curCord2);
				g_arrIntersections[GetGridIndex(curCord2.left, curCord2.top)].isTaken = true;
			}
		}
		else if (curCord2.top == coord.height && goDown == true) {
			goLeft = !goLeft;
			goDown = !goDown;
			coord.height -= 2 * g_GridSquareSize;
			loops++;
		}
		else if (curCord2.left == coord.left && goLeft == true) {
			goLeft = !goLeft;
			goUp = !goUp;
			coord.left += 2 * g_GridSquareSize;
			loops++;
		}
		else if (curCord2.top == coord.top + 2 * g_GridSquareSize && goUp == true) {
			goRight = !goRight;
			goUp = !goUp;
			coord.top += 2 * g_GridSquareSize;
			loops++;
		}
	}
}

void AddPathPoint(float x, float y) {
	if (g_SpirPathSize == g_SpirPathCapacity) {
		g_SpirPathCapacity = g_SpirPathCapacity * 2;
		Point2f* newArr{ new Point2f[g_SpirPathCapacity]{} };
		for (int i{ 0 }; i < g_SpirPathCapacity; i++) {
			newArr[i] = g_SpirPath[i];
		}
		delete[] g_SpirPath;
		g_SpirPath = newArr;
	}
	g_SpirPath[g_SpirPathSize].x = x;
	g_SpirPath[g_SpirPathSize].y = y;
	g_SpirPathSize++;
}

void CreateSpiralPath(Rectf bounds) {
	float left{ bounds.left };
	float top{ 2 * bounds.top };
	float right{ bounds.width - bounds.top };
	float bottom{ bounds.height };
	float targetCordX{ bounds.width / g_CollumnAmount * 9 };
	float targetCordY{ bounds.height / g_RowAmount * 3 };
	bool targetHit{ false };
	while (left < right && top < bottom && targetHit == false)
	{
		for (float i{ left }; i < right; i += g_GridSquareSize) {
			AddPathPoint(i, top);
			if (i == targetCordX && top == targetCordY) {
				targetHit = true;
			}
		}

		top += g_GridSquareSize;
		for (float i{ top }; i < bottom; i += g_GridSquareSize) {
			AddPathPoint(right - g_GridSquareSize, i);
			if (i == targetCordX && top == targetCordY) {
				targetHit = true;
			}
		}

		right -= g_GridSquareSize;

		for (float i{ right - g_GridSquareSize }; i > left; i -= g_GridSquareSize) {
			AddPathPoint(i, bottom - g_GridSquareSize);
			if (i == targetCordX && top == targetCordY) {
				targetHit = true;
			}
			std::cout << i << ' ' << targetCordX << ' ' << top << ' ' << targetCordY << '\n';
		}
		bottom -= g_GridSquareSize;
		left += g_GridSquareSize;

		for (float i{ bottom - g_GridSquareSize }; i > top; i -= g_GridSquareSize) {
			AddPathPoint(left, i);
			if (i == targetCordX && top == targetCordY) {
				targetHit = true;
			}
		}
		top += g_GridSquareSize;
		for (float i{ left }; i < right - g_GridSquareSize; i += g_GridSquareSize) {
			if (i == left) {
				i += g_GridSquareSize;
			}
			AddPathPoint(i, top);

		}
	}
}

void EnemyCapacity() {
	if (g_EnemiesCount >= g_EnemiesCap) {
		int oldEnemiesCap{ g_EnemiesCap };
		if (g_EnemiesCap == 0) {
			g_EnemiesCap = 4;
		}
		else {
			g_EnemiesCap = g_EnemiesCap * 2;
		}
		EnemyInfo* newArr{ new EnemyInfo[g_EnemiesCap]{} };
		for (int i{ 0 }; i < g_EnemiesCap; i++) {
			newArr[i] = g_Enemies[i];
		}
		delete[] g_Enemies;
		g_Enemies = newArr;
	}
}

void SpawnEnemy() {
	EnemyCapacity();
	g_Enemies[g_EnemiesCount].pathPosition = 0;
	g_Enemies[g_EnemiesCount].parameters.left = g_SpirPath[0].x;
	g_Enemies[g_EnemiesCount].parameters.top = g_SpirPath[0].y;
	g_Enemies[g_EnemiesCount].movingCooldown = 0.f;
	g_EnemiesCount++;
	TakeDamage(g_HealthAmount, g_Enemies);
}

void EnemyMovement(float elapsedSec) {
	for (int i{ 0 }; i < g_EnemiesCount; i++) {
		g_Enemies[i].movingCooldown -= 1 * elapsedSec;
		if (g_Enemies[i].pathPosition < g_SpirPathSize && g_Enemies[i].movingCooldown <= 0) {
			g_Enemies[i].parameters.left = g_SpirPath[g_Enemies[i].pathPosition].x;
			g_Enemies[i].parameters.top = g_SpirPath[g_Enemies[i].pathPosition].y;
			g_Enemies[i].pathPosition++;
			g_Enemies[i].movingCooldown = g_MoveCooldown;
		}
	}
}

void DrawEnemies() {
	for (int i{ 0 }; i < g_EnemiesCount; i++) {
		g_Enemies[i].texture = g_Enemy;
		g_Enemies[i].parameters.width = g_GridSquareSize;
		g_Enemies[i].parameters.height = g_GridSquareSize;
		DrawTexture(g_Enemies[i].texture, g_Enemies[i].parameters);
	}
}

void AddPathTilesToIntersections(Point2f* arrPathTiles, const int pathTileAmount)
{
	for (int index{ 0 }; index < pathTileAmount; ++index)
	{
		g_arrIntersections[GetGridIndex(arrPathTiles[index].x, arrPathTiles[index].y)].isTaken = true;
	}
}

void AddConsumableParameters(ConsumableInfo* arrConsumables)
{
	for (int index{ 0 }; index < g_ConsumableAmount; ++index)
	{
		switch (static_cast<TextureNames>(index))
		{
		case TextureNames::Obama:
		{
			arrConsumables[index].radius = g_GridSquareSize;
			arrConsumables[index].shotCooldown = 1.f;
			break;
		}
		case TextureNames::Bomb:
		{
			arrConsumables[index].radius = g_GridSquareSize * 0.5f;
			arrConsumables[index].shotCooldown = 1.5f;
			break;
		}
		case TextureNames::Turret:
		{
			arrConsumables[index].radius = g_GridSquareSize * 2.f;
			arrConsumables[index].shotCooldown = 0.7f;
			break;
		}
		case TextureNames::Soldier:
		{
			arrConsumables[index].radius = g_GridSquareSize * 1.5f;
			arrConsumables[index].shotCooldown = 0.5f;
			break;
		}
		case TextureNames::Tank:
		{
			arrConsumables[index].radius = g_GridSquareSize;
			arrConsumables[index].shotCooldown = 2.f;
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void DrawHealthBar(const int healthAmount, const int maxHealth)
{
	Rectf healthBar{
		0.f,
		g_GridSquareSize * 0.1f,
		g_GridSquareSize * 3,
		g_GridSquareSize * 0.8f
	},
		health{
		healthBar.left,
		healthBar.top,
		healthBar.width / maxHealth * healthAmount,
		healthBar.height
	};

	if (healthAmount >= (maxHealth / 3 * 2))
	{
		utils::SetColor(g_Green);
	}
	else if (healthAmount >= (maxHealth * 0.5))
	{
		utils::SetColor(g_Yellow);
	}
	else if (healthAmount >= (maxHealth / 3))
	{
		utils::SetColor(g_Orange);
	}
	else
	{
		utils::SetColor(g_Red);
	}

	utils::FillRect(health);

	utils::SetColor(g_Black);
	utils::DrawRect(healthBar, 3.f);
}

void TakeDamage(int& healthAmount, EnemyInfo* arrEnemies)
{
	for (int index{ 0 }; index < g_EnemiesCount; ++index)
	{
		if (arrEnemies[index].pathPosition == 36 && g_EnemySpawnTime >= g_MoveCooldown)
		{
			--healthAmount;
		}
	}
}

void Shoot(EnemyInfo* arrEnemies, ConsumableInfo* arrTowers)
{
	for (int tower{ 0 }; tower < g_ConsumableAmount; ++tower)
	{
		for (int enemy{ 0 }; enemy < g_EnemiesCap; ++enemy)
		{
			//if(arrEnemies[enemy].parameters.)
		}
	}
}

bool IsEnemyInShootingRadius(const Rectf& enemyPosition, const Ellipsef& shootingRadius)
{
	
}
#pragma endregion ownDefinitions