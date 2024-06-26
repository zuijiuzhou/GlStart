#pragma once

#include "PixelBuffer.h"

namespace AnyRenderer {

	class FrameBufferObject;

	class RenderBuffer : public PixelBuffer {

		VI_OBJECT_META;

		friend class FrameBufferObject;

	public:
		RenderBuffer();

		FrameBufferObject* getFrameBuffer() const;

	protected:
		virtual bool onUpdate(State& state) override;

		virtual void onBind(State& state) override;

		virtual void onUnbind(State& state) override;

	private:
		VI_OBJECT_DATA;
	};
}