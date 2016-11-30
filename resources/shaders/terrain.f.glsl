#version 420

out vec4 color_out;

in vec2 UV;
in vec3 normal_world;
in vec3 position_world;

layout(binding=0) uniform sampler2D grass;
layout(binding=1) uniform sampler2D dirt;

uniform vec3 cameraPos;
uniform struct Material material;
#include "phong.h"

#define MAX_LIGHTS 8
uniform struct Light lights[MAX_LIGHTS];
uniform int activeLights = 0;

void main() {
	float fScale = position_world.y/255;

	vec4 color;
	if(fScale < 0.2) {
		color = texture2D(grass, UV);
	} else if (fScale > 0.4) {
		color = texture2D(dirt, UV);
	} else {
		  fScale -= 0.2;
          fScale /= (0.4-0.2);

          float fScale2 = fScale;
          fScale = 1.0-fScale;

          color = texture2D(grass, UV)*fScale;
          color += texture2D(dirt, UV)*fScale2;
	}

    vec3 total = vec3(0);
    for(int i = 0; i < MAX_LIGHTS; i++) {
        if((activeLights & (1 << i)) > 0) {
            total += applyLight(lights[i], color.xyz, normal_world);
        }
    }

    color_out = vec4(total, 1);
}