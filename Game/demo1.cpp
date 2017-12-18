#include "demo1.h"

Demo1::Demo1() : Scene()
{
	std::cout << "===DEMO1===" << std::endl;
	//default value 
	texturePath = "";

	//background needs to be divined up top
	background = new Grid();
	addchild(background);
	background->pos = Vector2(0, 0);
	background->tileTexture = "assets/cobblestone.png";

	spawnEnemy(Vector2(600, 600));
	spawnEnemy(Vector2(500, 500));



	//spawns hearts that resemble your health
	hearts = new Entity();
	hearts->pos = Vector2(100, 100);
	hearts->size = Vector2(100, 400);
	hearts->spitesheetPath = "assets/hearts.png";
	hearts->animator.rows = Vector2(4, 1);
	hearts->animator.paused = true;
	hearts->animator.cur = 0;
	addchild(hearts);

	finishDoor = new Entity();
	finishDoor->texturePath = "assets/INA.png";
	finishDoor->size = Vector2(50, 100);
	finishDoor->pos = Vector2(-200, -200);
	addchild(finishDoor);

	spawnWalls();

	enemyHitTimer = 0;
	enemyHitTimerCheck = false;
	hitAfter = 2.0f;

	
	
}

Demo1::~Demo1()
{
	



}

void Demo1::update(double deltatime)
{
	Scene::update(deltatime);


}

void Demo1::audioController()
{
	
}

void Demo1::hitEnemy()
{
	
}

void Demo1::enemyDie()
{
	
}

void Demo1::AI(double deltatime)
{
	
}


void Demo1::spawnEnemy(Vector2 position)
{
	
}

void Demo1::heartController()
{
	
}

void Demo1::goToNextLevel()
{
	if (enemiesAlive <= 0) {
		finishDoor->pos = Vector2(800, 200);
		
	}
}

void Demo1::spawnWalls()
{
		wallLeft = new Entity();
		wallRight = new Entity();
		wallTop = new Entity();
		wallDown = new Entity();

		wallLeft->size = Vector2(2, 800);
		wallRight->size = Vector2(2, 800);
		wallTop->size = Vector2(800, 2);
		wallDown->size = Vector2(800, 2);

		wallLeft->pos = Vector2(180, 400);
		wallRight->pos = Vector2(975, 400);
		wallTop->pos = Vector2(600, -20);
		wallDown->pos = Vector2(600, 775);

		addchild(wallLeft);
		addchild(wallRight);
		addchild(wallTop);
		addchild(wallDown);

		wallVector.push_back(wallLeft);
		wallVector.push_back(wallRight);
		wallVector.push_back(wallTop);
		wallVector.push_back(wallDown);
}

void Demo1::wallCollisionCheck()
{
	
}
