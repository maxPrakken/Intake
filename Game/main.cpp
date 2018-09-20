#include <renderer.h>
#include <texture.h>
#include <SDL2\SDL.h>
#include <input.h>
#include "MyScene.h"
#include "MenuScene.h"
#include "optionsMenu.h"
#include "highscoreMenu.h"
#include "storeScene.h"

#include <sceneManager.h>

Input* Input::instance = NULL;

#undef main
int main(int argc, char *argv[])
{
	int curscene = 0;

	Audio::getInstance();

	//the first scene that gets added is the startup scene.
	SceneManager::getInstance()->addScene("MenuScene", new MenuScene(2));

	//store scene initiation
	SceneManager::getInstance()->addScene("StoreScene", new StoreScene(3));

	//options menu scene initiation
	SceneManager::getInstance()->addScene("OptionsScene", new optionsMenu());

	//highscore menu scene initiation
	SceneManager::getInstance()->addScene("HighScoreScene", new HighScoreMenu());

	//game scene
	SceneManager::getInstance()->addScene("MyScene", new MyScene(2));

	//set start scene
	SceneManager::getInstance()->setCurrentScene("MenuScene");

	while (!Input::getInstance()->getMustQuit())
	{
		Input::getInstance()->update();
		SceneManager::getInstance()->currentScene->update(Renderer::getInstance()->getDeltatime());
		Renderer::getInstance()->renderScene(SceneManager::getInstance()->currentScene);
		
		Renderer::getInstance()->update();
	}
	return 0;
}
