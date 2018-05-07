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
}

MenuScene::~MenuScene()
{
	for (unsigned int i = 0; i < buttonVector.size(); i++) {
		removechild(buttonVector[i]);
		delete buttonVector[i];
	}
	buttonVector.clear();

}

void MenuScene::update(double deltatime)
{
	Scene::update(deltatime);

	if (playButton->isClicked())
	{
		SceneManager::getInstance()->setCurrentScene("MyScene");
	}
}
