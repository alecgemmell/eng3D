#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

//set position in global coords to pos
void Player::position(glm::vec3 pos) {
	translation = pos;
}
//raw translation using global axis
void Player::translate(glm::vec3 translation) {
	translation = translation + translation;
}
//move using camera axis
void Player::move(char axis, float val) {
	glm::vec3 direction = glm::rotateY(glm::vec3(0, 0, -1), yrot);
	switch (axis) {
	case 'x':
		direction = glm::rotateY(direction, 3.14159f / 2);
		translation = translation - (direction * (float)val);
		break;
	case 'z':
		translation = translation + (direction * (float)val);
		break;
	}
}

//rotate relative to current orientation
void Player::rotate(char axis, float angle) {
	if (axis == 'y') {
		yrot += angle;
	}
	else if (axis == 'x') {
		xrot += angle;
	}
}
void Player::update(PhysicsObject* rect,float dt)
{
	translation += tryMove(rect, dt);
	velocity -= glm::vec3(0.0f, 9.8f, 0.0f)*dt;
	return;
}
glm::vec3 Player::tryMove(PhysicsObject* rect, float dt)
{
	//try the move in direction, return max actionable movement
	//just vertical collision check for now;
	glm::vec3 step = velocity * dt;
	glm::vec3 goal = translation + step;
	float y0 = rect->GetPosition().y - rect->GetScale().y / 2;
	float y1 = rect->GetPosition().y + rect->GetScale().y/2;

	if ((translation.y - height > y1) && (goal.y - height <= y1)) {
		goal.y=y1+height+0.001f;
		velocity.y = 0;
	}
	else if ((translation.y < y0) && (goal.y >= y0)) {
		goal.y = y0 - .001f;
		velocity.y = 0;
	}
	step = goal - translation;
	return step;
}


glm::mat4 Player::getView() {
	glm::mat4 camrotation = glm::rotate(yrot, glm::vec3(0, 1, 0))*glm::rotate(xrot, glm::vec3(1, 0, 0));
	return glm::inverse(glm::translate(translation)*camrotation);
}
