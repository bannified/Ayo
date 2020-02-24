#version 330 core

layout(location = 0) out vec4 color;

struct StandardMaterial {
	vec3 direction;

	sampler2D diffuse;
	sampler2D specular;
	float shininess;

	float intensity;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float intensity;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float intensity;

	// attenuation
	float constant;
	float linear;
	float quadratic;
};

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform StandardMaterial u_StandardMaterial;
uniform DirectionalLight u_GlobalDirLight;
uniform PointLight u_PointLight;

uniform vec3 u_ViewPosition;

uniform vec3 u_PointLightPosition;

void main() {
	color = texture(u_StandardMaterial.diffuse, v_TexCoord);
}