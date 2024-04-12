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
	}

	void MeshShape::addTexture(GLuint unit, Texture *tex)
	{
		auto found_at = textures_.find(unit);
		if (found_at != textures_.end())
		{
			auto tex = found_at->second;
			delete tex;
		}
		textures_[unit] = tex;
	}

	void MeshShape::addVertexAttribArray(GLuint loc, Array *arr)
	{
		auto found_at = vbos_.find(loc);
		if (found_at != vbos_.end())
		{
			auto vbo = found_at->second;
			delete vbo;
		}
		vbos_[loc] = arr;
	}

	void MeshShape::addPrimitive(PrimitiveSet* prim){
		primitives_.push_back(prim);
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
		if (!vbos_.empty())
			return;

		auto shader = getShader();
		if (vao_ == 0)
		{
			glGenVertexArrays(1, &vao_);
			glBindVertexArray(vao_);

			// Textures coords
			for (auto &kv : vbos_)
			{
				auto loc = kv.first;
				auto arr = kv.second;
				if (arr->getSize() > 1)
				{
					arr->bind();
					auto size_of_item = arr->getSizeOfItem();
					glVertexAttribPointer(loc, size_of_item / sizeof(GLfloat), GL_FLOAT, GL_FALSE, size_of_item, 0);
					glEnableVertexAttribArray(loc);
					arr->unbind();
				}
				else
				{
					auto arr_type = arr->getType();
					if (arr_type == Array::Vec2fArray)
					{
						glm::vec2 val = arr->getSize() ? glm::vec2(0.f, 0.f) : *(glm::vec2 *)arr->getAt(0);
						glVertexAttrib2f(loc, val.x, val.y);
					}
					else if (arr_type == Array::Vec3fArray)
					{
						glm::vec3 val = arr->getSize() ? glm::vec3(0.f, 0.f, 0.f) : *(glm::vec3 *)arr->getAt(0);
						glVertexAttrib3f(loc, val.x, val.y, val.z);
					}
					else if (arr_type == Array::Vec4fArray)
					{
						glm::vec4 val = arr->getSize() ? glm::vec4(0.f, 0.f, 0.f, 0.0f) : *(glm::vec4 *)arr->getAt(0);
						glVertexAttrib3f(loc, val.x, val.y, val.z);
					}
					else{

					}
				}
			}

			for (auto &kv : textures_)
			{
				auto unit = kv.first;
				auto tex = kv.second;
				glActiveTexture(unit);
				tex->bind();
			}
		}
		else
		{
			glBindVertexArray(vao_);
		}

		glBindVertexArray(0);
		for (auto &kv : textures_)
		{
			auto tex = kv.second;
			if (!tex)
				continue;
			tex->unbind();
		}
	}

	MeshShape *MeshShape::createCube(float size, bool gen_tex_coords)
	{
		auto n = size / 2;
		auto cube = new MeshShape();

		std::vector<glm::vec3> vertices = {
			glm::vec3(-n, -n, -n),
			glm::vec3(n, -n, -n),
			glm::vec3(n, n, -n),
			glm::vec3(n, n, -n),
			glm::vec3(-n, n, -n),
			glm::vec3(-n, -n, -n),

			glm::vec3(-n, -n, n),
			glm::vec3(n, -n, n),
			glm::vec3(n, n, n),
			glm::vec3(n, n, n),
			glm::vec3(-n, n, n),
			glm::vec3(-n, -n, n),

			glm::vec3(-n, n, n),
			glm::vec3(-n, n, -n),
			glm::vec3(-n, -n, -n),
			glm::vec3(-n, -n, -n),
			glm::vec3(-n, -n, n),
			glm::vec3(-n, n, n),

			glm::vec3(n, n, n),
			glm::vec3(n, n, -n),
			glm::vec3(n, -n, -n),
			glm::vec3(n, -n, -n),
			glm::vec3(n, -n, n),
			glm::vec3(n, n, n),

			glm::vec3(-n, -n, -n),
			glm::vec3(n, -n, -n),
			glm::vec3(n, -n, n),
			glm::vec3(n, -n, n),
			glm::vec3(-n, -n, n),
			glm::vec3(-n, -n, -n),

			glm::vec3(-n, n, -n),
			glm::vec3(n, n, -n),
			glm::vec3(n, n, n),
			glm::vec3(n, n, n),
			glm::vec3(-n, n, n),
			glm::vec3(-n, n, -n)};

		std::vector<glm::vec3> normals = {
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)};

		if (gen_tex_coords)
		{
			std::vector<glm::vec2> tex_coords = {
				glm::vec3(0.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 1.0f, 0.f),
				glm::vec3(1.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 0.0f, 0.f),

				glm::vec3(0.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 1.0f, 0.f),
				glm::vec3(1.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 0.0f, 0.f),

				glm::vec3(1.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 0.0f, 0.f),

				glm::vec3(1.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 1.0f, 0.f),
				glm::vec3(0.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 0.0f, 0.f),

				glm::vec3(0.0f, 1.0f, 0.f),
				glm::vec3(1.0f, 1.0f, 0.f),
				glm::vec3(1.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 0.0f, 0.f),
				glm::vec3(0.0f, 0.0f, 0.f),
				glm::vec3(0.0f, 1.0f, 0.f),

				glm::vec3(0.0f, 1.0f, 0.f),
				glm::vec3(1.0f, 1.0f, 0.f),
				glm::vec3(1.0f, 0.0f, 0.f),
				glm::vec3(1.0f, 0.0f, 0.f),
				glm::vec3(0.0f, 0.0f, 0.f),
				glm::vec3(0.0f, 1.0f, 0.f)

			};
			// cube->setTexCoords(tex_coords);
		}

		// auto vertices2 = new Vec3fArray();

		// cube->setVertices(0, );
		// cube->setNormals(normals);
		// cube->setDrawType(Triangles);
		return cube;
	}
}