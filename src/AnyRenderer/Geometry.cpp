#include "Geometry.h"

#include <vine/core/Ptr.h>

#include "Shader.h"
#include "State.h"
#include "Texture.h"

namespace AnyRenderer
{
	VI_OBJECT_META_IMPL(Geometry, Drawable);

	struct Geometry::Data
	{
		GLuint vao = 0;
		std::map<GLuint, vine::RefPtr<Array>> vbos;
		std::map<GLuint, vine::RefPtr<Texture>> textures;
		std::map<GLuint, GLuint> texture_locs;
		std::map<GLuint, std::string> texture_names_;
		std::vector<vine::RefPtr<PrimitiveSet>> primitives;
		BoundingBox bb;
	};

	Geometry::Geometry() : d(new Data())
	{
	}

	Geometry::~Geometry()
	{
		if (d->vao)
		{
			glDeleteVertexArrays(1, &d->vao);
		}
		delete d;
	}

	void Geometry::addTexture(GLuint unit, GLuint loc, Texture *tex)
	{
		auto found_at = d->textures.find(unit);
		if (found_at != d->textures.end())
		{
			auto t = found_at->second;
			if (t == tex)
				return;
		}
		d->textures[unit] = tex;
		d->texture_locs[unit] = loc;
	}

	void Geometry::addTexture(GLuint unit, const std::string &name, Texture *tex)
	{
		auto found_at = d->textures.find(unit);
		if (found_at != d->textures.end())
		{
			auto t = found_at->second;
			if (t == tex)
				return;
		}
		d->textures[unit] = tex;
		d->texture_names_[unit] = name;
	}

	void Geometry::addVertexAttribArray(GLuint loc, Array *arr)
	{
		assert(arr);
		auto found_at = d->vbos.find(loc);
		if (found_at != d->vbos.end())
		{
			auto vbo = found_at->second;
			if (vbo == arr)
				return;
		}
		d->vbos[loc] = arr;
	}

	void Geometry::addPrimitive(PrimitiveSet *prim)
	{
		d->primitives.push_back(prim);
	}

	void Geometry::draw(State &state)
	{
		if (d->vbos.empty())
			return;
		if (d->primitives.empty())
			return;

		auto shader = state.getCurrentShader();
		if (d->vao == 0)
		{
			glGenVertexArrays(1, &d->vao);
			glBindVertexArray(d->vao);
			// VBOs
			for (auto &kv : d->vbos)
			{
				auto loc = kv.first;
				auto arr = kv.second;
				if (arr->getSize() > 1)
				{
					arr->bind(state);
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
			glBindVertexArray(d->vao);
		}
		for (auto &kv : d->textures)
		{
			auto unit = kv.first;
			auto tex = kv.second;
			if (d->texture_locs.contains(unit))
			{
				shader->set(state, d->texture_locs[unit], unit);
			}
			else
			{
				shader->set(state, d->texture_names_[unit], unit);
			}
			glActiveTexture(unit);
			tex->bind(state);
		}

		for (auto priv : d->primitives)
		{
			priv->draw();
		}
		glBindVertexArray(0);
		for (auto &kv : d->textures)
		{
			auto tex = kv.second;
			if (!tex)
				continue;
			tex->unbind(state);
		}
	}

	BoundingBox Geometry::getBoundingBox() const
	{
		return d->bb;
	}
	void Geometry::setBoundingBox(const BoundingBox &bb)
	{
		d->bb = bb;
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

		if (normals_loc >= 0)
		{
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
			cube->addVertexAttribArray(normals_loc, normals);
		}
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
			auto tex_coords = new Vec3fArray();
			tex_coords->resize(vertices->size());
			std::copy(vertices->begin(), vertices->end(), tex_coords->begin());
			cube->addVertexAttribArray(cube_map_coords_loc, tex_coords);
		}
		cube->addVertexAttribArray(vertices_loc, vertices);
		cube->addPrimitive(new DrawArrays(DrawArrays::MODE_TRIANGLES, 0, vertices->size()));
		return cube;
	}

	//Geometry *Geometry::createTexturedQuad(int vertices_loc, int norms_loc, int tex_coords_loc, float w, float h, float x = 0, float y = 0, float left = 0, float bottom = 0, float right = 1, float top = 1)
	//{
	//	auto vertices = new Vec3fArray();
	//	vertices->push_back(glm::vec3(x, y, 0));
	//	vertices->push_back(glm::vec3(x + w, 0, 0));
	//	vertices->push_back(glm::vec3(x + w, y + h, 0));
	//	vertices->push_back(glm::vec3(0, y + h, 0));

	//	auto texcoords = new Vec2fArray();
	//	texcoords->push_back(glm::vec2(left, bottom));
	//	texcoords->push_back(glm::vec2(right, bottom));
	//	texcoords->push_back(glm::vec2(right, top));
	//	texcoords->push_back(glm::vec2(left, top));

	//	auto geom = new Geometry();
	//	geom->addVertexAttribArray(vertices_loc, vertices);
	//	geom->addVertexAttribArray(tex_coords_loc, texcoords);
	//	geom->addPrimitive(new DrawArrays(PrimitiveSet::MODE_QUADS, 0, vertices->size()));
	//	return geom;
	//}
}