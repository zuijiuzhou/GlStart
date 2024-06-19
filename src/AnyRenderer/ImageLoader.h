#pragma once
#include <string>
#include <vector>

namespace AnyRenderer{

class Model;
class ImageLoader {
public:
    Model* loadFile(const std::string& file);
    
    static bool isSupported(const std::string& file);
};
}