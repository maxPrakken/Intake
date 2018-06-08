#include "..\include\entity.h"

int Entity::_nextGuid = 0;

Entity::Entity()
{
	_guid = _nextGuid;
	_nextGuid++;
	_parent = NULL;
	texturePath = "";
	spitesheetPath = "";

	flip = SDL_FLIP_NONE;

	ZLayers.push_back(ZLayer_base);

	animator = Animator();

	pos = Vector2(0, 0);
	size = Vector2(0, 0);
	rot = 0;
}

Entity::~Entity()
{
	delete _parent;
}

void Entity::update(double deltatime)
{
	animator.update(deltatime);
	std::vector<std::vector<Entity*>>::iterator it = ZLayers.begin();
	while (it != ZLayers.end())
	{
		std::vector<Entity*>::iterator at = (*it).begin();
		while (at != (*it).end()) {
			(*at)->update(deltatime);
			at++;
		}
		it++;
	}
}

void Entity::addchild(Entity* child)
{
	if (child->_parent != NULL) {
		child->_parent->removechild(child);
	}
	if (child->_parent == this) {
		return;
	}
	child->_parent = this;

	if (ZLayer < ZLayers.size() && ZLayer >= 0) {
		this->ZLayers[child->ZLayer].push_back(child);
	}
	else if (ZLayer >= ZLayers.size()) {
		this->ZLayers[ZLayers.size() - 1].push_back(child);
	}
	else {
		this->ZLayers[0].push_back(child);
	}
	
}

void Entity::removechild(Entity * child)
{
	std::vector< Entity* >::iterator it = ZLayers[child->ZLayer].begin();
	while (it != ZLayers[child->ZLayer].end()) {
		if ((*it)->_guid == child->_guid) {
			it = ZLayers[child->ZLayer].erase(it);
			return;
		}
		else {
			++it;
		}
	}
}

Entity* Entity::getChildren()
{
	std::vector<std::vector<Entity*>>::iterator it = ZLayers.begin();
	while (it != ZLayers.end()) {
		std::vector<Entity*>::iterator at = (*it).begin();
		while (at != (*it).end()) {
			return (*at);
		}
	}
	return NULL;
}

float Entity::distanceTo(Entity * other)
{
	return (pos - other->pos).mag();
}

Vector2 Entity::getParentPosition()
{
	if (_parent == NULL) {
		return pos;
	}
	else {
		return pos + _parent->getParentPosition();
	}
}

bool Entity::isColliding(Entity* other) {
	Vector2 pos = getParentPosition();
	Vector2 otherPos = other->getParentPosition();

	float dx = pos.x - otherPos.x;
	float dy = pos.y - otherPos.y;

	if ((abs(dx) * 2.0f < (size.x + other->size.x)) &&
		(abs(dy) * 2.0f < (size.y + other->size.y)))
	{
		return true;
	}
	return false;	
}

bool Entity::isColliding(Vector2 other)
{
	Vector2 pos = getParentPosition();

	if (other.x > pos.x && other.x < pos.x + this->size.x &&
		other.y > pos.y && other.y < pos.y + this->size.y)
	{
		return true;
	}

	return false;
}

bool Entity::isOutOfCanvas()
{
	Vector2 canvas = Renderer::getInstance()->getResolution();

	if (pos.y + size.y < 0 || pos.x + size.x < 0 || pos.y > canvas.y || pos.x > canvas.x) {
		return true;
	}
	return false;
}
