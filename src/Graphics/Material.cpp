#include "../Utils/ResourceManager.h"
#include "Mesh.h"
#include "Texture.h"

void Material::apply(Program &program) const {
	program.send("material.ambientColor", ambientColor);
	program.send("material.diffuseColor", diffuseColor);
	program.send("material.specularColor", specularColor);
	program.send("material.shininess", shininess);
	program.send("material.shininessStrength", shininessStrength);

	if(texture) {
		program.useTexture("modelTexture", *texture, 0);
		program.send("hasTexture", true);
	} else {
		program.send("hasTexture", false);
	}

	if(bumpTexture) {
		program.useTexture("bumpTexture", *bumpTexture, 2);
	}
}

void Material::createMaterial(const aiMaterial *material, const std::string &path) {
	aiColor3D c;
	if(material->Get(AI_MATKEY_COLOR_AMBIENT, c) == AI_SUCCESS) {
		ambientColor = Color(c.r, c.g, c.b);
	}

	if(material->Get(AI_MATKEY_COLOR_DIFFUSE, c) == AI_SUCCESS) {
		diffuseColor = Color(c.r, c.g, c.b);
	}

	if(material->Get(AI_MATKEY_COLOR_SPECULAR, c) == AI_SUCCESS) {
		specularColor = Color(c.r, c.g, c.b);
	}

	float n;
	if(material->Get(AI_MATKEY_SHININESS, n) == AI_SUCCESS && n != 0) {
		shininess = n;
	}

	if(material->Get(AI_MATKEY_SHININESS_STRENGTH, n) == AI_SUCCESS) {
		shininessStrength = n;
	}

	aiString str;
	if(material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), str) == AI_SUCCESS) {
		ResourceManager<Texture> &textures = ResourceManager<Texture>::getInstance();
		texture = &textures.getResource((path + "/" + std::string(str.C_Str())).c_str());
	}

	str = "";
	if(material->Get(AI_MATKEY_TEXTURE(aiTextureType_HEIGHT, 0), str) == AI_SUCCESS) {
		ResourceManager<Texture> &textures = ResourceManager<Texture>::getInstance();
		bumpTexture = &textures.getResource((path + "/" + std::string(str.C_Str())).c_str());
	}
}