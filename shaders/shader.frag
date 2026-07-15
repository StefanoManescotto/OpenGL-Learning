#version 460 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D myTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue = .0f;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

void main() {
//    FragColor = vec4(vertexColor, 1.0f);
//    FragColor = texture(myTexture, texCoord);
//    FragColor = mix(texture(texture1, texCoord), vec4(vertexColor, 1.0f), 0.2f);
//    float mixV = clamp(mixValue, 0.0f, 1.0f);

//    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), mixValue);

    // Lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); // Both norm and lightColor are normalized -> dot produce result is cosine
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
