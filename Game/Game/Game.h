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

struct ConsumableInfo {
	Rectf position;
	float shotCooldown;
	float radius;
	float timeUntilShot;
	int shotAmount;
};

float g_TimeFlow{0};

enum class TextureNames {
	Obama,
	Bomb,
	Turret,
	Soldier,
	Tank
};


float g_MoveCooldown{ 0.5f };

const int
g_PathTileAmount{ 36 },
g_CollumnAmount{ 13 },
g_RowAmount{ 7 },
g_ConsumableAmount{ 5 },
g_GridAmount{ g_CollumnAmount * g_RowAmount },
g_MaxHealthAmount{ 20 };

const float
g_GameWindowWidth{ g_WindowWidth / 16.f * 13.f },
g_GameWindowHeight{ g_WindowHeight / 9.f * 7.f },
g_GridSquareSize{ 80.f };

bool
g_IsGameLost{ false };

Texture
g_Obama,
g_Castle,
g_Bomb,
g_Turret,
g_Tank,
g_Soldier,
g_Road,
g_Grass,
g_Enemy;


const Rectf
g_GridPosition{
	0.f,
	g_GridSquareSize,
	g_GridSquareSize * g_CollumnAmount,
	g_GridSquareSize * g_RowAmount
},
g_GridBlockSize{
	0.f,
	0.f,
	g_GridSquareSize,
	g_GridSquareSize
},
g_EnemySpawnLocation{
	0.f,
	g_GridSquareSize * 2,
	g_GridBlockSize.width,
	g_GridBlockSize.height
};

struct EnemyInfo {
	Texture texture{ g_Enemy };
	int pathPosition{0};
	Rectf parameters{ 0.f,
	g_GridSquareSize * 2,
	g_GridBlockSize.width,
	g_GridBlockSize.height };
	float movingCooldown{ 0.f };
};

struct Grid
{
	Point2f originLocation{ Point2f{0.f, 0.f} };
	bool isTaken{ false };
};

const Color4f 
g_White{
	1.f, 1.f, 1.f, 1.f
}, g_Green{
	0.f, 1.f, 0.f, 1.f
},
g_Black{
	0.f,
	0.f,
	0.f,
	1.f
},
g_Red{
	1.f,
	0.f,
	0.f,
	1.f
},
g_Yellow{
	1.f,
	1.f,
	0.f,
	1.f
},
g_Orange{
	1.f,
	0.647f,
	0.f,
	1.f
};

int 
g_SelectedConsumableIndex{ -1 },
g_HealthAmount{ 20 };

int g_SpirPathSize{ 0 };
int g_SpirPathCapacity{ 0 };
Point2f* g_SpirPath{ nullptr };

Texture g_ConsumablesTextures[g_ConsumableAmount]{};
int g_EnemyAmount{ 0 };
EnemyInfo* g_Enemies{ nullptr };
int g_EnemiesCount{ 0 };
int g_EnemiesCap{ 0 };

Point2f
g_ShootTowardsCoordinate{ 0.f, 0.f },
g_MousePosition{ 0.f, 0.f },
g_InitialConsumableLocation{ 0.f, 0.f };

Grid
g_arrIntersections[g_GridAmount];

ConsumableInfo
g_arrConsumables[g_ConsumableAmount]{
	Rectf{
		0.f,
		0.f,
		0.f,
		0.f
	}
};

float g_EnemySpawnTime{ 0.f };
float g_Tst{ 0 };


// Declare your own functions here
void InitializeTextures();
void InitializeGridPositions();
void CheckGridPositions();
void DrawGrid();
void DrawItems(ConsumableInfo itemPos[], Texture texture[]);
void DeleteTextures();
void ClickConsumableToGrid(Rectf& consumable);
void InitializeConsumablePositions();
int FindConsumable();
bool IsMouseOutOfBounds();
bool IsMouseOutOfGrid();
int GetGridIndex(const Point2f& location);
int GetGridIndex(const float left, const float top);
void DrawRoadAndGrass(Rectf coord);
void AddPathPoint(float x, float y);
void CreateSpiralPath(Rectf bounds);
void EnemyCapacity();
void SpawnEnemy();
void EnemyMovement(float elapsedSec);
void DrawEnemies();
void MoveConsumable(Rectf& consumable);
void PutConsumableBack(const int index);
void PlaceConsumableOnGrid(Rectf& consumable, Grid& intersection);
void SelectConsumable();
void AddPathTilesToIntersections(Point2f* arrPathTiles, const int pathTileAmount);
void AddConsumableParameters(ConsumableInfo* arrConsumables);
void DrawHealthBar(const int healthAmount, const int maxHealth);
void TakeDamage(int& healthAmount, EnemyInfo* arrEnemies);
bool Shoot(EnemyInfo* arrEnemies, const ConsumableInfo & tower,
	int& enemyIndex);
Point2f IsEnemyInShootingRadius(const Rectf& enemyPosition,
	const Point2f& shootingRadiusCenter, const float radius, bool& shouldTowerShoot);



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
