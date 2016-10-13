#version 400
layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 normal_world;
out vec4 position_world;

void main(void) {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);

	position_world = modelMatrix * vec4(vp, 1.0);
	normal_world = mat3(transpose(inverse(modelMatrix))) * normal;
}
