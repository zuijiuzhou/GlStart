#pragma once
#include <string>
#include <vector>

namespace AnyRenderer{

class Group;
class MeshLoader{
public:
    Group* loadFile(const std::string& file);
    
    static bool isSupported(const std::string& file);
};
}