#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLObject.h"

namespace AnyRenderer
{
     class Shader : public GLObject
     {
     public:
          Shader(const std::string& vs_code, const std::string& gs_code, const std::string& fs_code);
          virtual ~Shader();

     public:
          void use();
          void unuse();

          std::string getName() const;
          void setName(const std::string& name);

          template <typename T>
          void set(const GLchar *name, const T &val)
          {
               auto id = getId();
               if constexpr (std::is_same<T, bool>::value)
               {
                    auto loc = glGetUniformLocation(id, name);
                    if(loc >= 0) glUniform1i(loc, (int)val);
               }
               else if constexpr (std::is_same<T, int>::value)
               {
                    auto loc = glGetUniformLocation(id, name);
                    if(loc >= 0) glUniform1i(loc, val);
               }
               else if constexpr (std::is_same<T, float>::value)
               {
                    auto loc = glGetUniformLocation(id, name);
                    if(loc >= 0) glUniform1f(loc, val);
               }
               else if constexpr (std::is_same<T, glm::vec3>::value)
               {
                    auto loc = glGetUniformLocation(id, name);
                    if(loc >= 0) glUniform3f(loc, val.x, val.y, val.z);
               }               
               else if constexpr (std::is_same<T, glm::vec4>::value)
               {
                    auto loc = glGetUniformLocation(id, name);
                    if(loc >= 0) glUniform4f(loc, val.r, val.g, val.b, val.a);
               }
               else if constexpr (std::is_same<T, glm::mat4>::value)
               {
                    auto loc = glGetUniformLocation(id, name);
                    if(loc >= 0) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
               }
               else
               {
                    static_assert("type not supported");
               }
          }

     public:
          static Shader *create(const std::string& vs_path, const std::string& gs_path, const std::string& fs_path);

     protected:
          GLuint onCreate();

     private:
          std::string name_;
          std::string vs_code_ = nullptr;
          std::string gs_code_ = nullptr;
          std::string fs_code_ = nullptr;
     };
}