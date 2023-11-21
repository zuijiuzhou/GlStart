#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace TinyViewer;

namespace{
    std::string readCode(const GLchar* path){
        std::string code;
        std::ifstream fs;

        fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            fs.open(path);
            std::stringstream ss;
            ss << fs.rdbuf();
            fs.close();
            code = ss.str();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return code;
    }
}

Shader::Shader(const GLchar *vs_code, const GLchar *fs_code)
{
    unsigned int vs_id, fs_id;
    int status;
    char msg[512];

    vs_id = createShader(vs_code, GL_VERTEX_SHADER);
    fs_id = createShader(fs_code, GL_FRAGMENT_SHADER);

    unsigned int app_id = glCreateProgram();
    glAttachShader(app_id, vs_id);
    glAttachShader(app_id, fs_id);
    glLinkProgram(app_id);
    glGetProgramiv(app_id, GL_LINK_STATUS, &status);

    if (0 == status)
    {
        glGetProgramInfoLog(app_id, sizeof(msg), NULL, msg);
        std::cerr << "ERROR: failed to link the shaders" << msg << std::endl;
        throw std::exception("Link shaders failed.");
    }
    glDetachShader(app_id, vs_id);
    glDeleteShader(vs_id);
    glDetachShader(app_id, fs_id);
    glDeleteShader(fs_id);
    program_id_ = app_id;
}

Shader::~Shader()
{
    if (program_id_)
    {
        glDeleteProgram(program_id_);
    }
}

void Shader::use()
{
    glUseProgram(program_id_);
}

void Shader::unuse()
{
    glUseProgram(0);
}

unsigned int Shader::createShader(const GLchar *code, int type)
{
    unsigned int shader_id;
    shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &code, NULL);
    glCompileShader(shader_id);

    int status;
    char msg[512];

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
    if (0 == status)
    {
        glGetShaderInfoLog(shader_id, sizeof(msg), NULL, msg);
        std::cerr << "ERROR: failed to compile the shader" << msg << std::endl;
        throw std::exception("Compile shader failed.");
    }
    return shader_id;
}

Shader *Shader::create(const GLchar *vs_path, const GLchar *fs_path){
    auto vs_code = readCode(vs_path);
    auto fs_code = readCode(fs_path);
    return new Shader(vs_code.data(), fs_code.data());
}