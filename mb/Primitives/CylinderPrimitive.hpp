/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#ifndef CYLINDERPRIMITIVE_H
#define CYLINDERPRIMITIVE_H

#include "ConePrimitive.hpp"

namespace mb
{
    class CylinderPrimitive: public ConePrimitive
    {
    public:
        MB_API
        CylinderPrimitive(float radius, float height,
                       float radialSubDiv = 15,
                       float heightSubDiv = 1,
                       bool createTopBase = true,
                       bool createBottomBase = true , Primitive::Type type = Primitive::Type::TRIANGLES,
                       Primitive::TDrawType typeDraw = Primitive::DRAW_ELEMENTS);

    };
}


#endif // CYLINDERPRIMITIVE_H
