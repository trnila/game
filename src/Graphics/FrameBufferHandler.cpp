#include "FrameBufferHandler.h"
#include "FrameBuffer.h"

unsigned int FrameBufferHandler::getId() {
	return this->obj.depthTexture;
}

FrameBufferHandler::FrameBufferHandler(FrameBuffer &t) : LockImpl(t) {}
