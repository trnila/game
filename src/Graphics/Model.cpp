#include <fstream>
#include <vector>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"
#include "../Utils/Formatter.h"

Model::Model(const char *name, float *vertices, int size) {


	/*auto vao = this->vao.activate();
	auto vbo = this->vbo.activate();

	vbo.setData(vertices, size, 3);
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, 6*size*sizeof(float), vertices, GL_STATIC_DRAW));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0));
	vao.enableAttrib(0);*/
}

void Model::render(RenderContext &context, Program &program) {
	for(Mesh* mesh: meshes) {
		mesh->render(context, program);
	}
}

Model::Model(const char *path) {
	Assimp::Importer importer;

	int conf =
			  aiProcess_GenSmoothNormals
			  | aiProcess_FlipUVs
			  | aiProcess_CalcTangentSpace
			  | aiProcess_PreTransformVertices
			  | aiProcess_Triangulate
			  | aiProcess_JoinIdenticalVertices
			  | aiProcess_SortByPType;

	const aiScene* scene = importer.ReadFile(path, conf);

	if(!scene) {
		throw std::runtime_error(Formatter() << "Could not load model: " << path);
	}

	for(int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		aiMaterial* material = nullptr;
		if(mesh->mMaterialIndex >= 0) {
			material = scene->mMaterials[mesh->mMaterialIndex];
		}

		std::string base = path;
		std::string::size_type pos = base.rfind('/');
		if(pos != std::string::npos) {
			base = std::string(path).substr(0, pos);
		}

		meshes.push_back(new Mesh(*mesh, material, std::string(base)));
	}
}

Model::~Model() {
	for(Mesh* i: meshes) {
		delete i;
	}
}
