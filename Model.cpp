#include "Model.h"

Model::Model(float *vertices, float *colors, int size) : size(size) {
	vao.bind();
	vao.enableAttrib(0);

	vbo.bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	vbo.setData((const char*) vertices, size * 3 * sizeof(float));

	colorsVbo.bind();
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	colorsVbo.setData((const char*) colors, size * 3 * sizeof(float));
	glEnableVertexAttribArray(1);
}

void Model::render() {
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, size);
}
