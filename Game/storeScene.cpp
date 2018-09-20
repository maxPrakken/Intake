#include "storeScene.h"

StoreScene::StoreScene() {
}

StoreScene::StoreScene(int ZLayer_amount) {
	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v7.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	backbutton = new Button();
	backbutton->size = Vector2(200, 50);
	backbutton->pos = Vector2((Renderer::getInstance()->getResolution().x / 2) - (backbutton->size.x / 2), 600); //set x in perfect middle
	backbutton->texturePath = "assets/buttons/backButton.png";
	addchild(backbutton);

	totalSpaceBucks = getSBAmount();
}

StoreScene::~StoreScene() {
	delete background;
	background = NULL;

	delete backbutton;
	backbutton = NULL;
}

void StoreScene::update(double deltatime) {
	Scene::update(deltatime);

	if (backbutton->isClicked()) {
		saveSB();
		SceneManager::getInstance()->setCurrentScene(SceneManager::getInstance()->sceneVector["StoreScene"]->lastScene);
	}

	displayText();
}

int StoreScene::getSBAmount() {
	std::string line;
	std::ifstream myfile;
	myfile.open("save_files/SB.txt", std::ios::app);
	if (myfile.is_open()) {
		if (myfile.peek() != std::ifstream::traits_type::eof()) { //checks if file is empty
			myfile >> line; //grabes the first and only line and puts in string line
			return std::stoi(line);
		}
		else {
			return 0;
		}
		myfile.close();
	}
	else {
		return 0;
	}
}

void StoreScene::displayText() {
	Score_rect.w = (20 * (MathM::getInstance()->getDigits(totalSpaceBucks) + 1));
	Score_rect.x = (Renderer::getInstance()->getResolution().x - (20 * (MathM::getInstance()->getDigits(totalSpaceBucks) + 1)));

	Renderer::getInstance()->RenderText(std::to_string(totalSpaceBucks), c, &Score_rect);
}

void StoreScene::saveSB() {
	std::ofstream file;
	file.open("save_files/SB.txt", std::ofstream::out | std::ofstream::trunc); //empty the whole file
	file.close();
	file.open("save_files/SB.txt", std::ios::app);

	file << std::to_string(totalSpaceBucks);

	file.close();
}


