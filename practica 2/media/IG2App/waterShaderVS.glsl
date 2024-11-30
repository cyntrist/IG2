#version 330 core 

out vec4 fFragColor;  
in vec2 vUv0;

uniform sampler2D textW;    

void main() { 

        vUv0=uv0; 
        gl_Position=modelViewProjMat*vertex;        
}