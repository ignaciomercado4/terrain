#version 450 core

in vec3 v_fragPos;
in vec3 v_normal;
in vec2 v_uv;

out vec4 fragmentColor;

// DIPSHIT
struct Material {
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec3 emmisive;

    float shininess;
    float alpha;

    sampler2D diffuseMap;
    sampler2D specularMap;
    sampler2D bumpMap;
    sampler2D transparencyMap;
    sampler2D emissiveMap;

    int hasDiffuse;
    int hasSpecular;
    int hasBump;
    int hasTransparency;
    int hasEmissive;
};

uniform Material material;

uniform vec3 u_lightPos = vec3(10, 10, 10);
uniform vec3 u_lightColor = vec3(1.0);
uniform vec3 u_viewPos;

void main() {
    // normal / bump
    vec3 norm = normalize(v_normal);
    if(material.hasBump == 1) {
        vec3 bumpNormal = texture(material.bumpMap, v_uv).rgb;
        bumpNormal = normalize(bumpNormal * 2.0 - 1.0);
        norm = normalize(bumpNormal);
    }

    vec3 lightDir = normalize(u_lightPos - v_fragPos);

    // diffuse base
    vec3 baseDiffuse = material.diffuse;
    if(material.hasDiffuse == 1) {
        baseDiffuse *= texture(material.diffuseMap, v_uv).rgb;
    }

    // specular base
    vec3 baseSpecular = material.specular;
    if(material.hasSpecular == 1) {
        baseSpecular *= texture(material.specularMap, v_uv).rgb;
    }

    // ambient
    vec3 ambient = material.ambient * baseDiffuse;

    // diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * baseDiffuse * u_lightColor;

    // specular lighting
    vec3 viewDir = normalize(u_viewPos - v_fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), max(material.shininess, 1.0));
    vec3 specular = spec * baseSpecular * u_lightColor;

    // emissive
    vec3 emissive = material.emmisive;
    if(material.hasEmissive == 1) {
        emissive += texture(material.emissiveMap, v_uv).rgb;
    }

    vec3 result = ambient + diffuse + specular + emissive;

    // transparency
    float alphaValue = material.alpha;
    if(material.hasTransparency == 1) {
        alphaValue *= texture(material.transparencyMap, v_uv).r;
    }

    fragmentColor = vec4(result, alphaValue);
}