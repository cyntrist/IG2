#version 330 core
in vec4 vertex;

// coordenadas de textura en el shader
in vec2 uv0;

uniform mat4 modelViewProjMat;
out vec2 vUv0;

 void main() {
 	//vUv0 = uv0;

    // centrar en el cuadrado           (traslacion)
    // aplicar el facor zoom (ZF)       (escala)
    // centrarlas en el nuevo cuadrado  (traslacion)

    //vUv0.s = (uv0.s- 0.5) * (ZF) + 0.5; 
    //vUv0.t = (uv0.t- 0.5) * (ZF) + 0.5;
 	//gl_Position = modelViewProjMat * vertex;
 }