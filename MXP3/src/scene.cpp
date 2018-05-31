#include "../include/scene.h"


Scene::Scene() : Entity()
{
	texturePath = "";
}

Scene::~Scene()
{
	
}

void Scene::update(double deltatime)
{
	updateChildren(deltatime);
}

Vector2 Scene::placeCenter(Entity* entity)
{
	return Vector2((Renderer::getInstance()->getResolution().x / 2) - (entity->size.x / 2), (Renderer::getInstance()->getResolution().y / 2) - (entity->size.x / 2));
}

void Scene::updateChildren(float deltatime)
{
	std::vector<std::vector<Entity*>>::iterator it = ZLayers.begin();
	while (it != ZLayers.end())
	{
		std::vector<Entity*>::iterator at = (*it).begin();
		while (at != (*it).end()) {
			(*at)->update(deltatime);
			(*at)->animator.update(deltatime);
			at++;
		}
		it++;
	}
}
