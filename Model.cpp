#include "Model.h"

Model::Model(float *vertices, float *colors, int size) : size(size), vbo(0), colorsVbo(1) {
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
