// shader.vert
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

uniform float changingColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aCol;

//    if(gl_VertexID == 0){
        vertexColor = vec3(aCol.r, changingColor, aCol.b);
//    }

    // -- Texture --
    texCoord = aTexCoord;
}
