#include "ShadowRenderer.h"
#include "Scene/NodeList.h"
#include "Scene/Lights/DirectionalLight.h"
#include "Scene.h"

ShadowResult ShadowRenderer::render(RenderContext &context, Scene *root) {
	context.setStage(RenderStage::Shadow);

	ShadowResult result;
	result.texture = &depthBuffer->getTexture();

	DirectionalLight* light = (DirectionalLight *) root->getRootNode().getLight(5);
	float m = 20;
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-1*m,1*m,-1*m,1*m,-10,100);
	glm::mat4 depthViewMatrix = glm::lookAt(light->getWorldPosition(), light->getWorldPosition() + light->getDir(), glm::vec3(0,1,0));
	result.depthMVP = depthProjectionMatrix * depthViewMatrix;

	{
		auto buffer = depthBuffer->activate();

		program.use();
		program.send("depthMVP", result.depthMVP);
		glViewport(0, 0, 1024, 1024);

		context.clearColor(0, 0, 0, 0);
		context.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.send("modelMatrix", root->getTerrain()->getTransform().getTransform());
		root->getTerrain()->drawShadows(*root);
		root->getRootNode().render(context);
	}

	return result;
}