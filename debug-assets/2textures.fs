#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

void main() {
	color = mix(texture(u_Texture, v_TexCoord), texture(u_Texture1, v_TexCoord), 0.2);
}