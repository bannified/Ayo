#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
}

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

uniform vec3 u_ViewPosition;

uniform vec3 u_DirLightColor;
uniform float u_DirLightIntensity;

uniform vec3 u_SpecColor;

uniform vec3 u_PointLightPosition;

void main() {
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_PointLightPosition - v_Position);

	// Spec
	vec3 viewDir = normalize(u_ViewPosition - v_Position);
	vec3 reflectDir = reflect(-lightDir, norm);

	float specValue = pow(max(dot(viewDir, reflectDir), 0.0f), 32);

	vec3 specular = u_SpecColor * specValue * u_DirLightColor;

	vec3 ambient = u_DirLightColor * u_DirLightIntensity;

	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 diffuse = diff * u_DirLightColor;

	vec3 result = (ambient/3.0f + diffuse/3.0f + specular/3.0f) * mix(texture(u_Texture, v_TexCoord), texture(u_Texture1, v_TexCoord), 0.2).rgb;

	color = vec4(result, 1.0f);
}