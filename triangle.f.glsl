#version 400

out vec4 frag_colour;
in vec4 color;
in vec4 worldNormal;

void main(void) {
	vec4 lightVector= normalize(vec4(10.0,10.0,10.0, 1.0));
	float dot_product = max(dot(lightVector, normalize(worldNormal)), 0.0);
	frag_colour = color * dot_product;
}
