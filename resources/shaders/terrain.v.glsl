#version 400

layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 color;
out vec3 normal_world;
out vec2 UV;
out vec3 position_world;

void main() {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);

	position_world = vec3(modelMatrix * vec4(vp, 1.0));
    normal_world = normalize(mat3(transpose(inverse(modelMatrix))) * normal);

	UV = uv;
}