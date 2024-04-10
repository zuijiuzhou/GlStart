#include "MeshShape.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "Texture.h"

namespace AnyRenderer
{
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

    void MeshShape::setVertices(std::vector<glm::vec3> vertices)
    {
        vertices_ = std::move(vertices);
    }

    void MeshShape::setNormals(std::vector<glm::vec3> normals)
    {
        normals_ = std::move(normals);
    }

    void MeshShape::setIndices(std::vector<glm::u32> indices)
    {
        indices_ = std::move(indices);
    }

    void MeshShape::setColors(std::vector<glm::vec4> colors)
    {
        colors_ = std::move(colors);
    }

    void MeshShape::setTexCoords(std::vector<glm::vec3> coords)
    {
        std::vector<glm::vec2> temp;
        tex_coords_2d_.swap(temp);
        tex_coords_3d_ = std::move(coords);
    }
    void MeshShape::setTexCoords(std::vector<glm::vec2> coords)
    {
        std::vector<glm::vec3> temp;
        tex_coords_3d_.swap(temp);
        tex_coords_2d_ = std::move(coords);
    }
    void MeshShape::setTexture(Texture *tex, unsigned int unit)
    {
        tex_ = tex;
        tex_unit_ = unit;
    }

    void MeshShape::setDrawType(DrawMode type)
    {
        draw_mode_ = type;
    }

    Shader *MeshShape::getShader() const
    {
        auto shader = Shape::getShader();
        if (!shader)
            shader = ResourceManager::instance()->getInternalShader(ResourceManager::IS_MeshShape);
        return shader;
    }

    void MeshShape::draw(const RenderContext &ctx)
    {
        if(vertices_.empty())
            return;

#ifdef __GL2_AVAILABLE
        // glBegin(GL_TRIANGLES);
        // glColor3f(1.0, 0.0, 0.0);
        // glVertex3f(1.0, 0.0, 0.0);
        // glColor3f(0.0, 1.0, 0.0);
        // glVertex3f(-1.0, -1.0, 0.0);
        // glColor3f(0.0, 0.0, 1.0);
        // glVertex3f(1.0, -1.0, 0.0);
        // glEnd();
#else

        auto shader = getShader();
        if (tex_)
        {
            glActiveTexture(tex_unit_);
            tex_->bind();
        }
        if (vao_ == 0)
        {
            glGenVertexArrays(1, &vao_);
            glBindVertexArray(vao_);

            // Vertices
            GLuint vbo_id;
            glGenBuffers(1, &vbo_id);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
            glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3), (void *)vertices_.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
            glEnableVertexAttribArray(0);
            vbos_[0] = vbo_id;

            // Normals
            if(normals_.size() == vertices_.size()){
                glGenBuffers(1, &vbo_id);
                glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
                glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(glm::vec3), (void *)normals_.data(), GL_STATIC_DRAW);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
                glEnableVertexAttribArray(1);
                vbos_[1] = vbo_id;
            }
            else{
                glm::vec3 norm = normals_.empty() ? glm::vec3() : normals_.front();
                glVertexAttrib3f(1, norm.x, norm.y, norm.z);
            }

            // Colors
            if(colors_.size() == vertices_.size()){
                glGenBuffers(1, &vbo_id);
                glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
                glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(glm::vec4), (void *)colors_.data(), GL_STATIC_DRAW);
                glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
                glEnableVertexAttribArray(2);
                vbos_[2] = vbo_id;
            }
            else{
                glm::vec4 color = colors_.empty() ? glm::vec4() : colors_.front();
                glVertexAttrib4f(2, color.x, color.y, color.z, color.a);
            }

            // Tex coords
            glBindBuffer(GL_ARRAY_BUFFER, vbos_[3]);
            if (tex_coords_2d_.size())
            {
                glBufferData(GL_ARRAY_BUFFER, tex_coords_2d_.size() * sizeof(glm::vec2), (void *)tex_coords_2d_.data(), GL_STATIC_DRAW);
                glVertexAttribPointer(3, tex_coords_2d_.size(), GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
                glEnableVertexAttribArray(3);
            }
            else if(tex_coords_3d_.size())
            {
                glBufferData(GL_ARRAY_BUFFER, tex_coords_3d_.size() * sizeof(glm::vec3), (void *)tex_coords_3d_.data(), GL_STATIC_DRAW);
                glVertexAttribPointer(3, tex_coords_3d_.size(), GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
                
            }

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        else
        {
            glBindVertexArray(vao_);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            if (tex_coords_2d_.size() || tex_coords_3d_.size()){
                glEnableVertexAttribArray(3);
            }
            else{
                glDisableVertexAttribArray(3);
            }
        }
        if(indices_.empty()){
            glDrawArrays(draw_mode_, 0, static_cast<GLsizei>(vertices_.size()));
        }
        else{
            glDrawElements(draw_mode_, indices_.size(), GL_UNSIGNED_INT, indices_.data());
        }
        glBindVertexArray(0);
        if (tex_)
        {
            tex_->unbind();
        }
#endif
    }

    MeshShape *MeshShape::createCube(double size)
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tex_coords;

        auto n = size / 2;
        vertices.push_back(glm::vec3(n, -n, -n));

        auto cube = new MeshShape();

        return cube;
    }
}