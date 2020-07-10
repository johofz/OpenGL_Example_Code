#version 330 core

layout(location = 0) out vec4 f_color;

uniform vec3 u_objectColor;

void main()
{
    f_color = vec4(u_objectColor, 1.0);
}