#version 420

out vec4 frag_colour;

in vec2 UV;
layout(binding=0) uniform sampler2D grass;
layout(binding=1) uniform sampler2D dirt;


void main() {
	frag_colour = texture2D(dirt, UV);
}