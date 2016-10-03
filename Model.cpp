#include <fstream>
#include <vector>
#include <sstream>
#include "Model.h"

Model::Model(float *vertices, float *colors, int size) : size(size), vbo(0), colorsVbo(1) {
	/*vao.bind();

	vbo.bind();
	vbo.setData(vertices, size, 3);

	colorsVbo.bind();
	colorsVbo.setData(colors, size, 3);

	vao.enableAttrib(0);
	vao.enableAttrib(1);*/

	std::vector<float> verts, indices, my;
	std::ifstream in("monkey.obj");
	std::string line;
	while(std::getline(in, line)) {
		if(line[0] == 'v') {
			float x, y, z;
			std::istringstream is(line.substr(2));
			is >> x >> y >> z;

			verts.push_back(x);
			verts.push_back(y);
			verts.push_back(z);
		} else if(line[0] == 'f') {
			int x, y, z;
			int g;
			//sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &x, &g, &y, &g, &z, &g);
			sscanf(line.c_str(), "f %d %d %d", &x, &y, &z);

			my.push_back(verts[3*(x - 1)]);
			my.push_back(verts[3*(x - 1)+1]);
			my.push_back(verts[3*(x - 1)+2]);

			my.push_back(verts[3*(y - 1)]);
			my.push_back(verts[3*(y - 1)+1]);
			my.push_back(verts[3*(y - 1)+2]);

			my.push_back(verts[3*(z - 1)]);
			my.push_back(verts[3*(z - 1)+1]);
			my.push_back(verts[3*(z - 1)+2]);
		}
	}
	//vao.bind();

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * my.size(), my.data(), GL_STATIC_DRAW);


	/*glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float) * 3, &indices[0], GL_STATIC_DRAW);*/

	this->size = my.size();
}

void Model::render(RenderContext &context) {
	//context.bind(vao);
	//context.drawArrays(GL_TRIANGLES, 0, size);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);
// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, size);
	glDisableVertexAttribArray(0);



/*
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

	// Draw the triangles !
	glDrawElements(
			GL_TRIANGLES,      // mode
			size * 3,    // count
			GL_FLOAT,   // type
			(void*)0           // element array buffer offset
	);*/
}
