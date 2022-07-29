#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API Vector2f
	{
	public:
		float x;
		float y;

		Vector2f()
			: x(0.0f), y(0.0f)
		{
		}

		Vector2f(float x, float y)
			: x(x), y(y)
		{
		}
	};
}