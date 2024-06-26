#pragma once

namespace AnyRenderer {
	struct GLVersionInfo {
		int major;
		int minor;

		bool glslSupported;
		bool fboSupported;
		bool drawBuffersSupported;

		bool npotSupported;
	};

	bool queryGLVersion(GLVersionInfo& vi);
}