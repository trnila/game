#version 420

layout(binding=0) uniform sampler2D modelTexture;
layout(binding=1) uniform sampler2D shadowTexture;
layout(binding=2) uniform sampler2D bumpTexture;

out vec4 frag_colour;

in vec3 normal_world;
in vec3 position_world;
in vec2 UV;
in vec3 ex_tangents;

uniform vec3 simpleColor;
uniform vec3 cameraPos;
uniform bool hasTexture;
uniform vec3 ambientColor;

uniform struct Material material;

#define MAX_LIGHTS 8
uniform struct Light lights[MAX_LIGHTS];
uniform int activeLights = 0;

in vec4 shadCoord;
uniform float offset;

#include "phong.h"

vec3 CalcNormal() {
	vec3 Normal = normalize(normal_world);
	vec3 Tangent = normalize(ex_tangents);
	//Gram–Schmidt process
	Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
	vec3 Bitangent = cross(Tangent, Normal);
	vec3 BumpMapNormal = texture(bumpTexture, UV).xyz;
	//převod z vektoru barvy o rozsahu <0,1> do vektoru normály <-1,1>
	BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
	// Transformační matice TBN
	mat3 TBN = mat3(Tangent, Bitangent, Normal);
	return normalize(TBN * BumpMapNormal);
}

void main(void) {
	vec3 color = hasTexture ? texture(modelTexture, vec2(UV.x, UV.y + sin(offset / 300))).rgb : simpleColor;

	vec3 ambient = material.ambientColor * ambientColor * color;

	vec3 total = vec3(0);
	for(int i = 0; i < MAX_LIGHTS; i++) {
		if((activeLights & (1 << i)) > 0) {
			total += applyLight(lights[i], color, CalcNormal());
	    }
	}

	float visibility = 1.0;
	if ( texture( shadowTexture, shadCoord.xy ).z  <  shadCoord.z - 0.005){
		visibility = 0.5;
	}

	frag_colour = vec4(ambient + visibility * total, 1);
}
