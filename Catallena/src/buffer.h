#pragma once

#include <glad/gl.h>
#include "batch.h"

namespace Catallena::Graphics
{
	struct Buffer {
		GLuint handle{};
		GLenum target{};

		static Buffer create(GLenum target, const void* initial_data, GLsizeiptr size)
		{
			GLuint handle{};
			glGenBuffers(1, &handle);
			glBindBuffer(target, handle);
			glBufferData(target, size, initial_data, GL_DYNAMIC_DRAW);
			return { handle, target };
		}

		void destroy() const
		{
			glDeleteBuffers(1, &handle);
		}

		void bind() const
		{
			glBindBuffer(target, handle);
		}

		void data(const void* data, int size) const
		{
			glBufferSubData(target, 0, size, data);
		}
	};

	struct VertexArrayObject
	{
		GLuint handle{};

		static VertexArrayObject create(Buffer vbo, Buffer ebo)
		{
			GLuint handle{};
			glGenVertexArrays(1, &handle);
			vbo.bind();
			ebo.bind();
			const VertexArrayObject vao{ handle };
			vao.bind();
			return vao;
		}

		void destroy() const
		{
			glDeleteVertexArrays(1, &handle);
		}

		void bind() const
		{
			glBindVertexArray(handle);
		}

		void vertex_attrib_pointer(int index, int count, int vtype, bool normalise, int vertex_size, GLsizeiptr offset) const
		{
			glVertexAttribPointer(index, count, vtype, normalise, vertex_size, (void*)offset);
			glEnableVertexAttribArray(index);
		}
	};
}