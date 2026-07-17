#version 460 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue = .0f;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main() {
//    FragColor = mix(texture(texture1, texCoord), vec4(vertexColor, 1.0f), 0.2f);
//    float mixV = clamp(mixValue, 0.0f, 1.0f);

//    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), mixValue);

//    float ambientStrength   = .1f;
    float specularStrength  = .5f;
//
    // Ambient lighting
    vec3 ambient = vec3(texture(material.diffuse, TexCoord)) * light.ambient;

    // Diffusive lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); // Both norm and lightColor are normalized -> dot produce result is cosine
    vec3 diffuse = diff * vec3(texture(material.diffuse, TexCoord)) * light.diffuse;

    // Specular Lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = spec * vec3(texture(material.specular, TexCoord)) * light.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
