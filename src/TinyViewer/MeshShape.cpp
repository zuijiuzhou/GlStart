#include "MeshShape.h"
#include "Shader.h"

using namespace TinyViewer;

MeshShape::MeshShape()
{
}
MeshShape::~MeshShape()
{
    if(m_vao_id){
        glDeleteVertexArrays(1, &m_vao_id);
    }
    if(m_vbo_id)
    {
        glDeleteBuffers(1, &m_vbo_id);
    }
}

void MeshShape::setData(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors)
{
    m_vertices = std::move(vertices);
    m_colors = std::move(colors);
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
    if (m_vao_id == 0)
    {
        glGenVertexArrays(1, &m_vao_id);
        glBindVertexArray(m_vao_id);

        glGenBuffers(1, &m_vbo_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices.size()), (void *)m_vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const GLvoid *)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
    }
    else
    {
        glBindVertexArray(m_vao_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
    }
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertices.size() / 3));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

#endif
}