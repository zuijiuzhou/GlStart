#pragma once
#include <string>
#include <vector>

namespace AnyRenderer {

	class Image;
	class Model;
	class ImageLoader {

	public:
		ImageLoader();

	public:
		/**
		 * @brief
		 * @param file
		 * @return Maybe return nullptr.
		 */
		Image* loadFile(const std::string& file);

		void setFlipVertically(bool val);

	public:
		static bool isSupported(const std::string& file);

	private:
		struct Data;
		Data* const d;

	};
} // namespace AnyRenderer