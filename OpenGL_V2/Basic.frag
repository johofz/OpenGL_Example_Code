#version 330 core

layout(location = 0) out vec4 f_color;

in vec3 v_normal;
in vec3 v_position;
in vec3 v_lightPosition;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;
uniform vec3 u_cameraPosition;

void main()
{
    vec3 normal = normalize(v_normal);
    vec3 lightDirection = normalize(v_lightPosition - v_position);
    vec3 light = normalize(v_lightPosition);
    vec3 viewDirection = normalize(u_cameraPosition - v_position);
    vec3 reflectionDirection = reflect(-lightDirection, v_normal); 

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * u_lightColor;

    float diffusion = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diffusion * u_lightColor;

    float specularStrength = 0.5;
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0001), 16);
    vec3 specular = specularStrength * spec * u_lightColor;

    vec3 result = (ambient + diffuse + specular) * u_objectColor;
    f_color = vec4(result, 1.0f);
}