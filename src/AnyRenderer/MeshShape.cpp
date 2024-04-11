#include "MeshShape.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "CubeMap.h"
#include "RenderContext.h"

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
		tex_coords_ = std::move(coords);
	}
    
	void MeshShape::setTexture(Texture* tex, unsigned int unit)
	{
		tex_ = tex;
		tex_unit_ = unit;
	}

	void MeshShape::setEnvMap(CubeMap* tex, unsigned int unit)
	{
		envmap_ = tex;
		envmap_unit_ = unit;
	}

	void MeshShape::setDrawType(DrawMode type)
	{
		draw_mode_ = type;
	}

	Shader* MeshShape::getShader() const
	{
		auto shader = Shape::getShader();
		if (!shader)
			shader = ResourceManager::instance()->getInternalShader(ResourceManager::IS_MeshShape);
		return shader;
	}

	void MeshShape::draw(const RenderContext& ctx)
	{
		if (vertices_.empty())
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
		glActiveTexture(tex_unit_);
		if(tex_){
			tex_->bind();
		}
		else{
			ctx.getDefaultTexture()->bind();
		}
		glActiveTexture(envmap_unit_);
		if (envmap_)
		{
			envmap_->bind();
		}
		else{
			ctx.getDefaultEnvMap()->bind();
		}
		shader->set("tex", tex_unit_);
		shader->set("envmap", envmap_unit_);
		if (vao_ == 0)
		{
			glGenVertexArrays(1, &vao_);
			glBindVertexArray(vao_);

			// Vertices
			GLuint vbo_id;
			glGenBuffers(1, &vbo_id);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
			glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3), (void*)vertices_.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
			glEnableVertexAttribArray(0);
			vbos_[0] = vbo_id;

			// Normals
			if (normals_.size() == vertices_.size())
			{
				glGenBuffers(1, &vbo_id);
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
				glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(glm::vec3), (void*)normals_.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
				glEnableVertexAttribArray(1);
				vbos_[1] = vbo_id;
			}
			else
			{
				glm::vec3 norm = normals_.empty() ? glm::vec3(0.f, 0.f, 1.f) : normals_.front();
				glVertexAttrib3f(1, norm.x, norm.y, norm.z);
			}

			// Colors
			if (colors_.size() == vertices_.size())
			{
				glGenBuffers(1, &vbo_id);
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
				glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(glm::vec4), (void*)colors_.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
				glEnableVertexAttribArray(2);
				vbos_[2] = vbo_id;
			}
			else
			{
				glm::vec4 color = colors_.empty() ? glm::vec4(0.8f, 0.8f, 0.8f, 1.0f) : colors_.front();
				glVertexAttrib4f(2, color.x, color.y, color.z, color.a);
			}

			// Tex coords
			if (tex_coords_.size() == vertices_.size())
			{
				glGenBuffers(1, &vbo_id);
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
				glBufferData(GL_ARRAY_BUFFER, tex_coords_.size() * sizeof(glm::vec3), (void*)tex_coords_.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
				glEnableVertexAttribArray(3);
				vbos_[3] = vbo_id;
			}
			else
			{
				glm::vec2 coord = tex_coords_.empty() ? glm::vec2(0.f, 0.f) : tex_coords_.front();
				glVertexAttrib2f(3, coord.x, coord.y);
			}

			// Envmap
			if (envmap_coords_.size() == vertices_.size())
			{
				glGenBuffers(1, &vbo_id);
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
				glBufferData(GL_ARRAY_BUFFER, envmap_coords_.size() * sizeof(glm::vec3), (void*)envmap_coords_.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(4, envmap_coords_.size(), GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
				glEnableVertexAttribArray(4);
				vbos_[4] = vbo_id;
			}
			else
			{
				glm::vec3 coord = envmap_coords_.empty() ? glm::vec3(0.f, 0.f, 0.f) : envmap_coords_.front();
				glVertexAttrib3f(4, coord.x, coord.y, coord.z);
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else
		{
			glBindVertexArray(vao_);
		}
		if (indices_.empty())
		{
			glDrawArrays(draw_mode_, 0, static_cast<GLsizei>(vertices_.size()));
		}
		else
		{
			glDrawElements(draw_mode_, indices_.size(), GL_UNSIGNED_INT, indices_.data());
		}
		glBindVertexArray(0);
		if (tex_)
		{
			tex_->unbind();
		}
		if (envmap_)
		{
			envmap_->unbind();
		}
#endif
	}

	MeshShape* MeshShape::createCube(float size, bool gen_tex_coords)
	{
		auto n = size / 2;
		auto cube = new MeshShape();

		std::vector<glm::vec3> vertices = {
			glm::vec3(-n, -n, -n),
			glm::vec3(n, -n, -n),
			glm::vec3(n,  n, -n),
			glm::vec3(n,  n, -n),
			glm::vec3(-n,  n, -n),
			glm::vec3(-n, -n, -n),

			glm::vec3(-n, -n,  n),
			glm::vec3(n, -n,  n),
			glm::vec3(n,  n,  n),
			glm::vec3(n,  n,  n),
			glm::vec3(-n,  n,  n),
			glm::vec3(-n, -n,  n),

			glm::vec3(-n,  n,  n),
			glm::vec3(-n,  n, -n),
			glm::vec3(-n, -n, -n),
			glm::vec3(-n, -n, -n),
			glm::vec3(-n, -n,  n),
			glm::vec3(-n,  n,  n),

			glm::vec3(n,  n,  n),
			glm::vec3(n,  n, -n),
			glm::vec3(n, -n, -n),
			glm::vec3(n, -n, -n),
			glm::vec3(n, -n,  n),
			glm::vec3(n,  n,  n),

			glm::vec3(-n, -n, -n),
			glm::vec3(n, -n, -n),
			glm::vec3(n, -n,  n),
			glm::vec3(n, -n,  n),
			glm::vec3(-n, -n,  n),
			glm::vec3(-n, -n, -n),

			glm::vec3(-n,  n, -n),
			glm::vec3(n,  n, -n),
			glm::vec3(n,  n,  n),
			glm::vec3(n,  n,  n),
			glm::vec3(-n,  n,  n),
			glm::vec3(-n,  n, -n)
		};

		std::vector<glm::vec3> normals = {
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f)
		};

		if (gen_tex_coords) {
			std::vector<glm::vec3> tex_coords = {
				glm::vec3(0.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  1.0f, 0.f),
				glm::vec3(1.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  0.0f, 0.f),
                
				glm::vec3(0.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  1.0f, 0.f),
				glm::vec3(1.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  0.0f, 0.f),
                
				glm::vec3(1.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  0.0f, 0.f),
                
				glm::vec3(1.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  1.0f, 0.f),
				glm::vec3(0.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  0.0f, 0.f),
                
				glm::vec3(0.0f,  1.0f, 0.f),
				glm::vec3(1.0f,  1.0f, 0.f),
				glm::vec3(1.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  0.0f, 0.f),
				glm::vec3(0.0f,  0.0f, 0.f),
				glm::vec3(0.0f,  1.0f, 0.f),
                
				glm::vec3(0.0f,  1.0f, 0.f),
				glm::vec3(1.0f,  1.0f, 0.f),
				glm::vec3(1.0f,  0.0f, 0.f),
				glm::vec3(1.0f,  0.0f, 0.f),
				glm::vec3(0.0f,  0.0f, 0.f),
				glm::vec3(0.0f,  1.0f, 0.f)

			};
			cube->setTexCoords(tex_coords);
		}

		cube->setVertices(vertices);
		cube->setNormals(normals);
		cube->setDrawType(Triangles);
		return cube;
	}
}