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

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

void main(void) {
	vec3 color = hasTexture ? texture(myTextureSampler, UV).rgb : simpleColor;

	vec3 ambient = ambientColor * color;

	vec4 lightVector = normalize(vec4(lightPos, 1.0) - position_world);
	float dot_product = max(dot(normalize(lightVector), normalize(vec4(normal_world, 1))), 0);
	vec3 diffuse = diffuseColor * color * dot_product;

    vec3 lightDir = normalize(lightPos - position_world.xyz);
    vec3 camDir = normalize(cameraPos - position_world.xyz);
	float spec = pow(max(0.0, dot(camDir, reflect(-lightDir, normal_world))), 32);
    vec3 specular = 0.8f * specularColor * spec;

	frag_colour = vec4(ambient + diffuse + specular, 1);
}
