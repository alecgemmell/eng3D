#pragma once
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtc/matrix_transform.hpp>
class Camera {

private:
	float yrot = 0;
	float xrot = 0;
	glm::vec3 camtranslation = glm::vec3(0.0f, 0.0f, 0.0f);

public:
	Camera();
	~Camera();
	//set position in global coords to pos
	void position(glm::vec3 pos);
	//raw translation using global axis
	void translate(glm::vec3 translation);
	//move using camera axis
	void move(char axis, float val);
	//rotate relative to current orientation
	void rotate(char axis, float angle);
	glm::mat4 getView();
};