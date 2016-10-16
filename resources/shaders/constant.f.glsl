#version 400

out vec4 frag_colour;
uniform vec3 simpleColor;

void main(void) {
	frag_colour = vec4(simpleColor, 1);
}
