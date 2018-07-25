#pragma once

#include <helpers.h>
class PhysicsObject
{
protected:
	glm::vec3 position;
	glm::vec3 scale;
	int vcount;
	std::vector<GLfloat> vertex_buffer_data;
	std::vector<GLfloat> color_buffer_data;
	GLuint vertex_buffer;
	GLuint color_buffer;

public:
	PhysicsObject();
	~PhysicsObject();
	void Scale(float x, float y, float z);
	void Translate(float x, float y, float z);
	void Position(float x, float y, float z);
	void ConfigBuffers();
	glm::vec3 GetScale();
	glm::vec3 GetPosition();
	glm::mat4 GetModel();
	std::vector<GLfloat> GetVertexBufferData();
	std::vector<GLfloat> GetColorBufferData();
	GLuint GetVertexBufferID();
	GLuint GetColorBufferID();
	int GetVertexCount();
};

class Rectangle : public PhysicsObject
{
public:
	Rectangle();
	~Rectangle();
};

