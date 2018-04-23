#pragma once

#include "../MXP3/include/entity.h"

class Grid : public Entity {
public:
	Grid();
	Grid(Vector2 gridSize, std::string tiletexture);
	Grid(Vector2 gridSize, Vector2 tilesize);
	Grid(Vector2 gridSize, std::string tiletexture, Vector2 tilesize, bool isRandom = false, Vector2 rowAmound = Vector2(-1, -1));
	virtual ~Grid();
	virtual void update(double deltatime);

	std::vector<Entity*> getTileVector() {return tileVector;}

	std::string tileTexture;

	Vector2 grid;
	Vector2 spawnPos;
	Vector2 spawnPos2;

	std::vector<Entity*>tileVector;

private:
	void buildgrid();
	void buildgrid(Vector2 tilesize, bool isRandom = false, Vector2 rows = Vector2(-1, -1));
	void spawnTile();
	void spawnTile(Vector2 tilesize, bool isRandom = false, Vector2 rows = Vector2(-1, -1));

	int startX;
	int startX2;

	bool firstTile;
};