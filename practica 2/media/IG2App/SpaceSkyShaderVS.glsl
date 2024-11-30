#version 330 core 

in vec4 vertex;
uniform mat4 modelViewProjMat;
uniform float time;
uniform float minZoom; 
uniform float maxZoom; 

in vec2 uv0;
out vec2 vUv0;

void main() {   

    float a = (minZoom + maxZoom)/2;
    float b = maxZoom - a;

	// ZF = sintime * a + b
    float factor = (time*b) + a; //zoom factor

    vUv0.s = (uv0.s - minZoom) * (factor) + minZoom;
    vUv0.t = (uv0.t - minZoom) * (factor) + minZoom;
    
    gl_Position = modelViewProjMat * vertex;  

} 