

#version 330 core 
in vec2 vUv0; 
uniform sampler2D textW;    
out vec4 fFragColor; 
void main(){ 
    vec4 color = texture(textW,vUv0); 
    fFragColor= color;


    }