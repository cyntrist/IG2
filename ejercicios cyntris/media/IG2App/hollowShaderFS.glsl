#version 330 core
in vec2 vUv0;
uniform sampler2D textA;
uniform sampler2D textB;
uniform float flipping;
out vec4 fFragColor;

void main() {
    vec3 colorA = vec3(texture(textA, vUv0));
    vec3 colorB = vec3(texture(textB, vUv0));
    // vec3 color = mix(colorL, colorM, 1.0) * intLuzAmb;
    vec3 color = colorB;

    if (colorA.r == 0 && colorA.g == 0 && colorA.b == 0) 
        discard;
    
    fFragColor = vec4(color, 1.0);
}