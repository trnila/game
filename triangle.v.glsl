#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 simpleColor;
out vec3 color;
out vec4 worldNormal;

void main(void) {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
	color = simpleColor;

	worldNormal = modelMatrix * vec4(normal, 1.0);
}
