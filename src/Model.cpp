#include <fstream>
#include <vector>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"
#include "Formatter.h"

Model::Model(const char *name, float *vertices, int size) {
	/*auto vao = this->vao.activate();
	auto vbo = this->vbo.activate();

	vbo.setData(vertices, size, 3);
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, 6*size*sizeof(float), vertices, GL_STATIC_DRAW));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0));
	vao.enableAttrib(0);*/
}

void Model::render(RenderContext &context) {
	for(Mesh* mesh: meshes) {
		mesh->render(context);
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
		meshes.push_back(new Mesh(*scene->mMeshes[i]));
	}
}