#version 420

out vec4 color_out;

in vec2 UV;
in vec3 normal_world;
in vec3 position_world;

layout(binding=0) uniform sampler2D grass;
layout(binding=1) uniform sampler2D dirt;
layout(binding=2) uniform sampler2D snow;

uniform vec3 cameraPos;
uniform struct Material material;
#include "phong.h"

#define MAX_LIGHTS 8
uniform struct Light lights[MAX_LIGHTS];
uniform int activeLights = 0;

void main() {
	float fScale = position_world.y/40;
	float mez = 0.07;
	float y1 = 0.1;
	float y2 = 0.5;
	float y3 = 0.95;

	vec4 color;
	if(fScale < y1 - mez) {
		color = texture2D(grass, UV);
	} else if (fScale < y1 + mez) {
		  fScale = (fScale - (y1 - mez)) / (2 * mez);

          color = texture2D(grass, UV)*(1.0 - fScale);
          color += texture2D(dirt, UV)*fScale;
	} else if(fScale < y2 - mez) {
		color = texture2D(dirt, UV);
	} else if(fScale < y2 + mez) {
			fScale = (fScale - (y2 - mez)) / (2 * mez);

          color = texture2D(dirt, UV)*(1.0 - fScale);
          color += texture2D(snow, UV)*fScale;
	} else {
		color = texture2D(snow, UV);
	}

    vec3 total = vec3(0);
    for(int i = 0; i < MAX_LIGHTS; i++) {
        if((activeLights & (1 << i)) > 0) {
            total += applyLight(lights[i], color.xyz, normal_world);
        }
    }

    color_out = vec4(total, 1);
}