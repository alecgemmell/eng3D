#pragma once
#include <helpers.h>
#include <Object.h>
class Player
{
private:
	float yrot = 0;
	float xrot = 0;
	float height = 3.0f;
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
public:
	//set position in global coords to pos
	void position(glm::vec3 pos);
	//raw translation using global axis
	void translate(glm::vec3 translation);
	//move using camera axis
	void move(char axis, float val);
	//rotate relative to current orientation
	void rotate(char axis, float angle);
	void update(PhysicsObject* rect, float dt);
	glm::vec3 tryMove(PhysicsObject* rect, float dt);
	glm::mat4 getView();
	Player();
	~Player();
};

