#include "Object.h"



PhysicsObject::PhysicsObject()
{
}


PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::Scale(float x, float y, float z)
{
	scale.x *= x;
	scale.y *= y;
	scale.z *= z;
	return;
}

void PhysicsObject::Translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void PhysicsObject::Position(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void PhysicsObject::ConfigBuffers()
{
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(vertex_buffer_data[0]), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size()*sizeof(color_buffer_data[0]), &color_buffer_data[0], GL_STATIC_DRAW);
	return;
}

glm::vec3 PhysicsObject::GetScale()
{
	return scale;
}

glm::vec3 PhysicsObject::GetPosition()
{
	return position;
}

glm::mat4 PhysicsObject::GetModel()
{
	return glm::translate(position)*glm::scale(scale)*glm::mat4(1.0f);
}

std::vector<GLfloat> PhysicsObject::GetVertexBufferData()
{
	return vertex_buffer_data;
}

std::vector<GLfloat> PhysicsObject::GetColorBufferData()
{
	return color_buffer_data;
}

GLuint PhysicsObject::GetVertexBufferID()
{
	return vertex_buffer;
}

GLuint PhysicsObject::GetColorBufferID()
{
	return color_buffer;
}

int PhysicsObject::GetVertexCount()
{
	return vcount;
}

Rectangle::Rectangle()
{
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	vcount = 108;
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,//
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,//
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,//
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,//
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,//
		-0.5f, -0.5f,0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,//
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f,0.5f,//
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,//
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,//
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,//
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,//
		0.5f, -0.5f,0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, 0.5f//
	};
	vertex_buffer_data.assign(vertices, vertices + 108);
	GLfloat colors[108];
	for (int i = 0; i < 108; ++i) {
		if (i / 18 == 0) {
			colors[i] = 1.0f;
		}
		else if (i / 18 == 1) {
			colors[i] = 0.2f;
		}
		else if (i / 18 == 2) {
			if (i % 3 == 0) {
				colors[i] = 0.7f;
			}
			else if (i % 3 == 1) {
				colors[i] = 0.3f;
			}
			else {
				colors[i] = 0.3f;
			}
		}
		else if (i / 18 == 2) {
			if (i % 3 == 0) {
				colors[i] = 0.3f;
			}
			else if (i % 3 == 1) {
				colors[i] = 0.7f;
			}
			else {
				colors[i] = 0.3f;
			}
		}
		else if (i / 18 == 2) {
			if (i % 3 == 0) {
				colors[i] = 0.3f;
			}
			else if (i % 3 == 1) {
				colors[i] = 0.3f;
			}
			else {
				colors[i] = 0.7f;
			}
		}
		else {
			if (i % 3 == 0) {
				colors[i] = 0.6f;
			}
			else if (i % 3 == 1) {
				colors[i] = 0.6f;
			}
			else {
				colors[i] = 0.4f;
			}

		}
		color_buffer_data.assign(colors, colors + 108);
	}
	return;
}

Rectangle::~Rectangle()
{
}
