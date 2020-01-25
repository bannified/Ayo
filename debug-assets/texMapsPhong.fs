#version 330 core

layout(location = 0) out vec4 color;

struct StandardMaterial {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform StandardMaterial u_StandardMaterial;

uniform vec3 u_ViewPosition;

uniform vec3 u_DirLightColor;
uniform float u_DirLightIntensity;

uniform vec3 u_SpecColor;

uniform vec3 u_PointLightPosition;

void main() {
	// ambient
	vec3 ambient = (u_DirLightColor * u_DirLightIntensity) * vec3(texture(u_StandardMaterial.diffuse, v_TexCoord));

	// diffuse
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_PointLightPosition - v_Position);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * u_DirLightColor * vec3(texture(u_StandardMaterial.diffuse, v_TexCoord));

	// Spec
	vec3 viewDir = normalize(u_ViewPosition - v_Position);
	vec3 reflectDir = reflect(-lightDir, norm);

	float specValue = pow(max(dot(viewDir, reflectDir), 0.0f), u_StandardMaterial.shininess);
	vec3 specular = u_SpecColor * specValue * (vec3(texture(u_StandardMaterial.specular, v_TexCoord)));	

	vec3 result = (ambient + diffuse + specular);

	color = vec4(result, 1.0f);
}