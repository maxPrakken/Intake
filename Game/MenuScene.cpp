#include "MenuScene.h"

MenuScene::MenuScene()
{
	playButton = new Button();
	playButton->pos = Vector2(200, 50);
	playButton->size = Vector2(200, 50);
	playButton->texturePath = "assets/buttons/playButton.png";
	buttonVector.push_back(playButton);
	addchild(playButton);

	optionsButton = new Button();
	optionsButton->pos = Vector2(200, 150);
	optionsButton->size = Vector2(200, 50);
	optionsButton->texturePath = "assets/buttons/optionsButton.png";
	buttonVector.push_back(optionsButton);
	addchild(optionsButton);

	highscoresButton = new Button();
	highscoresButton->pos = Vector2(200, 250);
	highscoresButton->size = Vector2(200, 50);
	highscoresButton->texturePath = "assets/buttons/highscoresButton.png";
	buttonVector.push_back(highscoresButton);
	addchild(highscoresButton);

	quitButton = new Button();
	quitButton->pos = Vector2(200, 350);
	quitButton->size = Vector2(200, 50);
	quitButton->texturePath = "assets/buttons/quitButton.png";
	buttonVector.push_back(quitButton);
	addchild(quitButton);

	player = new Player();
	addchild(player);
}

MenuScene::MenuScene(int ZLayer_amount)
{
	addZLayers(ZLayer_amount);

	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v7.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	playButton = new Button();
	playButton->pos = Vector2(200, 50);
	playButton->size = Vector2(200, 50);
	playButton->texturePath = "assets/buttons/playButton.png";
	playButton->setZLayer(2);
	buttonVector.push_back(playButton);
	addchild(playButton);

	optionsButton = new Button();
	optionsButton->pos = Vector2(200, 150);
	optionsButton->size = Vector2(200, 50);
	optionsButton->texturePath = "assets/buttons/optionsButton.png";
	optionsButton->setZLayer(2);
	buttonVector.push_back(optionsButton);
	addchild(optionsButton);

	highscoresButton = new Button();
	highscoresButton->pos = Vector2(200, 250);
	highscoresButton->size = Vector2(200, 50);
	highscoresButton->texturePath = "assets/buttons/highscoresButton.png";
	highscoresButton->setZLayer(2);
	buttonVector.push_back(highscoresButton);
	addchild(highscoresButton);

	quitButton = new Button();
	quitButton->pos = Vector2(200, 350);
	quitButton->size = Vector2(200, 50);
	quitButton->texturePath = "assets/buttons/quitButton.png";
	quitButton->setZLayer(2);
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
		MyScene* scene = (MyScene*)SceneManager::getInstance()->currentScene;
		scene->resetWorld();
	}

	if (optionsButton->isClicked()) {
		SceneManager::getInstance()->setCurrentScene("OptionsScene");
		SceneManager::getInstance()->sceneVector["OptionsScene"]->lastScene = "MenuScene";
	}

	if (highscoresButton->isClicked()) {
		SceneManager::getInstance()->setCurrentScene("HighScoreScene");
		SceneManager::getInstance()->sceneVector["HighScoreScene"]->lastScene = "MenuScene";
		HighScoreMenu* scene = dynamic_cast<HighScoreMenu*> (SceneManager::getInstance()->sceneVector["HighScoreScene"]);
		if (scene != NULL) {
			scene->refresh();
		}
	}

	if (quitButton->isClicked()) {
		Input::getInstance()->setMustQuit(true);
	}
}

void MenuScene::playerShoot()
{
	Bullet* bullet = new Bullet();
	bullet->setOrigin(player);
	bullet->pos = player->pos;
	bullet->pos.y = player->pos.y - player->size.y / 2 + 30;

	Bullet* bullet2 = new Bullet();
	bullet2->setOrigin(player);
	bullet2->pos = player->pos;
	bullet2->pos.y = player->pos.y - player->size.y / 2 + 40;
	bullet2->pos.x = player->pos.x + player->size.x - 12;

	bullet->direction = Vector2(0, player->getBulletSpeed());

	bullet2->direction = Vector2(0, player->getBulletSpeed());

	bulletVector.push_back(bullet);
	bulletVector.push_back(bullet2);

	addchild(bullet);
	addchild(bullet2);

	if (player->doubleShot) {
		Bullet* bullet3 = new Bullet();
		bullet3->setOrigin(player);
		bullet3->pos = player->pos;
		bullet3->pos.x = player->pos.x + 10;
		bullet3->pos.y = player->pos.y - player->size.y / 2 + 31;

		Bullet* bullet4 = new Bullet();
		bullet4->setOrigin(player);
		bullet4->pos = player->pos;
		bullet4->pos.y = player->pos.y - player->size.y / 2 + 34;
		bullet4->pos.x = player->pos.x + player->size.x - 22;

		bullet3->direction = Vector2(0, player->getBulletSpeed());

		bullet4->direction = Vector2(0, player->getBulletSpeed());

		bulletVector.push_back(bullet3);
		bulletVector.push_back(bullet4);

		addchild(bullet3);
		addchild(bullet4);
	}

	player->hasShot = false;
}

void MenuScene::addZLayers(int zlayerAmount)
{
	setZLayer(zlayerAmount);

	for (int i = 0; i <= getZlayer() - 1; i++) {
		std::vector<Entity*>zlayer;
		ZLayers.push_back(zlayer);
	}
}
