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

vec3 applyLight(Light light, vec3 color, vec3 N) {
	vec3 lightVector;
	float attenuation = 1.0;
	if(light.position.w == 0.0) {
		lightVector = normalize(-light.position.xyz);
	} else {
		lightVector = normalize(light.position.xyz - position_world);
		float distanceToLight = length(light.position.xyz - position_world.xyz);
		attenuation = 1.0 / (1.0 + light.attenuation * distanceToLight*distanceToLight);

		// spotlight
		if(light.coneAngle > 0.0) {
			float lightToSurfaceAngle = degrees(acos(dot(vec3(-lightVector), normalize(light.coneDirection))));
			attenuation = max(0, dot(vec3(-lightVector), normalize(light.coneDirection)));
		}
	}

	float dot_product = max(dot(normalize(lightVector), normalize(N)), 0);
	vec3 diffuse = material.diffuseColor * light.diffuseColor * color * dot_product;

	vec3 lightDir = vec3(normalize(light.position.xyz - position_world));
	vec3 camDir = normalize(cameraPos - position_world.xyz);
	float spec = pow(max(0.0, dot(camDir, reflect(-lightDir, N))), material.shininess);
	vec3 specular = material.shininessStrength * material.specularColor * light.specularColor * spec;
	specular = vec3(0);

	float visibility = 1.0;
	/*if ( texture( shadowTexture, shadCoord.xy ).z  <  shadCoord.z - 0.005){
		visibility = 0.5;
	}*/

	return visibility * attenuation * (diffuse + specular);
}