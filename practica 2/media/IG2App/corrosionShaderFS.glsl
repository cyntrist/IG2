#version 330 core 

in vec2 vUv0; 
uniform sampler2D textC;  
uniform sampler2D textM;  
uniform sampler2D textChelo;  
uniform float flipping;

out vec4 fFragColor; 
void main() {   

    vec4 corrosionColor = texture(textC, vUv0);
    if (corrosionColor.r > 0.6) {
        discard;
    }

    // Determinar si estamos procesando la cara frontal o trasera
    float faceSide = 0;
    if(gl_FrontFacing)
        faceSide = 1.0;
    else
        faceSide = -1.0;
    

    // ???
    faceSide *= flipping;

    // Seleccionar la textura según la cara
    vec4 side = texture(textM, vUv0);

    if(faceSide > 0.0 )
        side = texture(textM, vUv0);
    else
        side = texture(textChelo, vUv0)

    fFragColor = sideColor; // Asignar el color de la textura al fragmento

} 