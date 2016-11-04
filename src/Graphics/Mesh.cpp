#include <assimp/material.h>
#include "Mesh.h"
#include "../Utils/ResourceManager.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 uv;
};

void Mesh::render(RenderContext &context, Program &program) {
	material.apply(program);

	auto vao = this->vao.activate();
	GL_CHECK(glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0));
}

Mesh::Mesh(aiMesh &mesh, aiMaterial *material, std::string path) {
	std::vector<Vertex> vertices;
	for(int i = 0; i < mesh.mNumVertices; i++) {
		Vertex vert;
		vert.pos = glm::vec3(mesh.mVertices[i].x, mesh.mVertices[i].y, mesh.mVertices[i].z);

		if(mesh.mNormals) {
			vert.normal = glm::vec3(mesh.mNormals[i].x, mesh.mNormals[i].y, mesh.mNormals[i].z);
		} else {
			vert.normal = glm::vec3(0,0,0);
		}

		if(mesh.HasTextureCoords(0)) {
			vert.uv = glm::vec2(mesh.mTextureCoords[0][i].x, mesh.mTextureCoords[0][i].y);
		} else {
			vert.uv = glm::vec2(0, 0);
		}

		vertices.push_back(vert);
	}

	auto vao = this->vao.activate();
	auto vbo = this->vbo.activate();
	vbo.setData(vertices.data(), vertices.size() + 10, 1); //TODO: fixme
	vbo.setPointer<Vertex>(0, 0);
	vbo.setPointer<Vertex>(1, sizeof(vertices[0].pos));
	vbo.setPointer<Vertex>(2, sizeof(vertices[0].pos) + sizeof(vertices[0].normal));

	vao.enableAttrib(0);
	vao.enableAttrib(1);
	vao.enableAttrib(2);

	std::vector<unsigned int> index;
	for(unsigned int i = 0; i < mesh.mNumFaces; i++) {
		aiFace& face = mesh.mFaces[i];
		index.push_back(face.mIndices[0]);
		index.push_back(face.mIndices[1]);
		index.push_back(face.mIndices[2]);
	}

	GL_CHECK(glGenBuffers(1, &ibo));
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW));

	size = index.size();

	if(material) {
		this->material.createMaterial(material, path);
	}
}

