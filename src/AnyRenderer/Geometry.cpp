#include "Geometry.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "CubeMap.h"
#include "RenderContext.h"

namespace AnyRenderer
{
	Geometry::Geometry()
	{
	}

	Geometry::~Geometry()
	{
		if (vao_)
		{
			glDeleteVertexArrays(1, &vao_);
		}
	}

	void Geometry::addTexture(GLuint unit, Texture *tex)
	{
		auto found_at = textures_.find(unit);
		if (found_at != textures_.end())
		{
			auto t = found_at->second;
			if (t == tex)
				return;
			t->unref();
		}
		textures_[unit] = tex;
		tex->ref();
	}

	void Geometry::addVertexAttribArray(GLuint loc, Array *arr)
	{
		assert(arr);
		auto found_at = vbos_.find(loc);
		if (found_at != vbos_.end())
		{
			auto vbo = found_at->second;
			if (vbo == arr)
				return;
			vbo->unref();
		}
		vbos_[loc] = arr;
		arr->ref();
	}

	void Geometry::addPrimitive(PrimitiveSet *prim)
	{
		primitives_.push_back(prim);
		prim->ref();
	}

	void Geometry::draw(const RenderContext &ctx)
	{
		if (vbos_.empty())
			return;
		if (primitives_.empty())
			return;

		auto shader = ctx.getCurrentShader();
		if (vao_ == 0)
		{
			glGenVertexArrays(1, &vao_);
			glBindVertexArray(vao_);
			// VBOs
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
					// arr->unbind();
				}
				else
				{
					auto arr_type = arr->getType();
					if (arr_type == Array::ARRAY_VEC2F)
					{
						glm::vec2 val = arr->isEmpty() ? glm::vec2(0.f, 0.f) : *(glm::vec2 *)arr->getAt(0);
						glVertexAttrib2f(loc, val.x, val.y);
					}
					else if (arr_type == Array::ARRAY_VEC3F)
					{
						glm::vec3 val = arr->isEmpty() ? glm::vec3(0.f, 0.f, 0.f) : *(glm::vec3 *)arr->getAt(0);
						glVertexAttrib3f(loc, val.x, val.y, val.z);
					}
					else if (arr_type == Array::ARRAY_VEC4F)
					{
						glm::vec4 val = arr->isEmpty() ? glm::vec4(0.f, 0.f, 0.f, 1.0f) : *(glm::vec4 *)arr->getAt(0);
						glVertexAttrib4f(loc, val.x, val.y, val.z, val.a);
					}
					else
					{
					}
				}
			}
		}
		else
		{
			glBindVertexArray(vao_);
		}

		shader->set("tex_2d", 0);
		for (auto &kv : textures_)
		{
			auto unit = kv.first;
			auto tex = kv.second;
			glActiveTexture(unit);
			tex->bind();
		}

		for (auto priv : primitives_)
		{
			priv->draw();
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

	BoundingBox Geometry::getBoundingBox() const
	{
		return bb_;
	}
	void Geometry::setBoundingBox(const BoundingBox &bb)
	{
		bb_ = bb;
	}

	Geometry *Geometry::createCube(float size, int vertices_loc, int normals_loc, int tex_2d_coords_loc, int cube_map_coords_loc)
	{
		auto n = size / 2;
		auto cube = new Geometry();

		auto vertices = new Vec3fArray();
		vertices->emplace_back(-n, -n, -n);
		vertices->emplace_back(n, -n, -n);
		vertices->emplace_back(n, n, -n);
		vertices->emplace_back(n, n, -n);
		vertices->emplace_back(-n, n, -n);
		vertices->emplace_back(-n, -n, -n);

		vertices->emplace_back(-n, -n, n);
		vertices->emplace_back(n, -n, n);
		vertices->emplace_back(n, n, n);
		vertices->emplace_back(n, n, n);
		vertices->emplace_back(-n, n, n);
		vertices->emplace_back(-n, -n, n);

		vertices->emplace_back(-n, n, n);
		vertices->emplace_back(-n, n, -n);
		vertices->emplace_back(-n, -n, -n);
		vertices->emplace_back(-n, -n, -n);
		vertices->emplace_back(-n, -n, n);
		vertices->emplace_back(-n, n, n);

		vertices->emplace_back(n, n, n);
		vertices->emplace_back(n, n, -n);
		vertices->emplace_back(n, -n, -n);
		vertices->emplace_back(n, -n, -n);
		vertices->emplace_back(n, -n, n);
		vertices->emplace_back(n, n, n);

		vertices->emplace_back(-n, -n, -n);
		vertices->emplace_back(n, -n, -n);
		vertices->emplace_back(n, -n, n);
		vertices->emplace_back(n, -n, n);
		vertices->emplace_back(-n, -n, n);
		vertices->emplace_back(-n, -n, -n);

		vertices->emplace_back(-n, n, -n);
		vertices->emplace_back(n, n, -n);
		vertices->emplace_back(n, n, n);
		vertices->emplace_back(n, n, n);
		vertices->emplace_back(-n, n, n);
		vertices->emplace_back(-n, n, -n);

		auto normals = new Vec3fArray();
		normals->emplace_back(0.0f, 0.0f, -1.0f);
		normals->emplace_back(0.0f, 0.0f, -1.0f);
		normals->emplace_back(0.0f, 0.0f, -1.0f);
		normals->emplace_back(0.0f, 0.0f, -1.0f);
		normals->emplace_back(0.0f, 0.0f, -1.0f);
		normals->emplace_back(0.0f, 0.0f, -1.0f);

		normals->emplace_back(0.0f, 0.0f, 1.0f);
		normals->emplace_back(0.0f, 0.0f, 1.0f);
		normals->emplace_back(0.0f, 0.0f, 1.0f);
		normals->emplace_back(0.0f, 0.0f, 1.0f);
		normals->emplace_back(0.0f, 0.0f, 1.0f);
		normals->emplace_back(0.0f, 0.0f, 1.0f);

		normals->emplace_back(-1.0f, 0.0f, 0.0f);
		normals->emplace_back(-1.0f, 0.0f, 0.0f);
		normals->emplace_back(-1.0f, 0.0f, 0.0f);
		normals->emplace_back(-1.0f, 0.0f, 0.0f);
		normals->emplace_back(-1.0f, 0.0f, 0.0f);
		normals->emplace_back(-1.0f, 0.0f, 0.0f);

		normals->emplace_back(1.0f, 0.0f, 0.0f);
		normals->emplace_back(1.0f, 0.0f, 0.0f);
		normals->emplace_back(1.0f, 0.0f, 0.0f);
		normals->emplace_back(1.0f, 0.0f, 0.0f);
		normals->emplace_back(1.0f, 0.0f, 0.0f);
		normals->emplace_back(1.0f, 0.0f, 0.0f);

		normals->emplace_back(0.0f, -1.0f, 0.0f);
		normals->emplace_back(0.0f, -1.0f, 0.0f);
		normals->emplace_back(0.0f, -1.0f, 0.0f);
		normals->emplace_back(0.0f, -1.0f, 0.0f);
		normals->emplace_back(0.0f, -1.0f, 0.0f);
		normals->emplace_back(0.0f, -1.0f, 0.0f);

		normals->emplace_back(0.0f, 1.0f, 0.0f);
		normals->emplace_back(0.0f, 1.0f, 0.0f);
		normals->emplace_back(0.0f, 1.0f, 0.0f);
		normals->emplace_back(0.0f, 1.0f, 0.0f);
		normals->emplace_back(0.0f, 1.0f, 0.0f);
		normals->emplace_back(0.0f, 1.0f, 0.0f);

		if (tex_2d_coords_loc >= 0)
		{
			auto tex_coords = new Vec2fArray();
			tex_coords->emplace_back(0.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 1.0f);
			tex_coords->emplace_back(1.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 0.0f);
			tex_coords->emplace_back(0.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 1.0f);
			tex_coords->emplace_back(1.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(0.0f, 1.0f);
			tex_coords->emplace_back(1.0f, 1.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(0.0f, 0.0f);
			tex_coords->emplace_back(0.0f, 1.0f);
			tex_coords->emplace_back(0.0f, 1.0f);
			tex_coords->emplace_back(1.0f, 1.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(1.0f, 0.0f);
			tex_coords->emplace_back(0.0f, 0.0f);
			tex_coords->emplace_back(0.0f, 1.0f);

			cube->addVertexAttribArray(tex_2d_coords_loc, tex_coords);
		}
		if (cube_map_coords_loc >= 0)
		{
		}
		cube->addVertexAttribArray(vertices_loc, vertices);
		cube->addVertexAttribArray(normals_loc, normals);
		cube->addPrimitive(new DrawArrays(DrawArrays::MODE_TRIANGLES, 0, vertices->size()));
		return cube;
	}
}