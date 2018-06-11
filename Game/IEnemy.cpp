#include "IEnemy.h"

void IEnemy::update(double deltatime)
{
	Entity::update(deltatime);
	
	if (!pointVector.empty()) {
		checkPoint();
		goTo(deltatime);
	}

	if (goCircles) {
		goCircle(startPos, radiusSize, circleSpeed);
		//startPos = Vector2(startPos.x + 1, startPos.y);
	}

	if (health <= 0) {
		isDead = true;
	}
}

void IEnemy::setGoCircles(bool yesno, int radiusSize, float speed)
{
	goCircles = yesno;
	this->radiusSize = radiusSize;
	this->circleSpeed = speed;
	startPos = this->pos;
}


void IEnemy::goTo(double deltatime)
{
	direction = point - this->pos;
	direction.normalize();
	direction *= speed * deltatime;
	this->pos += direction;
}

void IEnemy::checkPoint()
{
	//dirty way to get index, cant do it differently because vector2 doesnt work
	//with pointers. :(
	if (vectorIndex == 0) {
		std::vector<Vector2>::iterator it = pointVector.begin();
		while (it != pointVector.end()) {
			vectorIndex++;
			it++;
		}
	}

	//set index to 0 if higher or equal to vector size
	if (index >= vectorIndex - 1) {
		index = 0;
	}

	//overshoot right-under
	if (direction.x >= 0 && direction.y <= 0) {
		if (pos.x >= point.x && pos.y <= point.y) {
			index++;
		}
	}

	//overshoot left-under
	else if (direction.x <= 0 && direction.y >= 0) {
		if (pos.x <= point.x && pos.y >= point.y) {
			index++;
		}
	}

	//overshoot left-up
	else if (direction.x <= 0 && direction.y <= 0) {
		if (pos.x <= point.x && pos.y <= point.y) {
			index++;
		}
	}

	//overshoot right-up
	else if (direction.x >= 0 && direction.y >= 0) {
		if (pos.x >= point.x && pos.y >= point.y) {
			index++;
		}
	}

	point = pointVector[index];
}

void IEnemy::goCircle(Vector2 startpoint, int radiusSize, float speed)
{
	if (radiusSize > 0) {
		Vector2 v2 = startpoint - startpoint + radiusSize;
		float r = v2.mag();

		float posX = (cos(circleAngle) * r) + (startpoint.x - r);
		float posY = (sin(circleAngle) * r) + startpoint.y - r;

		this->pos = Vector2(posX, posY);
		circleAngle += speed;
	}
}
