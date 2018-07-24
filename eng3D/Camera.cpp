#include <Camera.h>
Camera::Camera()
{
}
Camera::~Camera()
{
}
//set position in global coords to pos
void Camera::position(glm::vec3 pos) {
	camtranslation = pos;
}
//raw translation using global axis
void Camera::translate(glm::vec3 translation) {
	camtranslation = camtranslation + translation;
}
//move using camera axis
void Camera::move(char axis, float val) {
	glm::vec3 direction = glm::rotateY(glm::vec3(0, 0, -1), yrot);
	switch (axis) {
	case 'x':
		direction = glm::rotateY(direction, 3.14159f / 2);
		camtranslation = camtranslation - (direction * (float)val);
		break;
	case 'z':
		camtranslation = camtranslation + (direction * (float)val);
		break;
	}
}

//rotate relative to current orientation
void Camera::rotate(char axis, float angle) {
	if (axis == 'y') {
		yrot += angle;
	}
	else if (axis == 'x') {
		xrot += angle;
	}
}
glm::mat4 Camera::getView() {
	glm::mat4 camrotation = glm::rotate(yrot, glm::vec3(0, 1, 0))*glm::rotate(xrot, glm::vec3(1, 0, 0));
	return glm::inverse(glm::translate(camtranslation)*camrotation);
}
