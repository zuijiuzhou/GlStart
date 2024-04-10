#include "PointCloud.h"
#include "Shader.h"
#include "ResourceManager.h"

namespace AnyRenderer
{
    PointCloud::PointCloud()
    {
    }

    PointCloud::~PointCloud()
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

    void PointCloud::setData(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors)
    {
        vertices_ = std::move(vertices);
        colors_ = std::move(colors);
    }

    Shader *PointCloud::getShader() const
    {
        auto shader = Shape::getShader();
        if (!shader)
            shader = ResourceManager::instance()->getInternalShader(ResourceManager::IS_PointCloud);
        return shader;
    }

    void PointCloud::draw(const RenderContext &ctx)
    {
        glEnable(GL_PROGRAM_POINT_SIZE);
        glEnable(GL_BLEND);
        glEnable(GL_POINT_SMOOTH);
        static GLfloat x = 0.2f;
        glPointParameterfv(GL_POINT_FADE_THRESHOLD_SIZE, &x);
        if (vao_ == 0)
        {
            glGenVertexArrays(1, &vao_);
            glBindVertexArray(vao_);
            glGenBuffers(2, vbos_);
            glBindBuffer(GL_ARRAY_BUFFER, vbos_[0]);
            glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3), (void *)vertices_.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
            glBindBuffer(GL_ARRAY_BUFFER, vbos_[1]);
            glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(glm::vec3), (void *)colors_.data(), GL_STATIC_DRAW);
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
        glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(vertices_.size()));
        glBindVertexArray(0);
    }
}