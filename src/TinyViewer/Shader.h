#pragma once
#include "tinyviewer_global.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace TinyViewer
{
     class Shader
     {
     private:
          unsigned int program_id_ = 0;

     public:
          Shader(const GLchar *vs_code, const GLchar* gs_code, const GLchar *fs_code);
          virtual ~Shader();

     public:
          void use();
          void unuse();

          template <typename T>
          void set(const GLchar *name, const T &val)
          {
               if constexpr (std::is_same<T, bool>::value)
               {
                    glUniformli(glGetUniformLocation(program_id_, name), (int)val);
               }
               else if constexpr (std::is_same<T, int>::value)
               {
                    glUniformli(glGetUniformLocation(program_id_, name), val);
               }
               else if constexpr (std::is_same<T, float>::value)
               {
                    glUniformlf(glGetUniformLocation(program_id_, name), val);
               }
               else if constexpr (std::is_same<T, glm::vec3>::value)
               {
                    glUniform3f(glGetUniformLocation(program_id_, name), val.x, val.y, val.z);
               }               
               else if constexpr (std::is_same<T, glm::vec4>::value)
               {
                    glUniform4f(glGetUniformLocation(program_id_, name), val.r, val.g, val.b, val.a);
               }
               else if constexpr (std::is_same<T, glm::mat4>::value)
               {
                    glUniformMatrix4fv(glGetUniformLocation(program_id_, name), 1, GL_FALSE, glm::value_ptr(val));
               }
               else
               {
                    static_assert("type not supported");
               }
          }

     public:
          static Shader *create(const GLchar *vs_path, const GLchar* gs_path, const GLchar *fs_path);
     };
}