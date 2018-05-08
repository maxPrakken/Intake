#include "optionsMenu.h"

optionsMenu::optionsMenu()
{
	backButton = new Button();
	backButton->pos = Vector2(200, 50);
	backButton->size = Vector2(200, 50);
	backButton->texturePath = "assets/buttons/backButton.png";
	buttonVector.push_back(backButton);
	addchild(backButton);

	muteButton = new Button();
	muteButton->pos = Vector2(500, 500);
	muteButton->size = Vector2(100, 100);
	muteButton->texturePath = "assets/buttons/muteButton.png";
	buttonVector.push_back(muteButton);
	addchild(muteButton);
}

optionsMenu::~optionsMenu()
{
}

void optionsMenu::update(double deltatime)
{
	Scene::update(deltatime);

	buttonClickCheck();
}

void optionsMenu::buttonClickCheck()
{
	if (backButton->isClicked()) {
		SceneManager::getInstance()->setCurrentScene(SceneManager::getInstance()->sceneVector["OptionsScene"]->lastScene);
	}

	if (muteButton->isClicked()) {
		if (muteClicked) {
			Audio::getInstance()->volumeAudio(128);
			muteClicked = false;
			return;
		}
		Audio::getInstance()->volumeAudio(0);
		muteClicked = true;
	}
}
