#pragma once

namespace Catallena::Graphics
{
	struct Color {
		unsigned char r{};
		unsigned char g{};
		unsigned char b{};
		unsigned char a{};
	};

	struct QuadColor {
		Color a{};
		Color b{};
		Color c{};
		Color d{};

		static QuadColor of_color(Color c)
		{
			return { c, c, c, c };
		}
	};

	struct Vec2 {
		float x{};
		float y{};
	};

	struct Quad
	{
		Vec2 a{};
		Vec2 b{};
		Vec2 c{};
		Vec2 d{};
	};

	struct Rect
	{
		float left{};
		float top{};
		float right{};
		float bottom{};

		Quad as_quad() const
		{
			return { { left, top }, { right, top }, { right, bottom }, { left, bottom } };
		}

		float width() const
		{
			return right - left;
		}

		float height() const
		{
			return bottom - top;
		}
	};
}