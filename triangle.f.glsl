#version 400

out vec4 frag_colour;

in vec3 normal_world;
in vec4 position_world;
in vec2 UV;

uniform vec3 lightPos;
uniform vec3 simpleColor;
uniform vec3 cameraPos;
uniform sampler2D myTextureSampler;
uniform bool hasTexture;

void main(void) {
	vec4 color = hasTexture ? texture(myTextureSampler, UV) : vec4(simpleColor, 1);

	vec4 ambient = 0.1 * color;

	vec4 lightVector = normalize(vec4(lightPos, 1.0) - position_world);
	float dot_product = max(dot(normalize(lightVector), normalize(vec4(normal_world, 1))), 0);
	vec4 diffuse = color * dot_product;

    vec3 lightDir = normalize(lightPos - position_world.xyz);
    vec3 camDir = normalize(cameraPos - position_world.xyz);
	float spec = pow(max(0.0, dot(camDir, reflect(-lightDir, normal_world))), 32);
    vec4 specular = 0.8f * vec4(1,1,1,1) * spec;

	frag_colour = ambient + diffuse + specular;
}
