#pragma once

#include "math.h"

namespace Catallena::Graphics
{
	namespace Render
	{
		void start();

		void finish();

		void resize(int width, int height);

		void init();

		void rect(Rect r, Color c);

		void quad(Quad q, QuadColor c);
	}
}