#include "Vector3.hpp"

namespace mb
{
  const Vector3 Vector3::ZERO = Vector3( 0.0f );
  const Vector3 Vector3::ONE = Vector3(1.0f );
  const Vector3 Vector3::FORWARD = Vector3( 0.0f, 0.0f, 1.0f );
  const Vector3 Vector3::BACK = Vector3( 0.0f, 0.0f, -1.0f );
  const Vector3 Vector3::UP = Vector3( 0.0f, 1.0f, 0.0f );
  const Vector3 Vector3::DOWN = Vector3( 0.0f, -1.0f, 0.0f );
  const Vector3 Vector3::LEFT = Vector3( -1.0f, 0.0f, 0.0f );
  const Vector3 Vector3::right = Vector3( 1.0f, 0.0f, 0.0f );
}