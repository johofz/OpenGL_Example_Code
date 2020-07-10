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