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

vec3 CalcDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(u_ViewPosition - v_Position);

	vec3 dirLightRes = CalcDirLight(u_GlobalDirLight, norm, viewDir);

	vec3 pointLightRes = CalcPointLight(u_PointLight, norm, v_Position, viewDir);

	color = vec4(dirLightRes + pointLightRes, 1.0f);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);

	// diffuse
	float diff = max(dot(normal, lightDir), 0.0f);

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), u_StandardMaterial.shininess);

	// add up results
	vec3 ambient = light.ambient * vec3(texture(u_StandardMaterial.diffuse, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_StandardMaterial.diffuse, v_TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(u_StandardMaterial.specular, v_TexCoord));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

	vec3 lightToFragment = light.position - fragPos;
	vec3 lightDir = normalize(lightToFragment);

	// diffuse
	float diff = max(dot(normal, lightDir), 0.0f);

	// Spec
	vec3 reflectDir = reflect(-lightDir, normal);

	float specValue = pow(max(dot(viewDir, reflectDir), 0.0f), u_StandardMaterial.shininess);
	
	// attenuation
	float distance = length(lightToFragment);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * vec3(texture(u_StandardMaterial.diffuse, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_StandardMaterial.diffuse, v_TexCoord));
	vec3 specular = light.specular * specValue * vec3(texture(u_StandardMaterial.specular, v_TexCoord));

	return (diffuse + specular) * attenuation;
}