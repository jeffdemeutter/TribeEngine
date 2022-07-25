#pragma once
#include <glm/glm.hpp>

struct RaycastInfo
{
	glm::vec2 hitPos;
	glm::vec2 reflect;
};

namespace Raycast
{
	inline bool DoRaycast(glm::vec2 p1, glm::vec2 dir, float speed, const std::vector<std::vector<glm::vec2>>& obstacles, RaycastInfo& rcInfo)
	{
		const glm::vec2 p2 = p1 + dir * speed * 1.2f;

		const float x1 = p1.x;
		const float x2 = p2.x;

		const float y1 = p1.y;
		const float y2 = p2.y;

		for (auto spline : obstacles)
		{
			glm::vec2 p3 = spline.back();
			for (int i = 0; i < spline.size(); ++i)
			{
				const glm::vec2 p4 = spline[i];
				if (i != 0)
					p3 = spline[i - 1];


				const float x3 = p3.x;
				const float x4 = p4.x;

				const float y3 = p3.y;
				const float y4 = p4.y;

				float d = (p1.x - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
				// If d is zero, there is no intersection
				if (abs(d) <= 1e-6)
					continue;

				const float pre = (x1 * y2 - y1 * x2);
				const float post = (x3 * y4 - y3 * x4);
				// Get the x and y
				float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
				float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

				// Check if the x and y coordinates are within both lines
				if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
					x < std::min(x3, x4) || x > std::max(x3, x4))
					continue;
				if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
					y < std::min(y3, y4) || y > std::max(y3, y4))
					continue;



				// raycast hit
				rcInfo.hitPos = { x, y };
				glm::vec2 normal{ (p4.y - p3.y), -(p4.x - p3.x) };
				normal = normalize(normal);
				rcInfo.reflect = normalize(reflect(normalize(p2 - p1), normal));

				return true;
			}
		}
		return false;
	}

}

