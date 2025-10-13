//--------------------------
// - Sisyphus 3D -
// Renderer3D Light Src Shader
// --------------------------

#type vertex
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;


void main()
{
    vec3 FragPos = vec3(u_Model * vec4(aPos, 1.0));
    gl_Position = u_Projection * u_View * vec4(FragPos, 1.0);
}

#type fragment
#version 450 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0);
}

