#version 330 core 

in vec4 vertex;
uniform mat4 modelViewProjMat;
uniform sampler2D textW;    
//uniform float time;

in vec2 uv0;
out vec2 vUv0;

void main() {   
    vec3 color = vec3(texture(textW,vUv0));
    
    fFragColor=vec4(color,1.0);
} 