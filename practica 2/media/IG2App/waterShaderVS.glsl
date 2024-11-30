#version 330 core 
in vec4 vertex; 
in vec2 uv0; 


uniform mat4 modelViewProjMat; 
uniform float time;

uniform vec2 center;

out vec2 vUv0; 




void main(){ 
    vUv0=uv0; 

    vec4 vertexCoord = vertex;
    float distanceCenter = distance(vec2(vertexCoord.x,vertexCoord.z), center);

    float a = 50;  // lo rapido que va
    float b = 1;    // lo alto que sube

    vertexCoord.y   += sin(vertexCoord.x + (time*a)) * b 
                    + sin(vertexCoord.z + (distanceCenter) + (time*a)) * b;


    gl_Position = modelViewProjMat * vertexCoord; 
}