#include "grid.h"

Grid::Grid() : Entity()
{
	grid = Vector2(2, 2);
	spawnPos = Vector2(0, 0);
	startX = spawnPos.x;

	size = Vector2(0, 0);

	firstTile = true;

	tileTexture = "assets/INA.png";

	buildgrid();
}

Grid::Grid(Vector2 gridSize, std::string tiletexture)
{
	grid = gridSize;
	spawnPos = Vector2(0, 0);
	pos = spawnPos;
	startX = spawnPos.x;

	firstTile = true;

	tileTexture = tiletexture;

	buildgrid();
}

Grid::Grid(Vector2 gridSize, Vector2 tilesize)
{
	grid = gridSize;
	spawnPos2 = Vector2(0, 0);
	pos = spawnPos2;
	startX2 = spawnPos2.x;

	firstTile = true;

	tileTexture = "assets/INA.png";

	buildgrid(tilesize);
}

Grid::Grid(Vector2 gridSize, std::string tiletexture, Vector2 tilesize, bool isRandom, Vector2 rowAmound)
{
	grid = gridSize;
	spawnPos2 = Vector2(0, 0);
	pos = spawnPos2;
	startX2 = spawnPos2.x;

	firstTile = true;

	tileTexture = tiletexture;

	if (!isRandom)
		buildgrid(tilesize);
	else
		buildgrid(tilesize, isRandom, rowAmound);
}

Grid::~Grid()
{
	for (unsigned int i = 0; i < tileVector.size(); i++) {
		removechild(tileVector[i]);
		delete tileVector[i];
	}
	tileVector.clear();
}

void Grid::update(double deltatime)
{
	Entity::update(deltatime);
}

void Grid::buildgrid()
{
	for (int i = 0; i < grid.x * grid.y; i++) {
		spawnTile();
	}
}

void Grid::buildgrid(Vector2 tilesize, bool isRandom, Vector2 rows)
{
	for (int i = 0; i < grid.x * grid.y; i++) {
		if (!isRandom)
			spawnTile(tilesize);
		else
			spawnTile(tilesize, isRandom, rows);
	}
}

void Grid::spawnTile()
{
	Entity* tile = new Entity();
	tile->texturePath = tileTexture;
	tile->size = Vector2(100, 100);
	addchild(tile);
	tileVector.push_back(tile);
	tile->pos = spawnPos;

	if (spawnPos.x <= grid.x * tile->size.x) {
		spawnPos += Vector2(tile->size.x, 0);
	}
	else if(spawnPos.x > grid.x * tile->size.x) {
		spawnPos.x = startX;
		spawnPos.y += tile->size.y;
	}

	size = Vector2(grid.x * tile->size.x, grid.y * tile->size.y);
}

void Grid::spawnTile(Vector2 tilesize, bool isRandom, Vector2 rows)
{
	Entity* tile = new Entity();
	if (isRandom && rows.x > 0)
	{
		int tilesAmount = rows.x * rows.y;
		
		int randomInt = rand() % tilesAmount;
		tile->spitesheetPath = tileTexture;
		tile->animator.rows = rows;
		tile->animator.paused = true;
		tile->animator.switchAfter = 1;
		tile->animator.cur = randomInt;
	}
	else
	{
		tile->texturePath = tileTexture;
	}
	tile->size = tilesize;
	addchild(tile);
	tileVector.push_back(tile);

	if (spawnPos2.x < grid.x * tile->size.x) {
		spawnPos2 += Vector2(tile->size.x, 0);
	}

	tile->pos = spawnPos2;

	if (spawnPos2.x >= grid.x * tile->size.x) {
		spawnPos2.x = startX2;
		spawnPos2.y += tile->size.y;
	}
	size = Vector2(grid.x * tile->size.x, grid.y * tile->size.y);
}
