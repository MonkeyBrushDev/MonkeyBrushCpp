/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "Interpolation.hpp"

namespace mb
{
	float Interpolation::linear(float p0, float p1, float t)
	{
		return (p1 - p0) * t + p0;
	}
	float Interpolation::bezier(float x1, float y1, float x2, float y2, float t)
	{
    float f0 = 1.0f - 3.0f * x2 + 3.0f * x1;
    float f1 = 3.0f * x2 - 6.0f * x1;
    float f2 = 3.0f * x1;

    float rt = t;
    for (unsigned int i = 0; i < 5; ++i)
    {
			float rt2 = rt * rt;
			float rt3 = rt2 * rt;

			float x = f0 * rt3 + f1 * rt2 + f2 * rt;
			float slope = 1.0f / (3.0f * f0 * rt2 + 2.0f * f1 * rt + f2);
            rt -= (x - t) * slope;
			rt = std::min(1.0f, std::max(0.0f, rt));
    }

    // Resolve cubic bezier
    return 3.0f * std::pow(1.0f - rt, 2.0f) * rt * y1 +
        3.0f * (1.0f - rt) * std::pow(rt, 2.0f) * y2 +
        std::pow(rt, 3.0f);
  }
  float Interpolation::catmullRom(float p0, float p1, float p2, float p3, float t)
  {
    float
      v0 = (p2 - p0) * 0.5f,
      v1 = (p3 - p1) * 0.5f,
      t2 = t * t,
      t3 = t * t2;
    return (2.0f * p1 - 2.0f * p2 + v0 + v1) * t3 +
        (-3.0f * p1 + 3.0f * p2 - 2.0f * v0 - v1) * t2 + v0 * t + p1;
  };
}
