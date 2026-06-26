#version 460 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D myTexture;

void main() {
//    FragColor = vec4(vertexColor, 1.0f);
//    FragColor = texture(myTexture, texCoord);
    FragColor = mix(texture(myTexture, texCoord), vec4(vertexColor, 1.0f), 0.2f);
}
