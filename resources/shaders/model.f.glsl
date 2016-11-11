#version 420

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

#include "phong.h"

void main(void) {
	vec3 color = hasTexture ? texture(modelTexture, UV).rgb : simpleColor;

	vec3 ambient = material.ambientColor * ambientColor * color;

	vec3 total = vec3(0);
	for(int i = 0; i < MAX_LIGHTS; i++) {
		if((activeLights & (1 << i)) > 0) {
			total += applyLight(lights[i], color);
	    }
	}

	frag_colour = vec4(ambient + total, 1);
}
