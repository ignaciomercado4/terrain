#version 450 core

in vec4 vertexColor;
in vec2 vertexUV;
in vec3 vertexNormal;
in vec3 fragmentPosition;

out vec4 fragmentColor;

uniform sampler2D u_texture;
uniform vec3 u_viewPosition;  // camera position in world space

void main(void)
{
    // --- Light setup ---
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightPosition = vec3(5.0f, 30.0f, 2.0f);

    // --- Sample base texture color ---
    vec4 textureColor = texture(u_texture, vertexUV);

    // --- Normalize inputs ---
    vec3 norm = normalize(vertexNormal);
    vec3 lightDir = normalize(lightPosition - fragmentPosition);

    // --- Ambient lighting ---
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // --- Diffuse lighting ---
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // --- Specular lighting ---
    float specularStrength = 0.5f; // how strong the shine is
    vec3 viewDir = normalize(u_viewPosition - fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  // reflection of light around normal
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // shininess exponent
    vec3 specular = specularStrength * spec * lightColor;

    // --- Combine all lighting ---
    vec3 lighting = (ambient + diffuse + specular) * textureColor.rgb;

    // --- Output final color ---
    fragmentColor = vec4(lighting, textureColor.a);
}
