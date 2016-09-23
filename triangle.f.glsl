out vec4 frag_colour;
in vec4 color;

void main(void) {
	frag_colour = vec4 (1.0, 0.0, 0.0, 1.0);
	frag_colour = color;
}
