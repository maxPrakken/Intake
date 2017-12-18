#include <renderer.h>
#include <texture.h>
#include <SDL2\SDL.h>
#include <input.h>
#include "demo1.h"
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
	SceneManager::getInstance()->addScene("FirstDemo", new Demo1());

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
		else if (curscene == 1 && SceneManager::getInstance()->currentScene != SceneManager::getInstance()->getScene("FirstDemo")) {
			SceneManager::getInstance()->setCurrentScene("FirstDemo");
		}
		
		else if (curscene > 3) {
			curscene = 0;
		}
		else if (curscene < 0) {
			curscene = 3;
		}

		Renderer::getInstance()->update();
	}
	return 0;
}
