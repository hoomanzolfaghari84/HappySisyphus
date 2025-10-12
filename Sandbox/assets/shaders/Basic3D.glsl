//--------------------------
// - Sisyphus 3D -
// Renderer3D Basic Shader
// --------------------------

#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
    TexCoords = a_TexCoords;
    FragPos = vec3(u_Model * vec4(a_Position, 1.0));
    Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
    gl_Position = u_Projection * u_View * vec4(FragPos, 1.0);
}

#type fragment
#version 450 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 u_ViewPos;

struct Material {
    vec4 flatColor; // Tint for the diffuse texture
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
}; 

uniform Material u_Material;

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light u_Light;

void main()
{
    // ambient
    vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuse, TexCoords));

    // normalize the normal vector
    vec3 norm = normalize(Normal);

    // diffuse
    vec3 lightDir = normalize(u_Light.position - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuse, TexCoords));  
    

    // specular
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),  u_Material.shininess);
    vec3 specular = u_Light.specular * spec * vec3(texture(u_Material.specular, TexCoords));
    


    // Map from [-1, 1] to [0, 1] so we can see it as a color
    // vec3 colorFromNormal = norm * 0.5 + 0.5;

    // Multiply by object color to keep tinting if desired
    vec3 result = (ambient + diffuse + specular);// * u_Material.flatColor.rgb;
    FragColor = vec4(result, u_Material.flatColor.w);
}

