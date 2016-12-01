#version 420
layout(binding=0) uniform sampler2D myTexture;
in vec2 uv;

void main() {
	gl_FragColor = texture(myTexture, uv);
}