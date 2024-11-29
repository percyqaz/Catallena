#pragma once

#include <glad/gl.h>
#include "linmath.h"
#include <iostream>

namespace Catallena::Graphics
{
	struct Shader
	{
		GLuint handle{};

		static bool compile(GLenum shader_type, const char* src, Shader *shader)
		{
			GLuint handle{ glCreateShader(shader_type) };
			glShaderSource(handle, 1, &src, NULL);

			glCompileShader(handle);
			GLint success;
			glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
		
			if (!success)
			{
				GLint length;
				glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
				std::string log(length, ' ');
				glGetShaderInfoLog(handle, length, &length, &log[0]);
				std::cout << "Error compiling shader: " << log << "\n";
				return false;
			}

			*shader = { handle };
			return true;
		}

		void destroy() const
		{
			glDeleteShader(handle);
		}
	};

	struct ShaderProgram {
		GLuint handle{};

		static ShaderProgram create(const char* vsh, const char* fsh)
		{
			Shader vert{ 0 };
			if (!Shader::compile(GL_VERTEX_SHADER, vsh, &vert))
			{
				throw std::logic_error("Vertex shader didn't compile");
			}

			Shader frag{ 0 };
			if (!Shader::compile(GL_FRAGMENT_SHADER, fsh, &frag))
			{
				throw std::logic_error("Fragment shader didn't compile");
			}

			GLuint program{ glCreateProgram() };
			glAttachShader(program, vert.handle);
			glAttachShader(program, frag.handle);
			glLinkProgram(program);
			GLint status;
			glGetProgramiv(program, GL_LINK_STATUS, &status);
			if (!status)
			{
				GLint length;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
				std::string log(length, ' ');
				glGetProgramInfoLog(program, length, &length, &log[0]);
				std::cout << "Error linking program: " << log << "\n";
				throw std::logic_error("Program did not link, see stdout for info log");
			}

			return { program };
		}

		GLint get_location(const char* uniform_name) const
		{
			return glGetUniformLocation(handle, uniform_name);
		}

		void set_uniform_mat4(GLint loc, mat4x4 value) const
		{
			glUniformMatrix4fv(loc, 1, false, (const GLfloat*)value);
		}

		void set_uniform_f32(GLint loc, float value) const
		{
			glUniform1f(loc, value);
		}

		void set_uniform_i32(GLint loc, int value) const
		{
			glUniform1i(loc, value);
		}

		void use() const
		{
			glUseProgram(handle);
		}

		void destroy() const
		{
			glDeleteProgram(handle);
		}
	};
}