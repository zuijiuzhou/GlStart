#include "ImageLoader.h"

#include <filesystem>
#include <set>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Image.h"

namespace AnyRenderer {

	struct ImageLoader::Data {
		bool filp_v = false;
	};

	bool ImageLoader::isSupported(const std::string& file)
	{
		namespace fs = std::filesystem;
		fs::path path(file);
		if (!path.has_extension())
			return false;
		auto file_ext = path.extension().string();
		static std::set<std::string> exts = { ".jpg", ".png" };
		return exts.contains(file_ext);
	}

	ImageLoader::ImageLoader()
		:d(new Data())
	{
	}

	Image* ImageLoader::loadFile(const std::string& file)
	{
		int w, h, channels;
		stbi_set_flip_vertically_on_load(d->filp_v);
		auto data = stbi_load(file.data(), &w, &h, &channels, 0);
		if (data) {
			auto fmt = Image::EMPTY;
			if (channels == 1)
				fmt = Image::R8;
			else if (channels == 3)
				fmt = Image::RGB888;
			else if (channels == 4)
				fmt = Image::RGBA8888;

			if (fmt == Image::EMPTY)
				return nullptr;

			auto img = new Image();
			img->setImage(w, h, fmt, data);
			stbi_image_free(data);
			return img;
		}

		return nullptr;
	}

	void ImageLoader::setFlipVertically(bool val)
	{
		d->filp_v = val;
	}

}