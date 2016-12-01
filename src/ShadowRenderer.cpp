#include "ShadowRenderer.h"
#include "Scene/NodeList.h"
#include "Scene/Lights/DirectionalLight.h"
#include "Scene.h"

Texture & ShadowRenderer::render(RenderContext &context, Scene *root, glm::mat4 &depthMVP) {
	context.setStage(RenderStage::Shadow);

	DirectionalLight* light = (DirectionalLight *) root->getRootNode().getLight(5);
	float m = 20;
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-1*m,1*m,-1*m,1*m,-1,100);
	glm::mat4 depthViewMatrix = glm::lookAt(light->getWorldPosition(), light->getDir(), glm::vec3(0,1,0));
	depthMVP = depthProjectionMatrix * depthViewMatrix;

	{
		auto buffer = depthBuffer->activate();

		program.use();
		program.send("depthMVP", depthMVP);
		glViewport(0, 0, 1024, 1024);

		context.clearColor(0, 0, 0, 0);
		context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		root->getRootNode().render(context);
	}

	return depthBuffer->getTexture();
}
