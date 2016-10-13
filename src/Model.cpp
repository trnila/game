#include <fstream>
#include <vector>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"

Model::Model(const char *name, float *vertices, float *colors, int size) : vbo(0), colorsVbo(1), size(size) {
	vao.bind();

	vbo.bind();
	vbo.setData(vertices, size, 3);

	colorsVbo.bind();
	colorsVbo.setData(colors, size, 3);

	vao.enableAttrib(0);
	vao.enableAttrib(1);
}

void Model::render(RenderContext &context) {
	context.bind(vao);

	if(ibo == 0) {
		context.drawArrays(GL_TRIANGLES, 0, size);
	} else {
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	}
}

Model::Model(const char *path) : vbo(0), colorsVbo(1) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	if(!scene) {
		throw std::runtime_error("Could not load model");
	}

	aiMesh* m = scene->mMeshes[0];

	vao.bind();

	vbo.bind();
	vbo.setData(m->mVertices, m->mNumVertices, 3);

	vao.enableAttrib(0);

	std::vector<int> index;
	for(unsigned int i = 0; i < m->mNumFaces; i++) {
		aiFace& face = m->mFaces[i];
		index.push_back(face.mIndices[0]);
		index.push_back(face.mIndices[1]);
		index.push_back(face.mIndices[2]);
	}

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(int), index.data(), GL_STATIC_DRAW);

	size = index.size();
}
