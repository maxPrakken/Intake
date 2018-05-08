#pragma once 

#include "scene.h"
#include <map>

//singleton scenemanager
class _declspec(dllexport) SceneManager {
public:
	//getinstance, gets instance of scenemanager
	static SceneManager* getInstance();

	virtual void update(double deltatime);

	Scene* currentScene;

	std::map<std::string, Scene*>sceneVector;

	void addScene(std::string name, Scene* scene);

	Scene* getScene(std::string name);

	void DeleteScene(std::string name);

	void setCurrentScene(std::string name);

private:

	static SceneManager* instance;

	//default constuctor
	SceneManager();
	virtual ~SceneManager();
};