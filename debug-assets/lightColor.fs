#version 330 core
			
layout(location = 0) out vec4 color;

uniform mat4 u_ViewProjectionMatrix;
uniform vec3 u_DirLightColor;

in vec3 v_Position;

void main() {
	color = vec4(u_DirLightColor, 1.0f);
}