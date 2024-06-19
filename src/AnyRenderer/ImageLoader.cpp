#include "ImageLoader.h"

#include <filesystem>
#include <stb_image.h>

#include "Texture2D.h"
#include "Geometry.h"
#include "Model.h"

namespace AnyRenderer
{
    bool ImageLoader::isSupported(const std::string &file)
    {
        namespace fs = std::filesystem;
        fs::path path(file);
        if (!path.has_extension())
            return false;
        auto file_ext = path.extension().string();
        static std::set<std::string> exts = {".jpg", ".png"};
        return exts.contains(file_ext);
    }

    Model * ImageLoader::loadFile(const std::string &file)
    {
        auto root = new Model();

        auto tex = new Texture2D();
        tex->setImage(file);
        
        

        //stbi_image_free(data);
        return root;
    }
}