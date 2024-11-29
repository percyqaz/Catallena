#include <glad/gl.h>
#include "batch.h"
#include "math.h"
#include "linmath.h"
#include "render.h"
#include "shader.h"

namespace Catallena::Graphics
{
		static const char* FRAGMENT_SHADER = R""""(
#version 330 core
in vec2 fUv;
in vec4 fColor;
in float fTexLayer;

uniform sampler2DArray sampler;

out vec4 FragColor;

void main()
{
    FragColor = vec4(1, 1, 1, 1);
    //FragColor += texture(sampler, vec3(fUv, fTexLayer));
    FragColor *= fColor;
}
			)"""";

		static const char* VERTEX_SHADER = R""""(
#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vUv;
layout (location = 2) in vec4 vColor;
layout (location = 3) in float vTexLayer;

uniform mat4 uProjection;

out vec2 fUv;
out vec4 fColor;
out float fTexLayer;

void main()
{
    gl_Position = uProjection * vec4(vPos, 0.0, 1.0);
    fUv = vUv;
    fColor = vColor;
    fTexLayer = vTexLayer;
}
			)"""";

	namespace Render
	{
		ShaderProgram main_shader{};
		GLint uProjection_loc{};
		Batch batch{};

		void init()
		{
			glDisable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glClearColor(0.0, 0.2, 0.0, 1.0);
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
			glClearStencil(0x00);

			batch = Batch::create();

			main_shader = ShaderProgram::create(VERTEX_SHADER, FRAGMENT_SHADER);
			main_shader.use();
			uProjection_loc = glGetUniformLocation(main_shader.handle, "uProjection");
		}

		void start()
		{
			glClear(GL_COLOR_BUFFER_BIT);
			batch.start();
		}

		void finish()
		{
			batch.finish();
			glFlush();
		}

		static mat4x4 view_mat{};

		static vec4* create_projection(int width, int height) 
		{
			mat4x4_identity(view_mat);
			mat4x4_ortho(view_mat, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
			mat4x4_translate_in_place(view_mat, -1.0f, -1.0f, 0.0f);
		}

		void resize(int width, int height)
		{
			glViewport(0, 0, width, height);

			mat4x4_identity(view_mat);
			mat4x4_ortho(view_mat, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
			mat4x4_translate_in_place(view_mat, -1.0f, -1.0f, 0.0f);

			main_shader.set_uniform_mat4(uProjection_loc, view_mat);
		}

		void quad(Quad q, QuadColor c)
		{
			batch.vertex(q.a, { 0.0, 0.0 }, c.a, 0);
			batch.vertex(q.b, { 0.0, 0.0 }, c.b, 0);
			batch.vertex(q.c, { 0.0, 0.0 }, c.c, 0);
			batch.vertex(q.a, { 0.0, 0.0 }, c.a, 0);
			batch.vertex(q.c, { 0.0, 0.0 }, c.c, 0);
			batch.vertex(q.d, { 0.0, 0.0 }, c.d, 0);
		}

		void rect(Rect r, Color c)
		{
			quad(r.as_quad(), QuadColor::of_color(c));
		}
	}
}