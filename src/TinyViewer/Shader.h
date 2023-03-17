#ifndef _SHADER_H_
#define _SHADER_H_

#include <iostream>
#include <gl/glew.h>
#include <string>
#include <sstream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




namespace TinyViewer
{
     class Shader
     {
     private:
          unsigned int m_glProgramId = 0;

     private:
     unsigned int createShader(const GLchar* path, int type);

     public:
          Shader(const GLchar* vs_path, const GLchar* fs_path);
          virtual ~Shader();

          void use();
          void unuse();

          template <typename T>
          void set(const GLchar *szName, const T &val)
          {
               if constexpr (std::is_same<T, bool>::value)
               {
                    glUniformli(glGetUniformLocation(m_glProgramId), szName, (int)val);
               }
               else if constexpr (std::is_same<T, int>::value)
               {
                    glUniformli(glGetUniformLocation(m_glProgramId), szName, val);
               }
               else if constexpr (std::is_same<T, float>::value)
               {
                    glUniformlf(glGetUniformLocation(m_glProgramId), szName, val);
               }
               else if constexpr (std::is_same<T, glm::vec3>::value)
               {
                    glUniform3f(glGetUniformLocation(m_glProgramId, szName), val.x, val.y, val.z);
               }
               else if constexpr (std::is_same<T, glm::mat4>::value)
               {
                    glUniformMatrix4fv(glGetUniformLocation(m_glProgramId, szName), 1, GL_FALSE, glm::value_ptr(val));
               }
               else
               {
                    static_assert("type not supported");
               }
        }
     };
}
#endif