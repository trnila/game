#include <fstream>
#include <vector>
#include <sstream>
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
		return;
	}

	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

	//context.drawArrays(GL_TRIANGLES, 0, size);
}

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>

Model::Model(const char *path) : vbo(0), colorsVbo(1) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile( path,
	                                          aiProcess_CalcTangentSpace       |
	                                          aiProcess_Triangulate            |
	                                          aiProcess_JoinIdenticalVertices  |
	                                          aiProcess_SortByPType);

	if(!scene) {
		printf("failed");
	}

	aiMesh* m = scene->mMeshes[0];

	vao.bind();

	vbo.bind();
	vbo.setData(m->mVertices, m->mNumVertices, 3);

	vao.enableAttrib(0);

	//colorsVbo.bind();
	//colorsVbo.setData(m->mFaces->mIndices, m->mFaces->mNumIndices, 1);


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


	return;

	std::vector<float> verts, data;
	std::ifstream in(path);
	if (!in.is_open()) {
		throw std::runtime_error("Could not open resource");
	}

	std::string line;
	while (std::getline(in, line)) {
		if (line[0] == 'v') {
			float x, y, z;
			std::istringstream is(line.substr(2));
			is >> x >> y >> z;

			verts.push_back(x);
			verts.push_back(y);
			verts.push_back(z);
		} else if (line[0] == 'f') {
			int x, y, z;
			sscanf(line.c_str(), "f %d %d %d", &x, &y, &z);

			data.push_back(verts[3 * (x - 1)]);
			data.push_back(verts[3 * (x - 1) + 1]);
			data.push_back(verts[3 * (x - 1) + 2]);

			data.push_back(verts[3 * (y - 1)]);
			data.push_back(verts[3 * (y - 1) + 1]);
			data.push_back(verts[3 * (y - 1) + 2]);

			data.push_back(verts[3 * (z - 1)]);
			data.push_back(verts[3 * (z - 1) + 1]);
			data.push_back(verts[3 * (z - 1) + 2]);
		}
	}

	vao.bind();

	vbo.bind();
	vbo.setData(data.data(), data.size() / 3, 3);

	vao.enableAttrib(0);

	this->size = data.size() / 3;
}
