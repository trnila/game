#include "Panel.h"
#include "../Utils/ResourceManager.h"

Panel::Panel() {
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/panel.v.glsl", GL_VERTEX_SHADER));
	prog.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/panel.f.glsl", GL_FRAGMENT_SHADER));
	prog.link();

	auto vbo = this->vbo.activate();
	float data[] = {
			-1, 1,
	        1, 1,
	        -1, -1,

	        1, 1,
	        1, -1,
	        -1, -1
	};


	auto lock = this->vbo.activate();
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));
}

void Panel::render() {
	prog.use();
	prog.useTexture("myTexture", *texture, 0);
	prog.send("scale", glm::vec2(0.25, 0.25));
	auto data = glm::vec2(-0.75, -0.75);
	prog.send("translate", data);

	auto lock = this->vbo.activate();
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}
