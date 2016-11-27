#include "ShadowRenderer.h"
#include "Scene/NodeList.h"

Texture & ShadowRenderer::render(RenderContext &context, NodeList &root, glm::mat4 &depthMVP) {
	context.setStage(RenderStage::Shadow);

	BaseLight* light = root.getLight(0);
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -20, 60);
	glm::mat4 depthViewMatrix = glm::lookAt(light->getWorldPosition(), light->getDirection(), glm::vec3(0,1,0));
	depthMVP = depthProjectionMatrix * depthViewMatrix;

	{
		auto buffer = depthBuffer->activate();

		program.send("depthMVP", depthMVP);

		context.clearColor(0, 0, 0, 0);
		context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();
		root.render(context);
	}

	return depthBuffer->getTexture();
}
