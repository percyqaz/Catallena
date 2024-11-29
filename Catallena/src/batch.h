#pragma once

#include <glad/gl.h>
#include "math.h"
#include "buffer.h"
#include <iostream>

namespace Catallena::Graphics
{
	struct Vertex {
		float x{};
		float y{};
		float u{};
		float v{};
		unsigned char r{};
		unsigned char g{};
		unsigned char b{};
		unsigned char a{};
		float l{};
	}; 
	
	static const int BATCH_CAPACITY{ 1024 };
	static const int VERTICES_PER_ELEMENT{ 6 };
	static const int VERTEX_COUNT{ BATCH_CAPACITY * VERTICES_PER_ELEMENT };
	static const int VERTEX_SIZE{ sizeof(Vertex) };

	struct Batch {
		Vertex* vertices{};
		Buffer ebo{};
		Buffer vbo{};
		VertexArrayObject vao{};
		bool active{};
		int vcount{};

		static Batch create()
		{
			int elements[]{ 0,1,2,3,4,5 };
			const Buffer ebo{ Buffer::create(GL_ELEMENT_ARRAY_BUFFER, elements, sizeof(elements)) };

			Vertex* vertices{ new Vertex[VERTEX_COUNT] };
			const Buffer vbo{ Buffer::create(GL_ARRAY_BUFFER, vertices, VERTEX_SIZE * VERTEX_COUNT) };

			const VertexArrayObject vao{ VertexArrayObject::create(vbo, ebo) };
			vao.vertex_attrib_pointer(0, 2, GL_FLOAT, false, VERTEX_SIZE, 0);
			vao.vertex_attrib_pointer(1, 2, GL_FLOAT, false, VERTEX_SIZE, sizeof(float) * 2);
			vao.vertex_attrib_pointer(2, 4, GL_UNSIGNED_BYTE, true, VERTEX_SIZE, sizeof(float) * 4);
			vao.vertex_attrib_pointer(3, 1, GL_FLOAT, false, VERTEX_SIZE, sizeof(float) * 4 + 4);

			return { vertices, ebo, vbo, vao, false, 0 };
		}

		void draw()
		{
			if (vcount)
			{
				vbo.data(vertices, VERTEX_SIZE * vcount);
				glDrawArrays(GL_TRIANGLES, 0, vcount);
			}
			vcount = 0;
		}

		void start()
		{
			vao.bind();
			active = true;
		}

		void finish()
		{
			draw();
			active = false;
		}

		void vertex(Vec2 pos, Vec2 uv, Color color, int texture_layer)
		{
			if (vcount == VERTEX_COUNT)
			{
				draw();
			}
			Vertex vertex{ pos.x, pos.y, uv.x, uv.y, color.r, color.g, color.b, color.a, static_cast<float>(texture_layer) };
			*(vertices + vcount) = vertex;
			vcount++;
		}
	};
}