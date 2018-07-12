#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include<GL/glew.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtc/matrix_transform.hpp>

class Camera {

private:
	double x = 0, y = 0, z = 0;
	float yrot = 0;
	float xrot = 0;
	glm::vec3 camtranslation = glm::vec3(0.0f, 0.0f, 0.0f);

public:
	//set position in global coords to pos
	void position(glm::vec3 pos) {
		camtranslation = pos;
	}
	//raw translation using global axis
	void translate(glm::vec3 translation) {
		camtranslation = camtranslation + translation;
	}
	//move using camera axis
	void move(char axis, float val) {
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
	void rotate(char axis, float angle) {
		if (axis == 'y') {
			yrot += angle;
		}
		else if (axis == 'x') {
			xrot += angle;
		}
	}
	glm::mat4 getView() {
		glm::mat4 camrotation = glm::rotate(yrot, glm::vec3(0, 1, 0))*glm::rotate(xrot,glm::vec3(1,0,0));
		return glm::inverse(glm::translate(camtranslation)*camrotation);
	}
};


//update rotation based on tick delta
double update(std::chrono::time_point<std::chrono::system_clock> &prev, std::chrono::time_point<std::chrono::system_clock> &current) {
	prev = current;
	current = std::chrono::system_clock::now();
	std::chrono::duration<double> frame_time = current - prev;
	return frame_time.count();
}

glm::mat4 updateCamera(Camera &cam, GLFWwindow* window, double frame_time, float dx, float dy) {
	float speed = 1.0f;
	float distance = speed * frame_time;
	if (glfwGetKey(window, GLFW_KEY_A)) {
		cam.move('x', -1*distance);
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		cam.move('x', 1*distance);
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		cam.move('z', -1*distance);
	}
	if (glfwGetKey(window, GLFW_KEY_W)) {
		cam.move('z', distance);
	}
	cam.rotate('y',dx);
	cam.rotate('x',dy);
	return cam.getView();
}

void getRectVertices(float width, float length, float height, std::vector<GLfloat> &g_vertex_buffer_data) {
	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f, 
		width, 0.0f, 0.0f,
		width, length, 0.0f,//
		0.0f, length, 0.0f,
		0.0f, 0.0f, 0.0f,
		width, length, 0.0f,//
		0.0f, 0.0f, 0.0f, 
		width, 0.0f, 0.0f,
		width, 0.0f, height,//
		0.0f, 0.0f, height,
		0.0f, 0.0f, 0.0f,
		width, 0.0f, height,//
		0.0f, 0.0f, 0.0f,
		0.0f, length, 0.0f,
		0.0f, length, height,//
		0.0f, 0.0f,height,
		0.0f, 0.0f, 0.0f,
		0.0f, length, height,//
		0.0f, 0.0f, height,
		width, 0.0f, height,
		width, length,height,//
		0.0f, length, height,
		0.0f, 0.0f, height,
		width, length, height,//
		0.0f, length, 0.0f,
		width, length, 0.0f,
		width, length, height,//
		0.0f, length, height,
		0.0f, length, 0.0f,
		width, length, height,//
		width, 0.0f, 0.0f,
		width, length, 0.0f,
		width, length, height,//
		width, 0.0f,height,
		width, 0.0f, 0.0f,
		width, length, height//
	};
	g_vertex_buffer_data.assign(vertices,vertices+108);
	return;
}

GLfloat* getRectColor(float r, float g, float b, static const GLfloat *colors) {
	GLfloat g_color_buffer_data[36];
	for (int i = 0; i < 12; i++) {
		g_color_buffer_data[i * 3] = r;
		g_color_buffer_data[i * 3 + 1] = g;
		g_color_buffer_data[i * 3 + 2] = b;
	}
	return g_color_buffer_data;
}

//draw objects helper function
void drawObjects(GLuint MatrixID, glm::mat4 MVP, GLuint vertexbuffer, GLuint colorbuffer, int vcount) {
	//MVP setup
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	//vertex setup stuff
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//color setup stuff
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//draw call
	glDrawArrays(GL_TRIANGLES, 0, vcount);

	//cleanup
	glDisableVertexAttribArray(0);
	return;
}