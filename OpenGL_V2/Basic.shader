#shader VERTEX
#version 330 core

layout(location = 0) in vec3 a_position;

out vec4 v_color;

uniform vec4 u_color;
uniform mat4 u_modelProjection;

void main()
{
    gl_Position = u_modelProjection * vec4(a_position, 1.0f);
    v_color = u_color;
}

#shader FRAGMENT
#version 330 core

layout(location = 0) out vec4 f_color;

in vec4 v_color;

void main()
{
    f_color = v_color;
}