#include "MeshShape.h"
#include "Shader.h"

using namespace TinyViewer;

MeshShape::MeshShape()
{
}

MeshShape::~MeshShape()
{
    if (vao_)
    {
        glDeleteVertexArrays(1, &vao_);
    }
    if (vbos_)
    {
        glDeleteBuffers(2, vbos_);
    }
}

void MeshShape::setData(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals)
{
    vertices_ = std::move(vertices);
    normals_ = std::move(normals);
}

void MeshShape::draw()
{
#ifdef __GL_FIXED_PIPLINE__
    // glBegin(GL_TRIANGLES);
    // glColor3f(1.0, 0.0, 0.0);
    // glVertex3f(1.0, 0.0, 0.0);
    // glColor3f(0.0, 1.0, 0.0);
    // glVertex3f(-1.0, -1.0, 0.0);
    // glColor3f(0.0, 0.0, 1.0);
    // glVertex3f(1.0, -1.0, 0.0);
    // glEnd();
#else
    if (vao_ == 0)
    {
        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);
        glGenBuffers(2, vbos_);
        glBindBuffer(GL_ARRAY_BUFFER, vbos_[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3), (void *)vertices_.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
        glBindBuffer(GL_ARRAY_BUFFER, vbos_[1]);
        glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(glm::vec3), (void *)normals_.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else
    {
        glBindVertexArray(vao_);
        glEnableVertexAttribArray(0);    
        glEnableVertexAttribArray(1);
    }    
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()));
    glBindVertexArray(0);

#endif
}

void MeshShape::setColor(const glm::vec4 &color)
{
    color_ = color;
}

glm::vec4 MeshShape::getColor() const{
    return color_;
}