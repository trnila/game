#include <fstream>
#include <vector>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"

struct __attribute__((__packed__)) Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
};

Model::Model(const char *name, float *vertices, int size) : vbo(0), colorsVbo(1), size(size) {
	vao.bind();

	vbo.bind();
	vbo.setData(vertices, size, 3, 0);
	glBufferData(GL_ARRAY_BUFFER, 6*size*sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	vao.enableAttrib(0);
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

	if(!m->mNormals) {
		printf("obj %s has no normals!\n", path);
	}

	vao.bind();

	vbo.bind();

	std::vector<Vertex> vertices;
	for(int i = 0; i < m->mNumVertices; i++) {
		Vertex vert;
		vert.pos = glm::vec3(m->mVertices[i].x, m->mVertices[i].y, m->mVertices[i].z);

		if(m->mNormals) {
			vert.normal = glm::vec3(m->mNormals[i].x, m->mNormals[i].y, m->mNormals[i].z);
		}
		vertices.push_back(vert);
	}

	vbo.setData(vertices.data(), vertices.size(), 3, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(vertices[0].pos));

	vao.enableAttrib(0);
	vao.enableAttrib(1);

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
