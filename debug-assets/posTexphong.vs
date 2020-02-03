#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ModelMatrix;
uniform mat4 u_NormalMatrix;

uniform vec3 u_ViewPosition;

uniform mat4 u_ViewProjectionMatrix;
uniform vec3 u_PointLightPosition;

out vec3 v_Position;
out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TexCoord;

void main() {
	v_Position = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
	v_TexCoord = a_TexCoord;
	v_Normal = mat3(u_NormalMatrix) * a_Normal;

	gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
}