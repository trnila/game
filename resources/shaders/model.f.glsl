#version 420

struct Material {
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float shininess;
	float shininessStrength;
};

struct Light {
	vec4 position;
	vec3 diffuseColor;
    vec3 specularColor;
    float attenuation;
    vec3 coneDirection;
    float coneAngle;
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

#define MAX_LIGHTS 8
uniform struct Light lights[MAX_LIGHTS];
uniform int activeLights = 0;

in vec4 shadCoord;

void main(void) {
	vec3 color = hasTexture ? texture(modelTexture, UV).rgb : simpleColor;

	vec3 ambient = material.ambientColor * ambientColor * color;

	vec3 total = vec3(0);
	for(int i = 0; i < MAX_LIGHTS; i++) {
		if((activeLights & (1 << i)) > 0) {
			vec4 lightVector;
			float attenuation = 1.0;
			if(lights[i].position.w == 0.0) {
				lightVector = vec4(normalize(-lights[i].position.xyz), 1);
			} else {
				lightVector = normalize(vec4(lights[i].position.xyz, 1.0) - position_world);
				float distanceToLight = length(lights[i].position.xyz - position_world.xyz);
				//attenuation = 1.0 / (1.0 + lights[i].attenuation * pow(distanceToLight, 2));

				//cone restrictions (affects attenuation)
                float lightToSurfaceAngle = degrees(acos(dot(vec3(-lightVector), normalize(lights[i].coneDirection))));
                if(lightToSurfaceAngle > lights[i].coneAngle){
                    attenuation = 0.0;
                }
			}

			float dot_product = max(dot(normalize(lightVector), normalize(vec4(normal_world, 1))), 0);
			vec3 diffuse = material.diffuseColor * lights[i].diffuseColor * color * dot_product;

		    vec3 lightDir = vec3(normalize(lights[i].position - position_world));
		    vec3 camDir = normalize(cameraPos - position_world.xyz);
			float spec = pow(max(0.0, dot(camDir, reflect(-lightDir, normal_world))), material.shininess);
		    vec3 specular = material.shininessStrength * material.specularColor * lights[i].specularColor * spec;

		    float visibility = 1.0;
	        if ( texture( shadowTexture, shadCoord.xy ).z  <  shadCoord.z - 0.005){
	       //     visibility = 0.5;
	        }

	        total += visibility * attenuation * (diffuse + specular);
	    }
	}

	frag_colour = vec4(ambient + total, 1);
}
