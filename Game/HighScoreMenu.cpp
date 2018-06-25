#include "HighScoreMenu.h"

HighScoreMenu::HighScoreMenu()
{
	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v7.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	backbutton = new Button();
	backbutton->size = Vector2(200, 50);
	backbutton->pos = Vector2((Renderer::getInstance()->getResolution().x / 2) - (backbutton->size.x / 2), 600); //set x in perfect middle
	backbutton->texturePath = "assets/buttons/backButton.png";
	addchild(backbutton);

	rectVector.push_back(score5);
	rectVector.push_back(score4);
	rectVector.push_back(score3);
	rectVector.push_back(score2);
	rectVector.push_back(score1);
}

HighScoreMenu::~HighScoreMenu()
{
	delete backbutton;
	backbutton = NULL;
}

void HighScoreMenu::update(double deltatime)
{
	Scene::update(deltatime);

	if (backbutton->isClicked()) {
		SceneManager::getInstance()->setCurrentScene(SceneManager::getInstance()->sceneVector["HighScoreScene"]->lastScene);
	}

	displayHighScores();
}

void HighScoreMenu::getHighScores()
{
	std::string line;
	std::ifstream myfile;
	myfile.open("save_files/highscores.txt", std::ios::app);

	if (myfile.is_open()) {
		if (myfile.peek() != std::ifstream::traits_type::eof()) { //checks if file is empty
			while (std::getline(myfile, line)) {
				int i = std::atoi(line.c_str());
				highscoreVector.push_back(i);
			}
		}
		while (highscoreVector.size() != 5) {
			highscoreVector.push_back(42);
		}
		myfile.close();
	}
}

void HighScoreMenu::orderHighScores()
{
	if (highscoreVector.size() != 0) {
		std::sort(highscoreVector.begin(), highscoreVector.end());
	}
}

void HighScoreMenu::manageScoresRect()
{
	for(int i = 0; i < highscoreVector.size(); i++) {
		rectVector[i].w = (50 * (MathM::getInstance()->getDigits(highscoreVector[i])));
		rectVector[i].x = ((Renderer::getInstance()->getResolution().x / 2 ) - (rectVector[i].w / 2));
		rectVector[i].y = (450 - (100 * i));
	}
}

void HighScoreMenu::displayHighScores()
{
	Renderer::getInstance()->RenderText("1: " + std::to_string(highscoreVector[4]), c, &rectVector[4]);
	Renderer::getInstance()->RenderText("2: " + std::to_string(highscoreVector[3]), c, &rectVector[3]);
	Renderer::getInstance()->RenderText("3: " + std::to_string(highscoreVector[2]), c, &rectVector[2]);
	Renderer::getInstance()->RenderText("4: " + std::to_string(highscoreVector[1]), c, &rectVector[1]);
	Renderer::getInstance()->RenderText("5: " + std::to_string(highscoreVector[0]), c, &rectVector[0]);
}
