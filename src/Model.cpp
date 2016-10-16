#include <fstream>
#include <vector>
#include <sstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"
#include "Formatter.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 uv;
};

Model::Model(const char *name, float *vertices, int size) : vbo(), colorsVbo(), size(size) {
	vao.bind();

	auto vbo = this->vbo.activate();


	vbo.setData(vertices, size, 3);
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

Model::Model(const char *path) : vbo(), colorsVbo() {
	Assimp::Importer importer;

	int conf =
			  aiProcess_GenSmoothNormals
			| aiProcess_FlipUVs
			| aiProcess_CalcTangentSpace
			| aiProcess_Triangulate
			| aiProcess_JoinIdenticalVertices
			| aiProcess_SortByPType;

	const aiScene* scene = importer.ReadFile(path, conf);

	if(!scene) {
		throw std::runtime_error(Formatter() << "Could not load model: " << path);
	}

	aiMesh* m = scene->mMeshes[0];

	if(!m->mNormals) {
		printf("model %s has no normals!\n", path);
	}

	if(!m->HasTextureCoords(0)) {
		printf("model %s has no normals!\n", path);
	}

	std::vector<Vertex> vertices;
	for(int i = 0; i < m->mNumVertices; i++) {
		Vertex vert;
		vert.pos = glm::vec3(m->mVertices[i].x, m->mVertices[i].y, m->mVertices[i].z);

		if(m->mNormals) {
			vert.normal = glm::vec3(m->mNormals[i].x, m->mNormals[i].y, m->mNormals[i].z);
		} else {
			vert.normal = glm::vec3(0,0,0);
		}

		if(m->HasTextureCoords(0)) {
			vert.uv = glm::vec2(m->mTextureCoords[0][i].x, m->mTextureCoords[0][i].y);
		} else {
			vert.uv = glm::vec2(0, 0);
		}

		vertices.push_back(vert);
	}
	vao.bind();
	auto vbo = this->vbo.activate();
	vbo.setData(vertices.data(), vertices.size() + 10, 1); //TODO: fixme
	vbo.setPointer<Vertex>(0, 0);
	vbo.setPointer<Vertex>(1, sizeof(vertices[0].pos));
	vbo.setPointer<Vertex>(2, sizeof(vertices[0].pos) + sizeof(vertices[0].normal));

	vao.enableAttrib(0);
	vao.enableAttrib(1);
	vao.enableAttrib(2);

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

	if(scene->mNumMaterials >= 1) {
		//aiMaterial *mat = scene->mMaterials[0]
	}
}
