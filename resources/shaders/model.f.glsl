#version 420

struct Material {
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float shininess;
	float shininessStrength;
};

struct Light {
	vec3 position;
	vec3 diffuseColor;
    vec3 specularColor;
};

layout(binding=0) uniform sampler2D modelTexture;
layout(binding=1) uniform sampler2D shadowTexture;

out vec4 frag_colour;

in vec3 normal_world;
in vec4 position_world;
in vec2 UV;

uniform vec3 simpleColor;
uniform vec3 cameraPos;
uniform bool hasTexture;
uniform vec3 ambientColor;

uniform struct Material material;

uniform struct Light lights[5];
uniform int totalLights;

in vec4 shadCoord;

void main(void) {
	vec3 color = hasTexture ? texture(modelTexture, UV).rgb : simpleColor;

	vec3 ambient = material.ambientColor * ambientColor * color;

	vec3 total = vec3(0);
	for(int i = 0; i < 2; i++) {
		vec4 lightVector = normalize(vec4(lights[i].position, 1.0) - position_world);
		float dot_product = max(dot(normalize(lightVector), normalize(vec4(normal_world, 1))), 0);
		vec3 diffuse = material.diffuseColor * lights[i].diffuseColor * color * dot_product;

	    vec3 lightDir = normalize(lights[i].position - position_world.xyz);
	    vec3 camDir = normalize(cameraPos - position_world.xyz);
		float spec = pow(max(0.0, dot(camDir, reflect(-lightDir, normal_world))), material.shininess);
	    vec3 specular = material.shininessStrength * material.specularColor * lights[i].specularColor * spec;

	    float visibility = 1.0;
        if ( texture( shadowTexture, shadCoord.xy ).z  <  shadCoord.z - 0.005){
            visibility = 0.5;
        }

        total += visibility * diffuse + specular;
	}

	frag_colour = vec4(ambient + total, 1);
}
