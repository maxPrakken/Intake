#include "Explosion.h"

Explosion::Explosion()
{
	size = Vector2(100, 100);
	spitesheetPath = "assets/spritesheets/explosion.png";
	animator.rows = Vector2(4, 1);
	animator.paused = true;
	animator.cur = 0;
	animator.animateFromTo = Vector2(1, 3);
	animator.switchAfter = 0.1f;
}

Explosion::Explosion(Vector2 position, Vector2 size)
{
	pos = position;
	this->size = size;

	spitesheetPath = "assets/spritesheets/explosion.png";
	animator.rows = Vector2(4, 1);
	animator.cur = 0;
	animator.animateFromTo = Vector2(1, 3);
	animator.switchAfter = 0.2f;
}

Explosion::~Explosion()
{

}

void Explosion::update(double deltatime)
{
	if (animator.cur = animator.rows.x - 1) {
		animator.paused = true;
		animator.cur = animator.rows.x - 1;
		explosionDone = true;
	}
}
