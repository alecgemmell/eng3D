#version 330 core

in vec3 fragmentcolor;
out vec3 color;

void main(){
	color = fragmentcolor;
}