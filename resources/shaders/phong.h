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