#pragma once

#include "BindableResource.h"

class FrameBuffer;

class FrameBufferHandler: public LockImpl<FrameBuffer> {

public:
	FrameBufferHandler(FrameBuffer &t);

	unsigned int getId();

	friend class BindableResource<FrameBuffer, FrameBufferHandler>;
};


