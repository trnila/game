#include <fstream>
#include <vector>
#include <sstream>
#include "Model.h"

Model::Model(const char *name, float *vertices, float *colors, int size) : size(size), vbo(0), colorsVbo(1) {
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
	context.drawArrays(GL_TRIANGLES, 0, size);
}

Model::Model(const char *path) : vbo(0), colorsVbo(1) {
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
			int g;
			//sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &x, &g, &y, &g, &z, &g);
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
