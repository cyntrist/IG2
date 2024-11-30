#version 330 core 

out vec4 fFragColor;  
in vec2 textCoord;

uniform sampler2D textSky;    
uniform sampler2D textLight;    
uniform float my_time;

uniform float minLight;
uniform float maxLight; 

void main() { 

    vec3 color1 = vec3(texture(textSky,textCoord));
    vec3 color2 = vec3(texture(textLight,textCoord));

    vec3 mezcla = mix(color1,color2,0.5);

    float diff = maxLight - minLight;

    float lightFactor = minLight + (diff*((my_time+1)/2));

    fFragColor =  vec4( mezcla.x *lightFactor,
                        mezcla.y *lightFactor,
                        mezcla.z *lightFactor, 1); 

    vec3 cfinal = color1*color2*lightFactor;

    fFragColor =  vec4(cfinal , 1); 
                
}