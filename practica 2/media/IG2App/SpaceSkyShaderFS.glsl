#version 330 core 

out vec4 fFragColor;  
in vec2 vUv0;

uniform sampler2D textSky;    
uniform sampler2D textLight;    
uniform float time;

uniform float minLight;
uniform float maxLight; 

void main() { 

    vec3 t1 = vec3(texture(textSky,vUv0));
    vec3 t2 = vec3(texture(textLight,vUv0));

    vec3 mezcla = mix(t1, t2, 0.5);

    float diff = maxLight - minLight;

    float lfactor = minLight + (diff*( (time+1) / 2));

    fFragColor =  vec4( mezcla.x * lfactor,
                        mezcla.y * lfactor,
                        mezcla.z * lfactor, 1); 

    vec3 color = t1 * t2 * lfactor;

    fFragColor =  vec4(color , 1); 
                
}