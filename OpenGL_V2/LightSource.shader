#shader VERTEX
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;


uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    mat4 modelView = u_view * u_model;
    gl_Position = u_projection * modelView * vec4(a_position, 1.0f);
}

#shader FRAGMENT
#version 330 core

layout(location = 0) out vec4 f_color;

uniform vec3 u_objectColor;

void main()
{
    f_color = vec4(u_objectColor, 1.0);
}