#version 450 core

in vec2 vertexUV;
in vec3 vertexNormal;
in vec3 fragmentPosition;

out vec4 fragmentColor;

uniform sampler2D u_snowGrassTexture;
uniform sampler2D u_grassTexture;
uniform vec3 u_viewPosition;

void main(void)
{
    vec3 lightColor = vec3(0.8f, 0.8f, 1.0f);
    vec3 lightPosition = vec3(5.0f, 30.0f, 2.0f);

    // smooth blending between grass and snow
    float height = fragmentPosition.y;
    float blendFactor = smoothstep(4.0f, 5.0f, height);

    vec4 grassTex = texture(u_grassTexture, vertexUV);
    vec4 snowTex = texture(u_snowGrassTexture, vertexUV);
    vec4 textureColor = mix(grassTex, snowTex, blendFactor);

    // lighting
    vec3 norm = normalize(vertexNormal);
    vec3 lightDir = normalize(lightPosition - fragmentPosition);
    vec3 viewDir = normalize(u_viewPosition - fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float diff = max(dot(norm, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    vec3 ambient = 0.1f * lightColor;
    vec3 diffuse = diff * lightColor;

    float specularShininess = (height - 3.0f)/(9.0f - 3.0f);

    vec3 specular = specularShininess * spec * lightColor;

    vec3 lighting = (ambient + diffuse + specular) * textureColor.rgb;
    fragmentColor = vec4(lighting, textureColor.a);
}
