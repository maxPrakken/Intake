#include "MenuScene.h"

MenuScene::MenuScene()
{
	playButton = new Button();
	playButton->pos = Vector2(200, 50);
	playButton->size = Vector2(200, 50);
	playButton->texturePath = "assets/INA.png";
	buttonVector.push_back(playButton);
	addchild(playButton);

	optionsButton = new Button();
	optionsButton->pos = Vector2(200, 150);
	optionsButton->size = Vector2(200, 50);
	optionsButton->texturePath = "assets/INA.png";
	buttonVector.push_back(optionsButton);
	addchild(optionsButton);

	highscoresButton = new Button();
	highscoresButton->pos = Vector2(200, 250);
	highscoresButton->size = Vector2(200, 50);
	highscoresButton->texturePath = "assets/INA.png";
	buttonVector.push_back(highscoresButton);
	addchild(highscoresButton);

	quitButton = new Button();
	quitButton->pos = Vector2(200, 350);
	quitButton->size = Vector2(200, 50);
	quitButton->texturePath = "assets/INA.png";
	buttonVector.push_back(quitButton);
	addchild(quitButton);

	player = new Player();
	addchild(player);
}

MenuScene::~MenuScene()
{
	for (unsigned int i = 0; i < buttonVector.size(); i++) {
		removechild(buttonVector[i]);
		delete buttonVector[i];
	}
	buttonVector.clear();

	delete player;
}

void MenuScene::update(double deltatime)
{
	Scene::update(deltatime);

	if (player->hasShot) {
		playerShoot();
	}

	buttonClickCheck();
}

void MenuScene::buttonClickCheck()
{
	if (playButton->isClicked())
	{
		SceneManager::getInstance()->setCurrentScene("MyScene");
	}

	if (quitButton->isClicked()) {
		Input::getInstance()->setMustQuit(true);
	}
}

void MenuScene::playerShoot()
{
	Bullet* bullet = new Bullet();
	bullet->pos = player->pos;
	bullet->pos.y = player->pos.y - player->size.y / 2 + 30;

	Bullet* bullet2 = new Bullet();
	bullet2->pos = player->pos;
	bullet2->pos.y = player->pos.y - player->size.y / 2 + 30;
	bullet2->pos.x = player->pos.x + player->size.x - 12;

	bullet->direction = Vector2(0, player->getBulletSpeed());
	bullet->rot = 90;

	bullet2->direction = Vector2(0, -10);
	bullet2->rot = 90;

	bulletVector.push_back(bullet);
	bulletVector.push_back(bullet2);

	addchild(bullet);
	addchild(bullet2);

	if (player->doubleShot) {
		Bullet* bullet3 = new Bullet();
		bullet3->pos = player->pos;
		bullet3->pos.x = player->pos.x + 10;
		bullet3->pos.y = player->pos.y - player->size.y / 2 + 30;

		Bullet* bullet4 = new Bullet();
		bullet4->pos = player->pos;
		bullet4->pos.y = player->pos.y - player->size.y / 2 + 30;
		bullet4->pos.x = player->pos.x + player->size.x - 22;

		bullet3->direction = Vector2(0, player->getBulletSpeed());
		bullet3->rot = 90;

		bullet4->direction = Vector2(0, -10);
		bullet4->rot = 90;

		bulletVector.push_back(bullet3);
		bulletVector.push_back(bullet4);

		addchild(bullet3);
		addchild(bullet4);
	}

	player->hasShot = false;
}
