
#include "anyrenderer_global.h"
#include "Array.h"

namespace AnyRenderer {

	VI_OBJECT_META_IMPL(Array, DataBuffer);

	Array::~Array() {

	}

	void Array::onBind(State& state) {
		glBindBuffer(GL_ARRAY_BUFFER, getId(state));
	}

	void Array::onUnbind(State& state) {
		GLint current_id = 0;
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &current_id);
		if (current_id == getId(state))
			glBindTexture(GL_ARRAY_BUFFER, 0);
	}

	void Array::onRelease(State& state) {
		auto id = getId(state);
		glDeleteBuffers(1, &id);
	}

	DataBuffer::Target Array::getTarget() const
	{
		return TARGET_ARRAY_BUFFER;
	}

	DataBuffer::Usage Array::getUsage() const
	{
		return USAGE_STREAM_DRAW;
	}

	bool Array::isEmpty() const {
		return getSize() == 0;
	}
}