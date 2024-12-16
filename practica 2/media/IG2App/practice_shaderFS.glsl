#version 330 core 

in vec2 vUv0; 
uniform sampler2D textCorrosion;  
uniform sampler2D textChelo;  

out vec4 fFragColor; 

void main() {   
    fFragColor=vec4(1, 0.5, 0.2,1.0);
} 