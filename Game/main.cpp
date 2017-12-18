#include <renderer.h>
#include <texture.h>
#include <SDL2\SDL.h>
#include <input.h>
#include "NHTVScene.h"

#include "../MXP3/include/entity.h"
#include <sceneManager.h>

Input* Input::instance = NULL;

#undef main
int main(int argc, char *argv[])
{
	int curscene = 0;

	Audio::getInstance();

	//the first scene that gets added is the startup scene.
	SceneManager::getInstance()->addScene("NHTVScene", new NHTVScene());

	while (!Input::getInstance()->getMustQuit())
	{
		Input::getInstance()->update();
		SceneManager::getInstance()->currentScene->update(Renderer::getInstance()->getDeltatime());
		Renderer::getInstance()->renderScene(SceneManager::getInstance()->currentScene);
		
		//a way to switch scenes. still need to do this better

		if (Input::getInstance()->getKeyDown(SDLK_RIGHTBRACKET))
		{
			curscene++;
		}
		else if (Input::getInstance()->getKeyDown(SDLK_LEFTBRACKET))
		{
			curscene--;
		}

		if (curscene == 0 && SceneManager::getInstance()->currentScene != SceneManager::getInstance()->getScene("NHTVScene")) {
			SceneManager::getInstance()->setCurrentScene("NHTVScene");
		}

		Renderer::getInstance()->update();
	}
	return 0;
}
