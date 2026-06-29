#version 460 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D myTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue = .2f;

void main() {
//    FragColor = vec4(vertexColor, 1.0f);
//    FragColor = texture(myTexture, texCoord);
//    FragColor = mix(texture(texture1, texCoord), vec4(vertexColor, 1.0f), 0.2f);
//    float mixV = clamp(mixValue, 0.0f, 1.0f);

    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), mixValue);
}
