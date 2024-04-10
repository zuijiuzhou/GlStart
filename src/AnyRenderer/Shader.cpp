#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace AnyRenderer
{
    namespace
    {
        std::string readCode(const std::string& path)
        {
            if (path.empty())
                return {};
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

        unsigned int createShader(const GLchar *code, int type)
        {
            if (!code || !strlen(code))
                return 0;
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
    }

    Shader::Shader(const std::string& vs_code, const std::string& gs_code, const std::string& fs_code) : vs_code_(vs_code), gs_code_(gs_code), fs_code_(fs_code)
    {
        
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
        if(!isCreated())
            create();
        if(!isCreated())
            return;
        glUseProgram(program_id_);
    }

    void Shader::unuse()
    {
        glUseProgram(0);
    }

    void Shader::create(){
        if(isCreated())
            return;
        unsigned int vs_id, gs_id, fs_id;
        char msg[512];
        auto status = 0;
        auto app_id = glCreateProgram();

        if (!vs_code_.empty())
        {
            vs_id = createShader(vs_code_.data(), GL_VERTEX_SHADER);
            glAttachShader(app_id, vs_id);
        }
        if (!gs_code_.empty())
        {
            gs_id = createShader(gs_code_.data(), GL_GEOMETRY_SHADER);
            glAttachShader(app_id, gs_id);
        }
        if (!fs_code_.empty())
        {
            fs_id = createShader(fs_code_.data(), GL_FRAGMENT_SHADER);
            glAttachShader(app_id, fs_id);
        }
        glLinkProgram(app_id);
        glGetProgramiv(app_id, GL_LINK_STATUS, &status);

        if (0 == status)
        {
            glGetProgramInfoLog(app_id, sizeof(msg), NULL, msg);
            std::cerr << "ERROR: failed to link the shaders" << msg << std::endl;
            throw std::exception("Link shaders failed.");
        }
        if (vs_id)
        {
            glDetachShader(app_id, vs_id);
            glDeleteShader(vs_id);
        }
        if (gs_id)
        {
            glDetachShader(app_id, gs_id);
            glDeleteShader(gs_id);
        }
        if (fs_id)
        {
            glDetachShader(app_id, fs_id);
            glDeleteShader(fs_id);
        }
        program_id_ = app_id;
    }

    bool Shader::isCreated() const{
        return program_id_ > 0;
    }

    Shader *Shader::create(const std::string& vs_path, const std::string& gs_path, const std::string& fs_path)
    {
        auto vs_code = readCode(vs_path);
        auto gs_code = readCode(gs_path);
        auto fs_code = readCode(fs_path);

        if(vs_code.empty() || fs_code.empty())
            return nullptr;

        return new Shader(vs_code, gs_code, fs_code);
    }
}