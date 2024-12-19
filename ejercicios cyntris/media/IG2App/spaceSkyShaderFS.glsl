#version 330 core 
in vec2 vUv0; 
uniform sampler2D space;  
uniform sampler2D light;  
uniform float intLuzAmb; 
out vec4 fFragColor; 

void main()
{ 
    vec4 colorL = vec4(texture(space,vUv0)); 
    vec4 colorM = vec4(texture(light, vUv0)); 
    vec4 color = mix(colorL,  colorM, 0.5)*intLuzAmb; 
    fFragColor = color; 
}