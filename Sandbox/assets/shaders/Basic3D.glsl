//--------------------------
// - Sisyphus 3D -
// Renderer3D Basic Shader
// --------------------------

#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
    vec4 worldPos = u_Transform * vec4(a_Position, 1.0);
    v_FragPos = worldPos.xyz;

    v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal; // correct normal transform
    gl_Position = u_ViewProjection * worldPos;
}

#type fragment
#version 450 core

out vec4 FragColor;

in vec3 v_Normal;
in vec3 v_FragPos;

// Simple directional light
uniform vec3 u_LightDir;
uniform vec3 u_Color;

void main()
{
    vec3 norm = normalize(v_Normal);
    float diff = max(dot(norm, -u_LightDir), 0.0);

    vec3 diffuse = diff * u_Color;
  
    FragColor = vec4(abs(norm), 1.0); // absolute values, easier to see all directions
}
