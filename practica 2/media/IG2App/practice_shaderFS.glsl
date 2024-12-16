#version 330 core 

in vec2 vUv0; 
uniform sampler2D textCorrosion;  
uniform sampler2D textChelo;  
uniform sampler2D textMetal;  

out vec4 fFragColor; 

void main() {   

    vec3 check_color = texture(textCorrosion, vUv0).rgb;
    bool check = check_color.r == 0 && check_color.g == 0 && check_color.b == 0;

    vec4 checker = texture(textCorrosion, vUv0);

    vec4 color = texture(textChelo, vUv0);
    if(check){
        vec4 color = texture(textChelo, vUv0);
    }
    else{
        vec4 color = texture(textMetal, vUv0);
    }

    fFragColor = checker;
} 