#shader VERTEX
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;

out vec3 v_normal;
out vec3 v_position;
out vec3 v_lightPosition;

uniform vec3 u_lightPosition;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    mat4 modelView = u_view * u_model;
    gl_Position = u_projection * modelView * vec4(a_position, 1.0f);
    v_normal = mat3(transpose(inverse(u_model))) * a_normal;
    v_position = vec3(modelView * vec4(a_position, 1.0f));
    v_lightPosition = vec3(u_view * vec4(u_lightPosition, 1.0));
}

#shader FRAGMENT
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