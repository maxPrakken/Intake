#include "OptionsMenu.h"

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

	generalAudioSlider = new Slider(Vector2(125, 200), -1);
	addchild(generalAudioSlider);

	playerAudioSlider = new Slider(Vector2(125, 350), 1);
	addchild(playerAudioSlider);

	enemyAudioSlider = new Slider(Vector2(125, 500), 2);
	addchild(enemyAudioSlider);

	calcTextPosition();
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

	delete generalAudioSlider;
	generalAudioSlider = NULL;

	delete playerAudioSlider;
	playerAudioSlider = NULL;

	delete enemyAudioSlider;
	enemyAudioSlider = NULL;
}

void optionsMenu::update(double deltatime)
{
	Scene::update(deltatime);

	buttonClickCheck();
	displayText();
}

void optionsMenu::buttonClickCheck()
{
	if (backButton->isClicked()) {
		SceneManager::getInstance()->setCurrentScene(SceneManager::getInstance()->sceneVector["OptionsScene"]->lastScene);
	}

	if (muteButton->isClicked()) {
		if (muteClicked) {
			generalAudioSlider->audioMuted = false;
			playerAudioSlider->audioMuted = false;
			enemyAudioSlider->audioMuted = false;

			Audio::getInstance()->volumeAudio(128);
			muteClicked = false;
			return;
		}
		generalAudioSlider->audioMuted = true;
		playerAudioSlider->audioMuted = true;
		enemyAudioSlider->audioMuted = true;
		Audio::getInstance()->volumeAudio(0);
		muteClicked = true;
	}
}

void optionsMenu::displayText()
{
	Renderer::getInstance()->RenderText(generalText, c, &generalRect);
	Renderer::getInstance()->RenderText(playerText, c, &playerRect);
	Renderer::getInstance()->RenderText(enemyText, c, &enemyRect);
}

void optionsMenu::calcTextPosition()
{
	generalRect.w = (100 * (MathM::getInstance()->getDigits(generalText.length())));
	generalRect.x = ((Renderer::getInstance()->getResolution().x / 2) - (generalRect.w / 2));
	generalRect.y = generalAudioSlider->getSliderBodyPosition().y - 50;

	playerRect.w = (100 * (MathM::getInstance()->getDigits(playerText.length())));
	playerRect.x = ((Renderer::getInstance()->getResolution().x / 2) - (playerRect.w / 2));
	playerRect.y = playerAudioSlider->getSliderBodyPosition().y - 50;

	enemyRect.w = (100 * (MathM::getInstance()->getDigits(enemyText.length())));
	enemyRect.x = ((Renderer::getInstance()->getResolution().x / 2) - (enemyRect.w / 2));
	enemyRect.y = enemyAudioSlider->getSliderBodyPosition().y - 50;
}
