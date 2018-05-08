#include <renderer.h>
#include <texture.h>
#include <SDL2\SDL.h>
#include <input.h>
#include "MyScene.h"
#include "MenuScene.h"
#include "optionsMenu.h"

#include "../MXP3/include/entity.h"
#include <sceneManager.h>

Input* Input::instance = NULL;

#undef main
int main(int argc, char *argv[])
{
	int curscene = 0;

	Audio::getInstance();

	//the first scene that gets added is the startup scene.
	SceneManager::getInstance()->addScene("MenuScene", new MenuScene());

	//options menu scene initiation
	SceneManager::getInstance()->addScene("OptionsScene", new optionsMenu());

	//game scene
	SceneManager::getInstance()->addScene("MyScene", new MyScene());

	//set start scene
	SceneManager::getInstance()->setCurrentScene("MenuScene");

	while (!Input::getInstance()->getMustQuit())
	{
		Input::getInstance()->update();
		SceneManager::getInstance()->currentScene->update(Renderer::getInstance()->getDeltatime());
		Renderer::getInstance()->renderScene(SceneManager::getInstance()->currentScene);
		
		//a way to switch scenes. still need to do this better
		/*
		if (Input::getInstance()->getKeyDown(SDLK_RIGHTBRACKET))
		{
			curscene++;
		}
		else if (Input::getInstance()->getKeyDown(SDLK_LEFTBRACKET))
		{
			curscene--;
		}

		else if (curscene == 0 && SceneManager::getInstance()->currentScene != SceneManager::getInstance()->getScene("MenuScene")) {
			SceneManager::getInstance()->setCurrentScene("MenuScene");
		}

		else if (curscene == 1 && SceneManager::getInstance()->currentScene != SceneManager::getInstance()->getScene("MyScene")) {
			SceneManager::getInstance()->setCurrentScene("MyScene");
		}
		*/
		Renderer::getInstance()->update();
	}
	return 0;
}
