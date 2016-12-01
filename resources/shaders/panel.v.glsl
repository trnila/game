#version 400
layout(location=0) in vec2 pos;

out vec2 uv;
uniform vec2 scale;
uniform vec2 translate;


void main(void) {
	gl_Position = vec4(pos.x * scale.x + translate.x, pos.y * scale.y + translate.x, 0, 1);
	uv = vec2((pos.x+1)/2, 1 - (pos.y+1)/2);
}