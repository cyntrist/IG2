#version 330 core
in vec4 vertex;
uniform mat4 modelViewProjMat;

void main() {
 	gl_Position = modelViewProjMat * vertex;
}