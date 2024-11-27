#version 330 core
in vec2 vUv0;
// meter un vUv1

uniform sampler2D texturaL;
uniform sampler2D texturaM;
uniform float BF;
uniform float intLuzAmb;

// profundidad tmb -> gl_FragDepth
out vec4 fFragColor;

 void main() { 
    vec3 colorL = vec3(texture(texturaL, vUv0));
	//vec3 colorM = vec3(texture(texturaM, vUv0));
 	vec3 color = colorL; //*colorM;
 	fFragColor = vec4(color, 1.0);
 }