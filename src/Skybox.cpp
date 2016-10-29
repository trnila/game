#include "Skybox.h"
#include "ResourceManager.h"
#include "utils.h"
#include "stb_image.h"

GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
};

Skybox::Skybox() {
	program.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/skybox.v.glsl", GL_VERTEX_SHADER));
	program.attach(ResourceManager<Shader>::getInstance().getResource<>("resources/shaders/skybox.f.glsl", GL_FRAGMENT_SHADER));
	program.link();

	program.use();
	GL_CHECK(glGenTextures(1, &textureID));
	GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));

	std::vector<const GLchar*> faces;
	faces.push_back("resources/skyboxes/ely_hills/hills_rt.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_lf.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_up.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_dn.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_bk.tga");
	faces.push_back("resources/skyboxes/ely_hills/hills_ft.tga");


	int width,height;
	unsigned char* image;
	for(GLuint i = 0; i < faces.size(); i++)
	{
		int x,y,n;
		image = stbi_load(faces[i], &width, &height, &n, 3);
		if(!image) {
			throw std::runtime_error("ff");
		}
		GL_CHECK(glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
		));
	}

	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));


	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

}

void Skybox::render(Camera camera) {
	program.use();
	GL_CHECK(glDepthMask(GL_FALSE));
	//TODO: ... Set view and projection matrix
	glm::mat4 view = glm::mat4(glm::mat3(camera.getTransform()));
	program.setMatrix("viewMatrix", view);
	program.setMatrix("projectionMatrix", camera.getPerspective());

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(program.id, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 36));
	GL_CHECK(glDepthMask(GL_TRUE));

}
