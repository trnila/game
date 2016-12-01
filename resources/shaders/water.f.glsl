#version 430
layout(binding=0) uniform sampler2D modelTexture;

out vec4 color;
in vec2 UV;
uniform float offset;

void main() {
	color = texture(modelTexture, vec2(UV.x, UV.y + sin(offset / 300)));
}