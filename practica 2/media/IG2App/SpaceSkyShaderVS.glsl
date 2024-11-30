#version 330 core 

in vec4 vertex;
uniform mat4 modelViewProjMat;
uniform float my_time;
uniform float minZoom; 
uniform float maxZoom; 

in vec2 uv0;
out vec2 textCoord;

void main() {   

    float a = (minZoom + maxZoom)/2;
    float b = maxZoom  -a;

    //formula buena : (my_time*b) + a
    float factor = (my_time*b) + a; //zoom factor

    textCoord.s = (uv0.s- minZoom) * (factor) + minZoom;
    textCoord.t = (uv0.t- minZoom) * (factor) + minZoom;
    
    gl_Position = modelViewProjMat * vertex;  

} 