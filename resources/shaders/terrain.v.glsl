#version 400

layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 color;
out vec2 UV;

void main() {
	gl_Position = projectionMatrix * viewMatrix * /*modelMatrix * */vec4(vp, 1.0);
	UV = uv;
}