#version 400

out vec4 frag_colour;
in vec4 color;
in vec4 worldNormal;
in vec4 pos;

uniform vec3 lightPos;

void main(void) {
	vec4 lightVector = normalize(vec4(lightPos, 1.0) - pos);
	float dot_product = dot(normalize(lightVector), normalize(worldNormal));
	frag_colour = color * dot_product;
}
