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

	audioSlider = new Slider(Vector2(125, 200));
	addchild(audioSlider);
}

optionsMenu::~optionsMenu()
{
	std::vector<Button*>::iterator it = buttonVector.begin();
	while (it != buttonVector.end()) {
		Button* u = (*it);
		it = buttonVector.erase(it);
		this->removechild(u);
	}
	buttonVector.clear();

	delete audioSlider;
	audioSlider = NULL;
}

void optionsMenu::update(double deltatime)
{
	Scene::update(deltatime);
	std::cout << Audio::getInstance()->volume << " " << audioSlider->audioMuted << std::endl;

	buttonClickCheck();
}

void optionsMenu::buttonClickCheck()
{
	if (backButton->isClicked()) {
		SceneManager::getInstance()->setCurrentScene(SceneManager::getInstance()->sceneVector["OptionsScene"]->lastScene);
	}

	if (muteButton->isClicked()) {
		if (muteClicked) {
			audioSlider->audioMuted = false;
			Audio::getInstance()->volumeAudio(128);
			muteClicked = false;
			return;
		}
		audioSlider->audioMuted = true;
		Audio::getInstance()->volumeAudio(0);
		muteClicked = true;
	}
}
