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

#include "Curves.hpp"

namespace mb
{
	namespace curves
	{
		Ellipse::Ellipse(const Vect2& center, const Vect2& radius, float startAngle, float endAngle, bool isClockwise)
		: Curve2D()
			, _center(center)
			, _radius(radius)
			, _startAngle(startAngle)
			, _endAngle(endAngle)
			, _isClockwise(isClockwise)
		{
		}
		Vect2 Ellipse::evaluate(const float t)
		{
			float deltaAngle = this->_endAngle - this->_startAngle;
			if (deltaAngle < 0.0f) deltaAngle += Mathf::TWO_PI;
			if (deltaAngle > Mathf::TWO_PI) deltaAngle -= Mathf::TWO_PI;
			float angle = this->_isClockwise ? this->_endAngle + (1.0f - t) *
				(Mathf::TWO_PI - deltaAngle) : this->_startAngle + t * deltaAngle;

			float tx = this->_center.x() + this->_radius.x() * std::cos(angle);
			float ty = this->_center.y() + this->_radius.y() * std::sin(angle);
			return Vect2(tx, ty);
		}
		Line2D::Line2D(const Vect2& x, const Vect2& y)
			: Curve2D()
		{
			this->_p1 = x;
			this->_p2 = y;
		}
		Vect2 Line2D::evaluate(const float t)
		{
			return Vect2::add(Vect2::sub(this->_p2, this->_p1).multByScalar(t), this->_p1);
		}
		Line3D::Line3D(const Vect3& x, const Vect3& y)
			: Curve3D()
		{
			this->_p1 = x;
			this->_p2 = y;
		}
		Vect3 Line3D::evaluate(const float t)
		{
			return Vect3::add(Vect3::sub(this->_p2, this->_p1).multByScalar(t), (this->_p1));
		}
		CubicBezier::CubicBezier(const Vect2& cpi, const Vect2& cpp1, const Vect2& cpp2, const Vect2& cpe)
			: Curve2D()
		{
			this->_list.push_back(cpi);
			this->_list.push_back(cpp1);
			this->_list.push_back(cpp2);
			this->_list.push_back(cpe);
		}
		Vect2 CubicBezier::evaluate(const float t)
		{
			return Vect2(
				this->bezierCurveInterpolation(
					this->_list[0].x(), this->_list[1].x(), this->_list[2].x(), this->_list[3].x(), t),
				this->bezierCurveInterpolation(
					this->_list[0].y(), this->_list[1].y(), this->_list[2].y(), this->_list[3].y(), t)
			);
		}
		float CubicBezier::bezierCurveInterpolation(const float p0, const float p1,
			const float p2, const float p3, const float t)
		{
			return (p0 * std::pow(1.0f - t, 3.0f)) +
				(3.0f * p1 * std::pow(1.0f - t, 2.0f) * t) +
				(3.0f * p2 * t * t * (1.0f - t)) +
				(p3 * t * t * t);
		}
		CubicBezier3D::CubicBezier3D(const Vect3& cpi, const Vect3& cpp1, const Vect3& cpp2, const Vect3& cpe)
			: Curve3D()
		{
			this->_list.push_back(cpi);
			this->_list.push_back(cpp1);
			this->_list.push_back(cpp2);
			this->_list.push_back(cpe);
		}
		Vect3 CubicBezier3D::evaluate(const float t)
		{
			return Vect3(
				this->bezierCurveInterpolation(
					this->_list[0].x(), this->_list[1].x(), this->_list[2].x(), this->_list[3].x(), t),
				this->bezierCurveInterpolation(
					this->_list[0].y(), this->_list[1].y(), this->_list[2].y(), this->_list[3].y(), t),
				this->bezierCurveInterpolation(
					this->_list[0].z(), this->_list[1].z(), this->_list[2].z(), this->_list[3].z(), t)
			);
		}
		float CubicBezier3D::bezierCurveInterpolation(const float p0, const float p1, 
			const float p2, const float p3, const float t)
		{
			return (p0 * std::pow(1.0 - t, 3.0f)) +
				(3.0f * p1 * std::pow(1.0f - t, 2.0f) * t) +
				(3.0f * p2 * t * t * (1.0f - t)) +
				(p3 * t * t * t);
		}
		QuadraticBezier2D::QuadraticBezier2D(const Vect2& cpi, const Vect2& cpp, const Vect2& cpe)
			: Curve2D()
		{
			this->_list.push_back(cpi);
			this->_list.push_back(cpp);
			this->_list.push_back(cpe);
		}
		Vect2 QuadraticBezier2D::evaluate(const float t)
		{
			return Vect2(
				this->bezierCurveInterpolation(
					this->_list[0].x(), this->_list[1].x(), this->_list[2].x(), t),
				this->bezierCurveInterpolation(
					this->_list[0].y(), this->_list[1].y(), this->_list[2].y(), t)
			);
		}
		float QuadraticBezier2D::bezierCurveInterpolation(const float p0, const float p1, const float p2, const float t)
		{
			return  (p0 * std::pow((1.0f - t), 2.0f)) +
			(2.0f * p1 * (1.0f - t) * t) +
			(p2 * std::pow(t, 2.0f));
		}
		QuadraticBezier3D::QuadraticBezier3D(const Vect3& cpi, const Vect3& cpp, const Vect3& cpe)
			: Curve3D()
		{
			this->_list.push_back(cpi);
			this->_list.push_back(cpp);
			this->_list.push_back(cpe);
		}
		Vect3 QuadraticBezier3D::evaluate(const float t)
		{
			return Vect3(
				this->bezierCurveInterpolation(
					this->_list[0].x(), this->_list[1].x(), this->_list[2].x(), t),
				this->bezierCurveInterpolation(
					this->_list[0].y(), this->_list[1].y(), this->_list[2].y(), t),
				this->bezierCurveInterpolation(
					this->_list[0].z(), this->_list[1].z(), this->_list[2].z(), t)
			);
		}
		float QuadraticBezier3D::bezierCurveInterpolation(const float p0, const float p1, const float p2, const float t)
		{
			return  (p0 * std::pow((1.0f - t), 2.0f)) +
			(2.0f * p1 * (1.0f - t) * t) +
			(p2 * std::pow(t, 2.0f));
		}
	}
}
