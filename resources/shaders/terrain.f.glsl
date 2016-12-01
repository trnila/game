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

<vec4 blend(sampler2D xTexture, sampler2D yTexture, sampler2D zTexture) {
        vec3 blending = abs( normal_world );
        blending = normalize(max(blending, 0.0001));
        float b = (blending.x + blending.y + blending.z);
        blending /= vec3(b, b, b);

        float scale = 0.05;
        vec4 xaxis = texture2D( xTexture, position_world.yz * scale);
        vec4 yaxis = texture2D( yTexture, position_world.xz * scale);
        vec4 zaxis = texture2D( zTexture, position_world.xy * scale);
        // blend the results of the 3 planar projections.
        return xaxis * blending.x + yaxis * blending.y + zaxis * blending.z;
}


void main() {
	float fScale = position_world.y/40;
	float mez = 0.07;
	float y1 = 0.1;
	float y2 = 0.5;
	float y3 = 0.95;

	vec4 color;
	if(fScale < y1 - mez) {
		color = blend(grass, grass, grass);
	} else if (fScale < y1 + mez) {
		  fScale = (fScale - (y1 - mez)) / (2 * mez);

          color = blend(grass, grass, grass)*(1.0 - fScale);
          color += blend(grass, dirt, dirt)*fScale;
	} else if(fScale < y2 - mez) {
		color = blend(grass, dirt, dirt);
	} else if(fScale < y2 + mez) {
			fScale = (fScale - (y2 - mez)) / (2 * mez);

          color = blend(grass, dirt, dirt)*(1.0 - fScale);
          color += blend(snow, snow, snow)*fScale;
	} else {
		color = blend(snow, snow, snow);
	}

    vec3 total = vec3(0);
    for(int i = 0; i < MAX_LIGHTS; i++) {
        if((activeLights & (1 << i)) > 0) {
            total += applyLight(lights[i], color.xyz, normal_world);
        }
    }

    color_out = vec4(total, 1);
}