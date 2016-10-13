#version 400

out vec4 frag_colour;

in vec3 normal_world;
in vec4 position_world;

uniform vec3 lightPos;
uniform vec3 simpleColor;

void main(void) {
	vec4 lightVector = normalize(vec4(lightPos, 1.0) - position_world);
	float dot_product = dot(normalize(lightVector), normalize(vec4(normal_world, 1)));
	frag_colour =  vec4( 0.1, 0.1, 0.1, 1.0) + vec4(simpleColor, 1) * dot_product;

	if(dot_product < 0) {
		frag_colour = vec4(0,0 ,1,1);
	}
}
