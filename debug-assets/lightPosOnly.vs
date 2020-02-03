#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewProjectionMatrix;
uniform vec3 u_DirLightColor;

void main() {
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}