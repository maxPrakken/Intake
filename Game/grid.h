#pragma once

#include "../MXP3/include/entity.h"

class Grid : public Entity {
public:
	//default constructor
	Grid();
	//constructor with gridsize for amount of tiles and tiletexure for the textures of the tiles.
	Grid(Vector2 gridSize, std::string tiletexture);
	//constructor with gridsize for amount of tiles and the size of the tiles
	Grid(Vector2 gridSize, Vector2 tilesize);
	//constructor with gridsize for amount of tiles, tiletexure for the textures of the tiles, the size of the tiles, 
	//if it applies a random texure fom the tiletexure spritesheet, and a rowamount variable.
	Grid(Vector2 gridSize, std::string tiletexture, Vector2 tilesize, bool isRandom = false, Vector2 rowAmound = Vector2(-1, -1));
	//deconstructor
	virtual ~Grid();
	//update function which takes deltatime double variable
	virtual void update(double deltatime);

	//gets the vector with tiles
	std::vector<Entity*> getTileVector() {return tileVector;}

	//path to the texture for the tiles
	std::string tileTexture;

	//grid size
	Vector2 grid;
	//spawn position of the grid
	Vector2 spawnPos;
	//spawn position 2 of the grid
	Vector2 spawnPos2;

	//the tilevector with tiles
	std::vector<Entity*>tileVector;

private:
	//function buildGrid that makes a default grid
	void buildgrid();
	//function buildGrid that makes them in custom tilesize, random texure, and self assigned rows
	void buildgrid(Vector2 tilesize, bool isRandom = false, Vector2 rows = Vector2(-1, -1));
	//spawns tile of default values
	void spawnTile();
	//spawns tile on custom: size, texture, row.
	void spawnTile(Vector2 tilesize, bool isRandom = false, Vector2 rows = Vector2(-1, -1));

	//start position x and x2
	int startX;
	int startX2;

	//checks if the tile being spawned is the first tile
	bool firstTile;
};