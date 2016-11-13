#version 420

out vec4 frag_colour;

in vec2 UV;
in vec3 normal_out;
in vec3 worldPos;

layout(binding=0) uniform sampler2D grass;
layout(binding=1) uniform sampler2D dirt;


void main() {
	vec3 ok = vec3(0, 0, 1);

	float fScale = worldPos.y/255;

	if(fScale < 0.2) {
		frag_colour = texture2D(grass, UV);
	} else if (fScale > 0.4) {
		frag_colour = texture2D(dirt, UV);
	} else {
		  fScale -= 0.2;
          fScale /= (0.4-0.2);

          float fScale2 = fScale;
          fScale = 1.0-fScale;

          frag_colour += texture2D(grass, UV)*fScale;
          frag_colour += texture2D(dirt, UV)*fScale2;
	}

//	frag_colour = vec4(normal_out, 1);


	vec3 lightPos = vec3(-20, 64, 10);
	vec3 lightVector = normalize(lightPos - worldPos);
	float dot_product = max(dot(normalize(lightVector), normalize(normal_out)), 0);
    frag_colour *= dot_product;


}