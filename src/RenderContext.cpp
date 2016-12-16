#include "Graphics/Program.h"
#include "ShadowRenderer.h"

void RenderContext::applyShadows(Program &program) {
	if(stage == RenderStage::Normal) {
		result->apply(program);
	}
}

