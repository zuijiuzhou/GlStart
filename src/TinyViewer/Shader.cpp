#include "Shader.h"
#include <fstream>

using namespace TinyViewer;

Shader::Shader(const GLchar* vs_path, const GLchar* fs_path)
{
    unsigned int vs_id, fs_id;
    int status;
    char msg[512];

    vs_id = createShader(vs_path, GL_VERTEX_SHADER);
    fs_id = createShader(fs_path, GL_FRAGMENT_SHADER);

    unsigned int app_id = glCreateProgram();
    glAttachShader(app_id, vs_id);
    glAttachShader(app_id, fs_id);
    glLinkProgram(app_id);
    glGetProgramiv(app_id, GL_LINK_STATUS, &status);

    if( 0== status)
    {
        glGetProgramInfoLog(app_id, sizeof(msg), NULL, msg);
        std::cerr << "ERROR: failed to link the shaders"  << msg << std::endl;
    }
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);
    m_glProgramId = app_id;
}

   unsigned int Shader::createShader(const GLchar* path, int type)
   {
    std::string shader_str;
    std::ifstream shader_fs;

    shader_fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shader_fs.open(shader_str);

        std::stringstream shader_ss;
        shader_ss << shader_fs.rdbuf();

        shader_fs.close();

        shader_str = shader_ss.str();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    const char* shader_sz = shader_str.data();
    
    unsigned int shader_id;
    shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &shader_sz, NULL);
    glCompileShader(shader_id);

    int  status;
    char msg[512];

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
    if(0 == status){
        glGetShaderInfoLog(shader_id, sizeof(msg), NULL, msg);
        std::cerr << "ERROR: failed to compile the shader" << msg << std::endl;
        return;
    }
   }