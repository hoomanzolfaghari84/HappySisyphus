//--------------------------
// - Sisyphus 3D -
// Renderer3D Basic Shader
// --------------------------

#type vertex
#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    FragPos = vec3(u_Model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(u_Model))) * aNormal;
    gl_Position = u_Projection * u_View * vec4(FragPos, 1.0);
}

#type fragment
#version 450 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec4 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;

void main()
{
    // Normalize the normal vector
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_LightPos - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_LightColor;

    // Map from [-1, 1] to [0, 1] so we can see it as a color
    // vec3 colorFromNormal = norm * 0.5 + 0.5;

    // Multiply by object color to keep tinting if desired
    vec3 result = (ambient + diffuse) * u_ObjectColor.rgb;
    FragColor = vec4(result, u_ObjectColor.w);
}

