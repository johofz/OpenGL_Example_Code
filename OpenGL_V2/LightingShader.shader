#shader VERTEX
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;

out vec3 v_normal;
out vec3 v_position;

uniform mat4 u_modelProjection;
uniform mat4 u_modelView;
uniform mat4 u_invModelView;

void main()
{
    gl_Position = u_modelProjection * vec4(a_position, 1.0f);
    v_normal = mat3(u_invModelView) * a_normal;
    v_position = vec3(u_modelView * vec4(a_position, 1.0f));
}

#shader FRAGMENT
#version 330 core

layout(location = 0) out vec4 f_color;

in vec3 v_normal;
in vec3 v_position;

struct Material {
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
    float shine;
};

struct DirectionalLight {
    vec3 direction;

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
};

uniform Material u_material;
uniform DirectionalLight u_directionalLight;


void main()
{
    vec3 view = normalize(-v_position);
    vec3 normal = normalize(v_normal);

    vec3 light = normalize(-u_directionalLight.direction);
    vec3 reflection = reflect(u_directionalLight.direction, normal);

    vec3 ambient = u_directionalLight.ambient * u_material.diffuse;
    vec3 diffuse = u_directionalLight.diffuse * max(dot(normal, light), 0.0f) * u_material.diffuse;
    vec3 specular = u_directionalLight.specular * pow(max(dot(reflection, view), 0.00001f), u_material.shine) * u_material.specular;

    vec3 normalLight = normalize(ambient + diffuse + specular + u_material.emissive);

    f_color = vec4(normalLight, 1.0f);
}